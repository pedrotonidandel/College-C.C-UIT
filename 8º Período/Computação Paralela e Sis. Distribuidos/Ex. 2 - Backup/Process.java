import java.util.List;
import java.util.ArrayList;

public class Process {
    private int id;
    private int estado;
    private int osn;
    private int hsn;
    private List<Integer> queue;
    private static int globalOsn = 0; //

    public Process(int id) {
        this.id = id;
        this.estado = 0; // 0: livre, 1: ocupado, 2: aguardando
        this.osn = 0;
        this.hsn = 0;
        this.queue = new ArrayList<>();
    }

    public void requestCS() {
        estado = 2; // Aguardando
        osn = globalOsn;

        System.out.println("Processo " + id + " | OSN = " + osn);

        RequestFunctions.sendMessageToAll(id, osn);
        RequestFunctions.waitForReplies();
        estado = 1; // Ocupando a seção crítica
        CriticalSection.enterCS(id);
        estado = 0; // Livre
        RequestFunctions.sendReplies(queue);

        globalOsn = osn + 1;
    }

    public void receiveRequest(int senderId, int senderOsn) {
        hsn = Math.max(hsn, senderOsn);
        if (estado == 0) {
            RequestFunctions.sendReply(senderId, senderOsn);
        } else if (estado == 1) {
            queue.add(senderId);
        } else if (estado == 2) {
            if (osn < senderOsn || (osn == senderOsn && id < senderId)) {
                queue.add(senderId);
            } else {
                RequestFunctions.sendReply(senderId, senderOsn);
            }
        }
    }

    public void exitCS() {
        // Mostrar o OSN quando o processo sai da seção crítica
        System.out.println("Processo " + id + " OSN=" + osn + " saiu da seção crítica.");
        globalOsn++;

        estado = 0; // Livre
        CriticalSection.exitCS(id);
    }
}
