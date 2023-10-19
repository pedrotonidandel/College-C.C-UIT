const express = require('express');
const app = express();

app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*');
  res.header(
    'Access-Control-Allow-Headers', 
    'Origin, X-Requested-With, Content-Type, Accept, Authorization'
  );

  if (req.method === 'OPTIONS') {
    res.header('Access-Control-Allow-Methods', 'PUT, POST, PATCH, DELETE, GET');
    return res.status(200).send({});
  }
  next();
});

// Importar as rotas
const feriadosRoutes = require('./routes/feriados.js');

// Configurar middlewares
app.use(express.json());

// Configurar as rotas
app.use('/feriados', feriadosRoutes);

// Iniciar o servidor
const port = 3002;
app.listen(port, () => {
  console.log(`Servidor rodando na porta ${port}`);
});
