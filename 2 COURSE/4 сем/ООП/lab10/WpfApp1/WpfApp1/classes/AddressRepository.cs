using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp1.interfaces;

namespace WpfApp1.classes
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
            return db.Address;
        }

        public ADDRESS Get(int id)
        {
            return db.Address.Find(id);
        }

        public void Create(ADDRESS address)
        {
            db.Address.Add(address);
        }

        public void Update(ADDRESS address)
        {
            db.Entry(address).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            ADDRESS address = db.Address.Find(id);
            if (address != null)
                db.Address.Remove(address);
        }
    }
}
