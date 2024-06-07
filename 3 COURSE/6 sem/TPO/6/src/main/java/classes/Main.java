package classes;

import java.util.Arrays;
import java.util.Comparator;

public class Main {
    public static void main(String[] args) {
        Customer[] customers = {
                new Customer(1, "Ivanov", "Ivan", "Ivanovich", "Moscow", "1111-2222-3333-4444", "1234567890123456"),
                new Customer(2, "Petrov", "Petr", "Petrovich", "Saint Petersburg", "2222-3333-4444-5555", "2345678901234567"),
                new Customer(3, "Sidorov", "Sidor", "Sidorovich", "Novosibirsk", "3333-4444-5555-6666", "3456789012345678"),
        };

        // a) List of customers in alphabetical order
        Arrays.sort(customers, Comparator.comparing(Customer::getLastName));
        System.out.println("List of customers in alphabetical order:");
        for (Customer customer : customers) {
            System.out.println(customer);
        }

        // b) List of customers with credit card number in the specified range
        String minCreditCardNumber = "2222-3333-4444-5555";
        String maxCreditCardNumber = "3333-4444-5555-6666";
        System.out.println("\nList of customers with credit card number in the specified range:");
        for (Customer customer : customers) {
            String creditCardNumber = customer.getCreditCardNumber();
            if (creditCardNumber.compareTo(minCreditCardNumber) >= 0 && creditCardNumber.compareTo(maxCreditCardNumber) <= 0) {
                System.out.println(customer);
            }
        }
    }
}
