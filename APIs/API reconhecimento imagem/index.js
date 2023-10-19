const fs = require('fs');
const openOcr = require('open-ocr');

const imageUrl = 'https://omeudiadia.com.br/wp-content/uploads/2022/03/frases-de-bom-dia-3.png'; // Substitua pela URL da imagem que deseja reconhecer

openOcr.recognizeUrl(imageUrl)
  .then(text => {
    console.log(text); // Exibe o resultado do reconhecimento de texto
  })
  .catch(error => {
    console.error(error);
  });