const express = require('express');
const app = express();

app.use(express.json());

app.post('/nome', (req, res) => {
  const { texto1 } = req.body;

  if (!texto1) {
    return res.status(400).json({ error: 'É necessário enviar o nome.' });
  }

  const partes = texto1.split(' ');

  if (partes.length < 2) {
    return res.status(400).json({ error: 'A informação deve conter nome e sobrenome.' });
  }

  const nome = partes[0];
  const sobrenome = partes.slice(1).join(' ');

  res.json({ nome, sobrenome });
});

app.listen(3000, () => {
});