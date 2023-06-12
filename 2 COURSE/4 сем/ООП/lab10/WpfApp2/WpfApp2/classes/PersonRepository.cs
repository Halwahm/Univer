using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp2.interfaces;

namespace WpfApp2.classes
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
            return db.PERSON;
        }

        public PERSON Get(int id)
        {
            return db.PERSON.Find(id);
        }

        public void Create(PERSON person)
        {
            db.PERSON.Add(person);
        }

        public void Update(PERSON person)
        {
            db.Entry(person).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            PERSON person = db.PERSON.Find(id);
            if (person != null)
                db.PERSON.Remove(person);
        }
    }
}
