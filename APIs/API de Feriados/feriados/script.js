var apiUrl = 'http://localhost:3002/feriados';

// Enviar datas
document.getElementById('EnviarData').addEventListener('submit', function(event) {
  event.preventDefault(); // Evita o comportamento padrão de envio do formulário

  var inputData = document.getElementById('data').value;
  var datePattern = /^\d{2}\/\d{2}\/\d{4}$/;

  if (!inputData.match(datePattern)) {
    showMessage('Formato de data inválido. Utilize o formato DD/MM/YYYY.', 'error');
  } else {
    var descricao = document.getElementById('descricao').value;

    function convertDateFormat(dateString) {
      var parts = dateString.split('/');
      return parts[2] + '-' + parts[1] + '-' + parts[0];
    }

    var requestData = {
      data: convertDateFormat(inputData),
      descricao: descricao
    };

    fetch(apiUrl, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(requestData)
    })
      .then(function(response) {
        limparMensagens();
        if (response.status === 200) {
          showMessage('Data adicionada com sucesso!', 'success');
        } else if (response.status === 404) {
          showMessage('Data não encontrada!', 'warning');
        } else if (response.status === 409) {
          showMessage('Essa data já está no banco de dados!', 'warning');
        } else if (response.status === 500) {
          showMessage('Erro interno do servidor!', 'error');
        } else {
          showMessage('Erro desconhecido', 'error');
        }
        document.getElementById('EnviarData').reset(); // Limpa o formulário
      })
      .catch(function(error) {
        console.error('Erro:', error);
        showMessage('Erro ao enviar os dados: ' + error.message, 'error');
      });
  }
});
  
// Deletar datas
document.getElementById('DeletarDatas').addEventListener('submit', function(event) {
  event.preventDefault(); // Evita o comportamento padrão de envio do formulário

  var dataDeletar = document.getElementById('data-deletar').value;

  var delet = {
    descricao: dataDeletar
  };

  // Exibe o popup de confirmação
  var confirmationPopup = document.getElementById('confirmation-popup');
  confirmationPopup.style.display = 'flex';

  // Botões do popup
  var confirmYesButton = document.getElementById('confirm-yes');
  var confirmNoButton = document.getElementById('confirm-no');

  // Ação ao clicar no botão "Sim"
  confirmYesButton.addEventListener('click', function() {
    confirmationPopup.style.display = 'none';

    fetch(apiUrl, {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(delet)
    })
      .then(function(response) {
        limparMensagens();
        if (response.status === 200) {
          showMessage('Data removida com sucesso!', 'success');
        } else if (response.status === 404) {
          showMessage('Data não encontrada', 'warning');
        } else if (response.status === 500) {
          showMessage('Erro interno do servidor', 'error');
        } else {
          showMessage('Erro desconhecido', 'error');
        }
        document.getElementById('DeletarDatas').reset(); // Limpa o formulário
      })
      .catch(function(error) {
        console.error('Erro:', error);
        showMessage('Erro ao deletar a data: ' + error.message, 'error');
      });
  });

  // Ação ao clicar no botão "Não" ou fechar o popup
  confirmNoButton.addEventListener('click', function() {
    confirmationPopup.style.display = 'none';
  });
});
  
  // Função para exibir mensagens com cores correspondentes aos estilos do CSS
  function showMessage(message, type) {
    var messageElement = document.createElement('div');
    messageElement.textContent = message;
    messageElement.classList.add('message', type);
  
    var container = document.getElementById('messages');
    container.appendChild(messageElement);
  
    setTimeout(function() {
      container.removeChild(messageElement);
    }, 3000);
  }
  
// Função para buscar os dados do banco de dados e atualizar a tabela
function fetchData() {
  fetch(apiUrl)
    .then(function(response) {
      if (response.status === 200) {
        return response.json();
      } else {
        throw new Error('Erro ao buscar os dados');
      }
    })
    .then(function(data) {
      var tableBody = document.getElementById('data-table-body');

      // Limpa a tabela antes de atualizar com os novos dados
      tableBody.innerHTML = '';

      if (data.dates.length === 0) {
        // Exibe a mensagem "Nenhum dado encontrado"
        var emptyRow = document.createElement('tr');
        emptyRow.id = 'empty-row';

        var emptyCell = document.createElement('td');
        emptyCell.colSpan = 2;
        emptyCell.textContent = 'Nenhum dado encontrado';

        emptyRow.appendChild(emptyCell);
        tableBody.appendChild(emptyRow);
      } else {
        // Itera sobre os dados retornados e cria as linhas da tabela
        data.dates.forEach(function(date) {
          var row = document.createElement('tr');

          var dateCell = document.createElement('td');
          var formattedDate = new Date(date.data).toLocaleDateString('pt-BR');
          dateCell.textContent = formattedDate;

          var descriptionCell = document.createElement('td');
          descriptionCell.textContent = date.descricao;

          row.appendChild(dateCell);
          row.appendChild(descriptionCell);

          tableBody.appendChild(row);
        });
      }
    })
    .catch(function(error) {
      console.error('Erro:', error);
    });
}
  
  // Função para atualizar a tabela quando o botão for clicado
  function atualizarTabela() {
    fetchData();
  }
  
  // Associar evento de clique ao botão
  var btnAtualizar = document.getElementById('atualizarTabela');
  btnAtualizar.addEventListener('click', atualizarTabela);
  
  // Chama a função fetchData para buscar os dados e atualizar a tabela quando a página é carregada
  document.addEventListener('DOMContentLoaded', function() {
    fetchData();
  });

  function limparMensagens() {
    var container = document.getElementById('messages');
    container.innerHTML = '';
  }

  // Obtenha o elemento do cabeçalho da tabela
const tableHeader = document.querySelector("#data-table thead");

// Adicione um evento de rolagem ao elemento da tabela
document.querySelector(".table-container").addEventListener("scroll", function () {
  // Obtenha a posição atual de rolagem vertical
  const scrollTop = this.scrollTop;

  // Ajuste a posição de rolagem do cabeçalho da tabela
  tableHeader.style.transform = `translateY(${scrollTop}px)`;
});