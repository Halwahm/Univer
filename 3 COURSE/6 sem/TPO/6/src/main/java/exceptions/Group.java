package exceptions;

import java.util.ArrayList;
import java.util.List;

public class Group {
    private String name;
    private List<Student> students;

    public Group(String name) {
        this.name = name;
        this.students = new ArrayList<>();
    }

    public void addStudent(Student student) {
        students.add(student);
    }

    public double calculateAverageGrade(String subject) {
        if (students.isEmpty()) {
            throw new IllegalStateException("Group has no students");
        }
        double sum = 0;
        int count = 0;
        for (Student student : students) {
            for (double grade : student.getGrades()) {
                // Assuming each grade corresponds to a subject
                if (grade != 0 && grade >= 0 && grade <= 10) {
                    sum += grade;
                    count++;
                }
            }
        }
        if (count == 0) {
            throw new IllegalStateException("No grades found for subject");
        }
        return sum / count;
    }
}
