using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp1.interfaces;


namespace WpfApp1.classes
{
    public class PassportRepository : IRepository<PASSPORT>
    {
        private ApplicationContext db;

        public PassportRepository(ApplicationContext context)
        {
            this.db = context;
        }

        public IEnumerable<PASSPORT> GetAll()
        {
            return db.Passport;
        }

        public PASSPORT Get(int id)
        {
            return db.Passport.Find(id);
        }

        public void Create(PASSPORT passport)
        {
            db.Passport.Add(passport);
        }

        public void Update(PASSPORT passport)
        {
            db.Entry(passport).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            PASSPORT passport = db.Passport.Find(id);
            if (passport != null)
                db.Passport.Remove(passport);
        }
    }
}
