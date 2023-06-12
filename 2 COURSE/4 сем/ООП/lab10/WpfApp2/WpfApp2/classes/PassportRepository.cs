using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp2.interfaces;


namespace WpfApp2.classes
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
            return db.PASSPORT;
        }

        public PASSPORT Get(int id)
        {
            return db.PASSPORT.Find(id);
        }

        public void Create(PASSPORT passport)
        {
            db.PASSPORT.Add(passport);
        }

        public void Update(PASSPORT passport)
        {
            db.Entry(passport).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            PASSPORT passport = db.PASSPORT.Find(id);
            if (passport != null)
                db.PASSPORT.Remove(passport);
        }
    }
}
