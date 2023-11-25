const express = require('express');
const router = express.Router();
const multer = require('multer');
const sharp = require('sharp');
const Tesseract = require('tesseract.js');
const mysql = require('../mysql').pool;

// Função para converter BLOB em buffer
function blobToBuffer(blob) {
    return Buffer.from(blob, 'binary');
}

function removeNewlinesAndReplaceWithSpaces(text) {
    return text.replace(/\n/g, ' ');
}

// Rota para extrair e reconhecer o texto da imagem
router.get('/:id_imagem', (req, res) => {
    const idImagem = req.params.id_imagem;
    mysql.getConnection((error, conn) => {
        if (error) {
            return res.status(500).send({ error: error });
        }
        conn.query(
            'SELECT * FROM imagens WHERE id_imagem = ?',
            [idImagem],
            async (error, resultado, fields) => {
                conn.release(); // Libera a conexão

                if (error) {
                    return res.status(500).send({ error: error });
                }

                if (resultado.length === 0) {
                    return res.status(404).send({ message: 'Imagem não encontrada.' });
                } else {
                    try {
                        const imagem = resultado[0];
                        const imageBuffer = blobToBuffer(imagem.imagem);

                        // Use o método recognize para extrair o texto da imagem
                        const { data: { text } } = await Tesseract.recognize(
                            imageBuffer,
                            'por+eng', // Idioma de reconhecimento (Portuguese + English)
                            {
                                logger: m => console.log(m) // Função de registro opcional para exibir informações do processo
                            }
                        );

                        const textoFormatado = removeNewlinesAndReplaceWithSpaces(text);

                        return res.status(200).send({ texto: textoFormatado });
                    } catch (error) {
                        return res.status(500).send({ error: error.message });
                    }
                }
            }
        );
    });
});
const limits = {
    fileSize: 10 * 1024 * 1024, // 10MB
};
const storage = multer.memoryStorage(); // Armazene a imagem em memória para fácil processamento
const upload = multer({ storage: storage, limits: limits });

// Insere imagem
router.post('/', upload.single('imagem'), (req, res) => {
  const imageName = req.body.nome;
  const file = req.file;

  if (file) {
    const imageBuffer = file.buffer;

    mysql.getConnection((error, conn) => {
      if (error) {
        return res.status(500).send({ error: error });
      }

      conn.query(
        'INSERT INTO imagens (nome, imagem) VALUES (?, ?)',
        [imageName, imageBuffer],
        (error, resultado, field) => {
          conn.release();
          if (error) {
            return res.status(500).send({ error: error });
          }
          res.status(201).send({
            mensagem: 'Imagem inserida com sucesso!',
            id_imagem: resultado.insertId,
          });
        }
      );
    });
  } else {
    res.status(400).send({ error: 'Por favor, selecione um arquivo para fazer upload.' });
  }
});

// Retorna todas as imagens
router.get('/', (req, res) => {
    mysql.getConnection((error, conn) => {
        if (error) {
            return res.status(500).send({ error: error });
        }
        conn.query(
            'SELECT * FROM imagens;',
            async (error, resultado, fields) => {
                conn.release(); // Libera a conexão

                if (error) {
                    return res.status(500).send({ error: error });
                }

                if (resultado.length === 0) {
                    return res.status(200).send({ message: 'O banco de dados está vazio.' });
                } else {
                    try {
                        const imagensComDados = await Promise.all(
                            resultado.map(async (imagem) => {
                                const imagemComDados = { ...imagem };

                                // Converte dados binários em imagem reconhecível (JPEG)
                                const imageBuffer = imagem.imagem; // Não é mais necessário converter para JPEG
                                const imageBase64 = imageBuffer.toString('base64'); // Converte para base64
                                imagemComDados.imagem = imageBase64; // Armazena o BLOB em base64

                                return imagemComDados;
                            })
                        );
                        return res.status(200).send({ response: imagensComDados });
                    } catch (error) {
                        return res.status(500).send({ error: error.message });
                    }
                }
            }
        );
    });
});


// Deleta imagem
router.delete('/:id_imagem', (req, res) => {
    const idImagem = req.params.id_imagem;
    mysql.getConnection((error, conn) => {
        if (error) {
            return res.status(500).send({ error: error });
        }
        conn.query(
            `DELETE FROM imagens WHERE id_imagem = ?`,
            [idImagem],
            (error, resultado, field) => {
                conn.release(); // Libera a conexão

                if (error) {
                    return res.status(500).send({ error: error });
                }
                res.status(200).send({
                    mensagem: 'Imagem removida com sucesso!'
                });
            }
        );
    });
});



module.exports = router;