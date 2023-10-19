import java.util.concurrent.Semaphore;

public class CriticalSection {
    private static Semaphore csSemaphore = new Semaphore(1);

    public static void enterCS(int id) {
        try {
            csSemaphore.acquire(); // Tenta adquirir o semáforo (exclusão mútua)
            System.out.println("Processo " + id + " está na seção crítica.");
            Thread.sleep(10000); // Permanece na seção crítica por 10 segundos
            System.out.println("Processo " + id + " saiu da seção crítica.");
            csSemaphore.release(); // Libera o semáforo
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void exitCS(int id) {
    }
}
