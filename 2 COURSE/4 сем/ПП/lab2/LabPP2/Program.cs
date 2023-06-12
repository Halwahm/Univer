using System;

namespace LabPP2
{
    class Program
    {
        static void Main(string[] args)
        {
            University university = new University("Hawla", "Something", typeof(string));
            Faculty faculty = new Faculty("Halwa", "Something", typeof(string));

            JobTitle jobTitle = new JobTitle();
            Department department = new Department();

            university.PrintInfo();

            university.AddFaculty(faculty);
            university.AddJobTitle(jobTitle);

            faculty.AddDepartment(department);
            faculty.AddJobTitle(jobTitle);
        }
    }
}
