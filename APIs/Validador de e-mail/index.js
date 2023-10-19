const express = require('express');
const { validate } = require('email-validator');

const app = express();
const port = 3000;

app.use(express.json());

app.post('/email', (req, res) => {
  const { email } = req.body;
  const valido = validate(email);
  res.json({ valido });
});

app.listen(port, () => {
});