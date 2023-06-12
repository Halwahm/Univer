using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabPP2
{
    public class University : Organization, IStaff
    {
        protected List<Faculty> faculties = new List<Faculty>();

        public University()
        {

        }

        public University(University university)
        {
            faculties = university.faculties;
        }

        public University(string _name, string address, Type shortName) : base(_name, address, shortName)
        {

        }

        public int AddFaculty(Faculty faculty)
        {
            faculties.Add(faculty);
            return faculties.IndexOf(faculty);
        }

        public bool DelFaculty(int index)
        {
            if (VerFaculty(index))
            {
                faculties.RemoveAt(index);
                return true;
            }
            else
                return false;
        }

        public bool UpdateFaculty(Faculty faculty)
        {
            if (!faculties.Contains(faculty))
                return false;

            int index = faculties.IndexOf(faculty);

            faculties[index] = new Faculty();
            return true;
        }

        private bool VerFaculty(int index)
        {
            if (index >= 0 && index < faculties.Count)
                return true;
            else
                return false;
        }

        public List<Faculty> GetFaculties()
        {
            return faculties;
        }

    }
}
