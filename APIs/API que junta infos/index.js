const express = require('express');
const app = express();

app.use(express.json());

app.post('/juntar-info', (req, res) => {
  const { texto1, texto2 } = req.body;
  
  if (!texto1 || !texto2) {
    return res.status(400).json({ error: 'É necessário enviar duas informações.' });
  }
  
  const resposta = texto1 + texto2;
  
  res.status(200).json({ resposta });
});

app.listen(3000, () => {
});