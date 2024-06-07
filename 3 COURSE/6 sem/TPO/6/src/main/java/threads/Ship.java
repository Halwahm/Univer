package threads;

class Ship implements Runnable {
    private final String name;
    private final int maxContainers;
    private int currentContainers;
    private final int remainingCapacity;
    private final Port port;

    public Ship(String name, int maxContainers, int remainingCapacity, Port port) {
        this.name = name;
        this.maxContainers = maxContainers;
        this.currentContainers = 0;
        this.remainingCapacity = remainingCapacity;
        this.port = port;
    }

    public String getName() {
        return name;
    }

    public int getMaxContainers() {
        return maxContainers;
    }

    public int getRemainingCapacity() {
        return remainingCapacity;
    }

    public int getCurrentContainers() {
        return currentContainers;
    }

    public void loadContainers(int count) {
        currentContainers += count;
    }

    public void unloadContainers(int count) {
        currentContainers -= count;
    }

    @Override
    public void run() {
        port.loadShip(this);
        port.unloadShip(this);
    }
}
