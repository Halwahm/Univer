using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace LabPP2
{
    public class Organization : IStaff
    {
        public int Id { get; private set; }
        public string Name { get; protected set; }
        public Type ShortName { get; protected set; }
        public string Address { get; protected set; }
        public DateTime TimeStamp { get; protected set; }

        public Organization()
        {

        }

        public Organization(Organization organization)
        {
            Name = organization.Name;
            ShortName = organization.ShortName;
            Address = organization.Address;
        }

        public Organization(string _name, string address, Type shortName)
        {
            Name = _name;
            ShortName = shortName;
            Address = address;
        }

        public void PrintInfo()
        {
            Console.WriteLine(Name);
            Console.WriteLine(ShortName);
            Console.WriteLine(Address);
        }

        public List<JobVacancy> GetJobVacancies()
        {
            throw new NotImplementedException();
        }

        public int OpenJobVacancy(JobVacancy jobVacancy)
        {
            return 1;
        }

        public bool CloseJobVacancy(int index)
        {
            return true;
        }

        public int AddJobTitle(JobTitle jobTitle)
        {
            return 1;
        }

        public bool DelJobTitle(int index)
        {
            return true;
        }

        public Emploee Recruit(JobVacancy job, Person person)
        {
            throw new NotImplementedException();
        }

        public void Dismiss(Reason reason)
        {
            
        }
    }
}
