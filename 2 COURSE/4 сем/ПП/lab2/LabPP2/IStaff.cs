using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabPP2
{
    interface IStaff
    {
       List<JobVacancy> GetJobVacancies();
       int OpenJobVacancy(JobVacancy jobVacancy);
       bool CloseJobVacancy(int index);
       int AddJobTitle(JobTitle jobTitle);
       bool DelJobTitle(int index);
       Emploee Recruit(JobVacancy job, Person person);
       void Dismiss(Reason reason);
    }
}
