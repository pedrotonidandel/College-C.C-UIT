const express = require('express');
const app = express();
const morgan = require('morgan');
const bodyParser = require('body-parser')
const fs = require('fs');
const path = require('path');
const pdf2pic = require('pdf2pic');

const rotaImagens = require('./routes/imagem');

async function convertPdfToImages(pdfBuffer) {
  const converter = new pdf2pic({
    density: 300, // Densidade da imagem em DPI (ajustável)
    savename: 'pdf-to-image', // Nome base para as imagens geradas
    savedir: 'temp', // Diretório onde as imagens JPEG temporárias serão armazenadas
    format: 'jpeg', // Formato de imagem desejado (JPEG)
    size: '1200x1600', // Tamanho da imagem (ajustável)
  });

  try {
    const imagePaths = await converter.convertBuffer(pdfBuffer, -1); // -1 para converter todas as páginas
    const imageBuffers = imagePaths.map((imagePath) => fs.readFileSync(imagePath));
    return imageBuffers;
  } catch (error) {
    throw error;
  }
}

const logDirectory = path.join(__dirname, 'logs');
fs.existsSync(logDirectory) || fs.mkdirSync(logDirectory);

const logStream = fs.createWriteStream(path.join(logDirectory, 'response-times.log'), { flags: 'a' });

app.use(morgan('combined', { stream: logStream }));

function logResponseTime(req, res, next) {
    const start = new Date();
    res.on('finish', () => {
      const end = new Date();
      const responseTime = end - start;
      const logData = `Tempo de resposta: ${responseTime}ms\n`;
      const logFilePath = path.join(logDirectory, 'response-times.log');
  
      fs.appendFile(logFilePath, logData, (err) => {
        if (err) {
          console.error('Erro ao escrever o tempo de resposta no arquivo de log:', err);
        }
      });
    });
    next();
  }

  app.use(logResponseTime);

app.use(morgan('dev'));
app.use('/uploads', express.static('uploads'));

app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true, limit: '10mb' }));

app.use(bodyParser.urlencoded({ extended: false}));
app.use(bodyParser.json());

app.use((req, res, next) => {
    res.header('Access-Control-Allow-Origin', '*');
    res.header(
        'Access-Control-Allow-Header', 
        'Origin, X-Requested-With, Content-Type, Accept, Authorization'
        );

        if(req.method === 'OPTIONS'){
            res.header('Access-Control-Allow-Methods', 'PUT, POST, PATCH, DELETE, GET');
            return res.status(200).send({});
        }

        next();
});

app.use('/imagem', rotaImagens);

app.use((req, res, next) => {
    const erro = new Error('Não encontrado');
    erro.status = 404; // Aqui você deve usar "=" para atribuir o status 404
    next(erro);
});

app.get('/response-times', (req, res) => {
    const logFilePath = path.join(logDirectory, 'response-times.log');
    fs.readFile(logFilePath, 'utf8', (err, data) => {
      if (err) {
        res.status(500).send('Erro ao ler o arquivo de log');
      } else {
        res.type('text/plain').send(data);
      }
    });
  });
  

app.use((error, req, res, next) => {
    res.status(error.status || 500);
    return res.send({
        erro: {
            mensagem: error.message
        }
    });
});

module.exports = app;