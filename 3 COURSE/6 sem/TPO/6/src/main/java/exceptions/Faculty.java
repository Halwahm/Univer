package exceptions;

import java.util.ArrayList;
import java.util.List;

public class Faculty {
    private String name;
    private List<Group> groups;

    public Faculty(String name) {
        this.name = name;
        this.groups = new ArrayList<>();
    }

    public void addGroup(Group group) {
        groups.add(group);
    }

    public double calculateAverageGrade(String subject) {
        if (groups.isEmpty()) {
            throw new IllegalStateException("Faculty has no groups");
        }
        double sum = 0;
        int count = 0;
        for (Group group : groups) {
            try {
                sum += group.calculateAverageGrade(subject);
                count++;
            } catch (IllegalStateException e) {
                // No grades found for subject in this group
            }
        }
        if (count == 0) {
            throw new IllegalStateException("No groups with grades found for subject");
        }
        return sum / count;
    }
}
