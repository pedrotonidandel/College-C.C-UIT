public class CriticalSection {
    public static void enterCS(int id) {
        // Simulação de execução na seção crítica (10 segundos)
        System.out.println("Processo " + id + " está na seção crítica.");
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Processo " + id + " saiu da seção crítica.");
    }

    public static void exitCS(int id) {
        // Aqui você pode implementar qualquer ação de saída da seção crítica, se necessário.
    }
}
