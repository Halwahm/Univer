package exceptions;

public class Main {
    public static void main(String[] args) {
        // Создаем студентов с оценками
        Student student1 = new Student("Alice");
        student1.addGrade(8.5);
        student1.addGrade(7.0);
        student1.addGrade(9.0);

        Student student2 = new Student("Bob");
        student2.addGrade(6.0);
        student2.addGrade(7.5);
        student2.addGrade(8.0);

        // Создаем группу и добавляем в нее студентов
        Group group1 = new Group("Group 1");
        group1.addStudent(student1);
        group1.addStudent(student2);

        // Создаем факультет и добавляем в него группу
        Faculty faculty1 = new Faculty("Engineering");
        faculty1.addGroup(group1);

        // Создаем университет и добавляем в него факультет
        University university = new University("My University");
        university.addFaculty(faculty1);

        // Выполняем задачи по расчету средних оценок
        System.out.println("Average grade for Alice: " + student1.calculateAverageGrade());
        System.out.println("Average grade for Bob: " + student2.calculateAverageGrade());
        System.out.println("Average grade for Group 1 in Math: " + group1.calculateAverageGrade("Math"));
        System.out.println("Average grade for Engineering faculty in Math: " + faculty1.calculateAverageGrade("Math"));
        System.out.println("Average grade for Math in the university: " + university.calculateAverageGrade("Math"));
    }
}
