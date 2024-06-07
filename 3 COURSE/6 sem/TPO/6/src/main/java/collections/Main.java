package collections;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args)
    {
        ArrayList<Car> carList = new ArrayList<>();

        carList.add(new Car("Toyota", "Camry", 2021, 25000));
        carList.add(new Car("Honda", "Civic", 2022, 22000));
        carList.add(new Car("Ford", "Mustang", 2020, 40000));

        for (Car car : carList) {
            System.out.println(car.getInfo());
        }

        System.out.println("\nTax calculation:");
        for (Car car : carList) {
            System.out.println(car.getInfo() + " - Tax: $" + car.calculateTax());
        }

        List<Car> filteredCars = carList.stream()
                .filter(car -> car.getYear() > 2020)
                .collect(Collectors.toList());

        System.out.println("\nFiltered Cars:");
        filteredCars.forEach(car -> System.out.println(car.getInfo()));

        List<Car> sortedCars = carList.stream()
                .sorted((car1, car2) -> Double.compare(car1.getPrice(), car2.getPrice()))
                .collect(Collectors.toList());

        System.out.println("\nSorted Cars by Price:");
        sortedCars.forEach(car -> System.out.println(car.getInfo()));
    }
}
