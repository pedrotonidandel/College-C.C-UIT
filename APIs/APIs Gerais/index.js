const express = require('express');
const translate = require('translate-google');
const { NlpManager } = require('node-nlp');
const geradorCPF = require('gerador-validador-cpf');
const app = express();
const multer = require('multer');
const { createWorker } = require('tesseract.js');

app.use(express.json());

// API de Tradução
const nlpManager = new NlpManager({
  languages: ['en', 'es', 'fr', 'de', 'pt'],
  showLogs: false
});


app.post('/traducao', async (req, res) => {
  const { texto, idiomaDestino } = req.body;

  if (!texto || !idiomaDestino) {
    return res.status(400).json({ error: 'É necessário enviar o texto e o idioma de destino.' });
  }

  try {
    nlpManager.addDocument('pt', texto);
    await nlpManager.train();
    const response = await nlpManager.process('pt', texto);
    const idiomaOrigem = response.locale;

    const resultado = await translate(texto, { from: idiomaOrigem, to: idiomaDestino });
    res.json({ resultado });
  } catch (error) {
    res.status(500).json({ error: 'Ocorreu um erro ao realizar a tradução.' });
  }
});
/* app.post('/traducao', async (req, res) => {
  const { texto, idiomaOrigem, idiomaDestino } = req.body;

  if (!texto || !idiomaOrigem || !idiomaDestino) {
    return res.status(400).json({ error: 'É necessário enviar o texto, idioma de origem e idioma de destino.' });
  }

  try {
    const resultado = await translate(texto, { from: idiomaOrigem, to: idiomaDestino });
    res.json({ resultado });
  } catch (error) {
    res.status(500).json({ error: 'Ocorreu um erro ao realizar a tradução.' });
  }
}); */

// Gerar CPF aleatório
app.get('/cpf-aleatorio', (req, res) => {
    const cpf = geradorCPF.generate();
  
    res.json({ cpf });
  });


// Separar nome e sobrenome
app.post('/nome', (req, res) => {
    const { texto } = req.body;
  
    if (!texto) {
      return res.status(400).json({ error: 'É necessário enviar o nome.' });
    }
  
    const partes = texto.split(' ');
  
    if (partes.length < 2) {
      return res.status(400).json({ error: 'A informação deve conter nome e sobrenome.' });
    }
  
    const nome = partes[0];
    const sobrenome = partes.slice(1).join(' ');
  
    res.json({ nome, sobrenome });
  });


// Juntar informações
  app.post('/juntar-info', (req, res) => {
    const { texto1, texto2 } = req.body;
    
    if (!texto1 || !texto2) {
      return res.status(400).json({ error: 'É necessário enviar duas informações.' });
    }
    
    const resposta = texto1 + texto2;
    
    res.status(200).json({ resposta });
  });

// Reconhece texto da imagem

  const app = express();
  const upload = multer({ dest: 'uploads/' });
  
  app.post('/reconhecer-texto', upload.single('imagem'), async (req, res) => {
    try {
      const worker = createWorker();
      await worker.load();
      await worker.loadLanguage('por'); // Defina o idioma desejado
      await worker.initialize('por'); // Defina o idioma desejado
      const { data: { text } } = await worker.recognize(req.file.path);
      await worker.terminate();
  
      res.json({ texto: text });
    } catch (error) {
      console.error(error);
      res.status(500).json({ error: 'Erro ao reconhecer texto na imagem.' });
    }
  });

app.listen(3000, () => {
});