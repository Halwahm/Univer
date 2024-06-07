package exceptions;

import java.util.ArrayList;
import java.util.List;


public class Student {
    private String name;
    private List<Double> grades;

    public Student(String name) {
        this.name = name;
        this.grades = new ArrayList<>();
    }

    public void addGrade(double grade) {
        if (grade < 0 || grade > 10) {
            throw new IllegalArgumentException("Grade must be between 0 and 10");
        }
        grades.add(grade);
    }

    public List<Double> getGrades() {
        return grades;
    }

    public double calculateAverageGrade() {
        if (grades.isEmpty()) {
            throw new IllegalStateException("Student has no grades");
        }
        double sum = 0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
}
