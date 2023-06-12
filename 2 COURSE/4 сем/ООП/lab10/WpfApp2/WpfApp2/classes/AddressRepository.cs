using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp2.interfaces;
using WpfApp2;

namespace WpfApp2.classes
{
    public class AddressRepository : IRepository<ADDRESS>
    {
        private ApplicationContext db;

        public AddressRepository(ApplicationContext context)
        {
            this.db = context;
        }

        public IEnumerable<ADDRESS> GetAll()
        {
            return db.ADDRESS;
        }

        public ADDRESS Get(int id)
        {
            return db.ADDRESS.Find(id);
        }

        public void Create(ADDRESS address)
        {
            db.ADDRESS.Add(address);
        }

        public void Update(ADDRESS address)
        {
            db.Entry(address).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            ADDRESS address = db.ADDRESS.Find(id);
            if (address != null)
                db.ADDRESS.Remove(address);
        }
    }
}
