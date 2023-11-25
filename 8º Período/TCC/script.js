document.addEventListener("DOMContentLoaded", function () {
    const chatMessages = document.getElementById("chat-messages");
    const imageNameInput = document.getElementById("image-name");
    const imageInput = document.getElementById("image-input");
    const sendButton = document.getElementById("send-button");
    const copyButton = document.getElementById("copy-button");

    sendButton.addEventListener("click", async function () {
        const file = imageInput.files[0];
        const imageName = imageNameInput.value;

        if (file && imageName) {
            const formData = new FormData();
            formData.append("nome", imageName);
            formData.append("imagem", file);

            // Enviar a imagem para o servidor e obter o ID da imagem
            try {
                const response = await fetch("http://localhost:3001/imagem", {
                    method: "POST",
                    body: formData,
                });

                if (response.ok) {
                    const { id_imagem } = await response.json();

                    // Solicitar reconhecimento de texto usando o ID da imagem
                    const recognitionResponse = await fetch(`http://localhost:3001/imagem/${id_imagem}`, {
                        method: "GET",
                    });

                    if (recognitionResponse.ok) {
                        const { texto } = await recognitionResponse.json();

                        // Use uma regex para extrair o código do boleto e a data de referência
                        const boletoRegex = /Santander 033([\d. ]+)/;
                        const boletoMatch = texto.match(boletoRegex);
                        const codigoBoleto = boletoMatch ? boletoMatch[1].replace(/\s/g, "") : "Código do boleto não encontrado";

                        const dataReferenciaRegex = /Referéncia RG R\$ (\d{2}\/\d{2}\/\d{4})/;
                        const dataReferenciaMatch = texto.match(dataReferenciaRegex);
                        const dataReferencia = dataReferenciaMatch ? dataReferenciaMatch[1] : "Data de referência não encontrada";

                        // Exibir o código do boleto e a data de referência na interface do chatbot com estilo
                        const codeMessage = document.createElement("div");
                        codeMessage.classList.add("bot-message");
                        codeMessage.innerHTML = `
                        <p>Código do Boleto:</p>
                        <div class="code" id="codigo-boleto">${codigoBoleto}</div>
                        <p>Data de Referência:</p>
                        <div class="code" id="data-referencia">${dataReferencia}</div>
                    `;
                        chatMessages.appendChild(codeMessage);
                    } else {
                        console.error("Erro ao obter texto reconhecido da imagem.");
                    }
                } else {
                    console.error("Erro ao enviar a imagem.");
                }
            } catch (error) {
                console.error("Erro ao enviar a imagem:", error);
            }
        } else {
            chatMessages.innerHTML += `<div class="bot-message">Por favor, insira um nome e selecione uma imagem.</div>`;
        }
    });

    // Adicione um ouvinte de evento para copiar o código do boleto quando o botão de cópia for clicado
    copyButton.addEventListener("click", function () {
        const codigoBoletoElement = document.getElementById("codigo-boleto");
        const codigoBoletoValue = codigoBoletoElement.textContent;

        const textArea = document.createElement("textarea");
        textArea.value = codigoBoletoValue;
        document.body.appendChild(textArea);
        textArea.select();
        document.execCommand("copy");
        document.body.removeChild(textArea);
    });
});

// Selecione o botão de cópia
const copyButton = document.getElementById("copy-button");

// Selecione o elemento de mensagem
const copyMessage = document.getElementById("copy-message");

// Adicione um evento de clique ao botão
copyButton.addEventListener("click", () => {
    // Defina o texto da mensagem
    copyMessage.textContent = "O código foi copiado para a área de transferência";

    // Limpe a mensagem após alguns segundos (opcional)
    setTimeout(() => {
        copyMessage.textContent = "";
    }, 3000); // Limpar a mensagem após 3 segundos (pode ajustar o tempo conforme necessário)
});
