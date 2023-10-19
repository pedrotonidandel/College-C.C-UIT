const express = require('express');
const router = express.Router();
const connection = require('../db');

// Rota para registro de novos usuários
router.post('/', (req, res) => {
  const { login, senha } = req.body;

  // Verificar se os campos obrigatórios foram enviados na requisição
  if (!login || !senha) {
    return res.status(400).json({ message: 'Login e senha são obrigatórios' });
  }

  // Verificar se o login já está em uso por outro usuário
  const checkLoginQuery = 'SELECT COUNT(*) AS count FROM usuarios WHERE login = ?';
  connection.query(checkLoginQuery, [login], (checkLoginErr, checkLoginResults) => {
    if (checkLoginErr) {
      console.error('Erro ao verificar login:', checkLoginErr);
      return res.status(500).json({ message: 'Erro ao verificar login' });
    }

    if (checkLoginResults[0].count > 0) {
      return res.status(409).json({ message: 'Login já está em uso' });
    }

    // Inserir o novo usuário no banco de dados
    const insertQuery = 'INSERT INTO usuarios (login, senha) VALUES (?, ?)';
    connection.query(insertQuery, [login, senha], (insertErr, insertResults) => {
      if (insertErr) {
        console.error('Erro ao registrar usuário:', insertErr);
        return res.status(500).json({ message: 'Erro ao registrar usuário' });
      }

      return res.status(200).json({ message: 'Usuário registrado com sucesso' });
    });
  });
});

module.exports = router;
