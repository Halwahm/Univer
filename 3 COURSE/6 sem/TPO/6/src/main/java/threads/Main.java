package threads;

import java.util.concurrent.*;

public class Main {
    public static void main(String[] args) {
        Port port = new Port(100, 3);
        ExecutorService executorService = Executors.newFixedThreadPool(5);

        // Create and start ships
        for (int i = 1; i <= 5; i++) {
            Ship ship = new Ship("Ship " + i, 50, 20, port);
            executorService.execute(ship);
        }

        executorService.shutdown();
    }
}

