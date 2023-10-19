const express = require('express');
const router = express.Router();

const connection = require('../db');

// Rota para enviar datas e descrições para o banco de dados
router.post('/', (req, res) => {
  const { data, descricao } = req.body;

  if (!data || !descricao) {
    return res.status(400).json({ message: 'Dados inválidos' });
  }

  const checkQuery = 'SELECT COUNT(*) AS count FROM feriados WHERE data = ?';
  connection.query(checkQuery, [data], (checkErr, checkResults) => {
    if (checkErr) {
      console.error('Erro ao verificar data:', checkErr);
      return res.status(500).json({ message: 'Erro ao verificar data' });
    }

    if (checkResults[0].count > 0) {
      return res.status(409).json({ message: 'A data já está presente no banco de dados' });
    }

    const insertQuery = 'INSERT INTO feriados (data, descricao) VALUES (?, ?)';
    connection.query(insertQuery, [data, descricao], (insertErr, insertResults) => {
      if (insertErr) {
        console.error('Erro ao inserir data:', insertErr);
        return res.status(500).json({ message: 'Erro ao inserir data' });
      }

      return res.status(200).json({ message: 'Data inserida com sucesso' });
    });
  });
});

// Rota para deletar datas pela descrição
router.delete('/', (req, res) => {
  const { descricao } = req.body;

  if (!descricao) {
    return res.status(400).json({ message: 'Descrição inválida' });
  }

  const query = 'DELETE FROM feriados WHERE descricao = ?';
  connection.query(query, [descricao], (err, results) => {
    if (err) {
      console.error('Erro ao deletar datas:', err);
      return res.status(500).json({ message: 'Erro ao deletar datas' });
    }

    if (results.affectedRows > 0) {
      return res.status(200).json({ message: 'Data deletada com sucesso' });
    } else {
      return res.status(404).json({ message: 'Nenhuma data encontrada com essa descrição' });
    }
  });
});

// Rota para verificar se uma data já existe no banco de dados
router.get('/:descricao', (req, res) => {
  const { descricao } = req.params;

  const query = 'SELECT COUNT(*) AS count FROM feriados WHERE descricao = ?';
  connection.query(query, [descricao], (err, results) => {
    if (err) {
      console.error('Erro ao buscar data:', err);
      return res.status(500).json({ message: 'Erro ao buscar data' });
    }

    if (results[0].count > 0) {
      return res.status(200).json({ mensagem: 'A data já existe no banco de dados.' });
    } else {
      return res.status(200).json({ mensagem: 'A data não existe no banco de dados' });
    }
  });
});

// Rota para retornar as datas presentes no banco de dados e suas descrições
router.get('/', (req, res) => {

  const query = 'SELECT data, descricao FROM feriados';
  connection.query(query, (err, results) => {
    if (err) {
      console.error('Erro ao buscar datas:', err);
      return res.status(500).json({ message: 'Erro ao buscar datas' });
    }

    if (results.length > 0) {
      const dates = results.map((result) => ({
        data: result.data,
        descricao: result.descricao,
      }));
      return res.status(200).json({ dates });
    } else {
      return res.status(404).json({ message: 'Nenhuma data encontrada no banco de dados' });
    }
  });
});

module.exports = router;