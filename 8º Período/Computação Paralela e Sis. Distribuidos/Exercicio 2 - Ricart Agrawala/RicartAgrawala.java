import java.util.List;
import java.util.ArrayList;

public class RicartAgrawala {
    public static void main(String[] args) {
        int numProcesses = 5;
        List<Process> processes = new ArrayList<>();

        for (int i = 0; i < numProcesses; i++) {
            processes.add(new Process(i));
        }

        processes.get(3).requestCS();
        processes.get(4).requestCS();
        processes.get(3).requestCS();
        processes.get(4).requestCS();
        processes.get(1).requestCS();
    }
}
