package fundamentals;

import java.util.Random;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Enter name: ");
        String name = new Scanner(System.in).nextLine();
        System.out.println("Hello, " + name + "!!!");

        // Task 2: Display command line arguments in reverse order
        displayArgsInReverse(args);

        // Task 3: Display random numbers with and without newline
        displayRandomNumbers(5);

        // Task 4: Calculate sum and product of command line integer arguments
        calculateSumAndProduct(args);

        // Task 5: Display month name based on input number
        displayMonthName();
    }

    // Task 2: Display command line arguments in reverse order
    public static void displayArgsInReverse(String[] args) {
        System.out.println("Command line arguments in reverse order:");
        for (int i = args.length - 1; i >= 0; i--) {
            System.out.println(args[i]);
        }
    }

    // Task 3: Display random numbers with and without newline
    public static void displayRandomNumbers(int count) {
        Random random = new Random();
        System.out.println("Random numbers with newline:");
        for (int i = 0; i < count; i++) {
            System.out.println(random.nextInt(100));
        }
        System.out.println("Random numbers without newline:");
        for (int i = 0; i < count; i++) {
            System.out.print(random.nextInt(100) + " ");
        }
        System.out.println();
    }

    // Task 4: Calculate sum and product of command line integer arguments
    public static void calculateSumAndProduct(String[] args) {
        int sum = 0;
        int product = 1;
        for (String arg : args) {
            int num = Integer.parseInt(arg);
            sum += num;
            product *= num;
        }
        System.out.println("Sum of command line integer arguments: " + sum);
        System.out.println("Product of command line integer arguments: " + product);
    }

    // Task 5: Display month name based on input number
    public static void displayMonthName() {
        Scanner scanner = new Scanner(System.in);
        int monthNumber;
        do {
            System.out.println("Enter a number from 1 to 12:");
            while (!scanner.hasNextInt()) {
                System.out.println("That's not a number! Enter a number from 1 to 12:");
                scanner.next();
            }
            monthNumber = scanner.nextInt();
        } while (monthNumber < 1 || monthNumber > 12);

        String[] months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        System.out.println("Month corresponding to the number " + monthNumber + " is " + months[monthNumber - 1]);
    }
}
