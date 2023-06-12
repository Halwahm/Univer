using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabPP2
{
    public class Faculty : Organization, IStaff
    {
        protected List<Department> departments;

        public Faculty()
        {

        }

        public Faculty(Faculty university)
        {
            departments = university.departments;
        }

        public Faculty(string _name, string address, Type shortName): base(_name, address, shortName)
        {

        }

        public int AddDepartment(Department department)
        {
            departments.Add(department);
            return departments.IndexOf(department);
        }

        public bool DelDepartment(int index)
        {
            if (VerDepartment(index))
            {
                departments.RemoveAt(index);
                return true;
            }
            else
                return false;
        }

        public bool UpdateDepartment(Department department)
        {
            if (!departments.Contains(department))
                return false;

            int index = departments.IndexOf(department);

            departments[index] = new Department();
            return true;
        }

        private bool VerDepartment(int index)
        {
            if (index >= 0 && index < departments.Count)
                return true;
            else
                return false;
        }

        public List<Department> GetFaculties()
        {
            return departments;
        }
    }
}
