using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp1.interfaces;

namespace WpfApp1.classes
{
    public class PersonRepository : IRepository<PERSON>
    {
        private ApplicationContext db;

        public PersonRepository(ApplicationContext context)
        {
            this.db = context;
        }

        public IEnumerable<PERSON> GetAll()
        {
            return db.Person;
        }

        public PERSON Get(int id)
        {
            return db.Person.Find(id);
        }

        public void Create(PERSON person)
        {
            db.Person.Add(person);
        }

        public void Update(PERSON person)
        {
            db.Entry(person).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            PERSON person = db.Person.Find(id);
            if (person != null)
                db.Person.Remove(person);
        }
    }
}
