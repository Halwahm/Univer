package collections;

public class Car implements ICar{
    private String brand;
    private String model;
    private int year;
    private double price;

    public Car(String brand, String model, int year, double price) {
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.price = price;
    }

    public String getBrand() {
        return brand;
    }

    public String getModel() {
        return model;
    }

    public int getYear() {
        return year;
    }

    public double getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return "Brand: " + brand + ", Model: " + model + ", Year: " + year + ", Price: $" + price;
    }

    public String getInfo() {
        return "Brand: " + brand + ", Model: " + model + ", Year: " + year + ", Price: $" + price;
    }

    public double calculateTax() {
        return 0.02 * price;
    }
}
