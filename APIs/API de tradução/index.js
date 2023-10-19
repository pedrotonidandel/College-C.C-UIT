const express = require('express');
const translate = require('translate-google');
const app = express();

app.use(express.json());

app.post('/traducao', async (req, res) => {
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
});

app.listen(3000, () => {
});
