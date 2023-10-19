const atualizarTabelaBtn = document.getElementById('atualizarTabela');
const iconRefresh = document.getElementById('iconRefresh');

atualizarTabelaBtn.addEventListener('click', () => {
  iconRefresh.classList.add('rotate'); 

  setTimeout(() => {
    iconRefresh.classList.remove('rotate'); 
  }, 1000); 
});