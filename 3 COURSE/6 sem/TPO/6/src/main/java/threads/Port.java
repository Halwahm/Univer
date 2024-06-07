package threads;

import java.util.concurrent.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Port {
    private final int maxContainers;
    private int containersCount;
    private final Semaphore dockSemaphore;
    private final Lock lock;

    public Port(int maxContainers, int docksCount) {
        this.maxContainers = maxContainers;
        this.containersCount = 0;
        this.dockSemaphore = new Semaphore(docksCount, true);
        this.lock = new ReentrantLock();
    }

    public void loadShip(Ship ship) {
        try {
            dockSemaphore.acquire();
            lock.lock();
            int availableSpace = Math.min(maxContainers - containersCount, ship.getMaxContainers());
            int loadedContainers = Math.min(availableSpace, ship.getRemainingCapacity());
            ship.loadContainers(loadedContainers);
            containersCount += loadedContainers;
            System.out.println(ship.getName() + " loaded " + loadedContainers + " containers in port. Port containers: " + containersCount);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
            dockSemaphore.release();
        }
    }

    public void unloadShip(Ship ship) {
        try {
            dockSemaphore.acquire();
            lock.lock();
            int unloadedContainers = Math.min(containersCount, ship.getCurrentContainers());
            containersCount -= unloadedContainers;
            ship.unloadContainers(unloadedContainers);
            System.out.println(ship.getName() + " unloaded " + unloadedContainers + " containers in port. Port containers: " + containersCount);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
            dockSemaphore.release();
        }
    }
}