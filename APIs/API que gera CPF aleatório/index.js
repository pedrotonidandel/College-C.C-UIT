const express = require('express');
const geradorCPF = require('gerador-validador-cpf');
const app = express();

app.get('/cpf-aleatorio', (req, res) => {
  const cpf = geradorCPF.generate();

  res.json({ cpf });
});

app.listen(3000, () => {
  console.log('A API está rodando em http://localhost:3000');
});
