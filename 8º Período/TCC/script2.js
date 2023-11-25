// script.js

document.getElementById('sendMessage').addEventListener('click', function() {
    sendMessage();
});

document.getElementById('userInput').addEventListener('keydown', function(event) {
    if (event.key === "Enter") {
        sendMessage();
    }
});

// Adicione um evento para lidar com o envio de imagens
document.getElementById('uploadImage').addEventListener('change', function() {
    handleImageUpload();
});

function sendMessage() {
    var userInput = document.getElementById('userInput');
    var userMessage = userInput.value.trim();
    if (userMessage === "") return;

    // Adicione a mensagem do usuário ao chat
    appendMessage('user', userMessage);

    // Verifique se o usuário enviou uma imagem
    if (document.getElementById('uploadImage').files.length > 0) {
        handleImageUpload();
    } else {
        // Simule uma resposta do chatbot
        simulateBotResponse(userMessage);
    }

    userInput.value = "";
}

function appendMessage(sender, message) {
    var chat = document.getElementById('chat');
    var messageElement = document.createElement('div');
    messageElement.classList.add('message', sender);
    messageElement.textContent = message;
    chat.appendChild(messageElement);
    chat.scrollTop = chat.scrollHeight;
}

function handleImageUpload() {
    var imageInput = document.getElementById('uploadImage');
    if (imageInput.files.length > 0) {
        var uploadedImage = imageInput.files[0];
        // Você pode enviar a imagem para o servidor aqui, semelhante ao seu script original
        // Certifique-se de usar FormData para enviar a imagem.
        sendImageToServer(uploadedImage);
    }
}

function sendImageToServer(image) {
    var formData = new FormData();
    formData.append('imagem', image);

    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:3000/imagem');

    xhr.onload = function() {
        if (xhr.status === 201) {
            var botMessage = 'Imagem enviada com sucesso!';
            appendMessage('bot', botMessage);
        } else {
            var botMessage = 'Erro ao enviar a imagem';
            appendMessage('bot', botMessage);
        }
    };

    xhr.send(formData);
}

function simulateBotResponse(userMessage) {
    // Simule uma resposta do chatbot
    var botMessage = getBotResponse(userMessage);

    setTimeout(function() {
        appendMessage('bot', botMessage);
    }, 500);
}

function getBotResponse(userMessage) {
    // Adicione a lógica para gerar respostas do chatbot aqui
    // ...
}
