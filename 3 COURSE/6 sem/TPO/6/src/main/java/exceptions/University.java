package exceptions;

import java.util.ArrayList;
import java.util.List;

public class University {
    private String name;
    private List<Faculty> faculties;

    public University(String name) {
        this.name = name;
        this.faculties = new ArrayList<>();
    }

    public void addFaculty(Faculty faculty) {
        faculties.add(faculty);
    }

    public double calculateAverageGrade(String subject) {
        if (faculties.isEmpty()) {
            throw new IllegalStateException("University has no faculties");
        }
        double sum = 0;
        int count = 0;
        for (Faculty faculty : faculties) {
            try {
                sum += faculty.calculateAverageGrade(subject);
                count++;
            } catch (IllegalStateException e) {
                // No groups with grades found for subject in this faculty
            }
        }
        if (count == 0) {
            throw new IllegalStateException("No faculties with grades found for subject");
        }
        return sum / count;
    }
}
