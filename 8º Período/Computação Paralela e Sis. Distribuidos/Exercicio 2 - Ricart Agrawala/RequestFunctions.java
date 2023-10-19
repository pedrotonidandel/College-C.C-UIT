import java.util.List;

public class RequestFunctions {
    public static void sendMessageToAll(int senderId, int senderOsn) {
        // Simulação de envio de mensagens pros processos
        System.out.println("Processo " + senderId + " enviou requisição para todos os outros processos.");
    }

    public static void waitForReplies() {
        // Simulação de espera da msg dos outros processos
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void sendReply(int receiverId, int senderOsn) {
        // Simulação de resposta
        System.out.println("Processo " + receiverId + " enviou resposta para o Processo " + senderOsn);
    }

    public static void sendReplies(List<Integer> queue) {
        for (int receiverId : queue) {
            sendReply(receiverId, 0);
        }
        queue.clear();
    }
}