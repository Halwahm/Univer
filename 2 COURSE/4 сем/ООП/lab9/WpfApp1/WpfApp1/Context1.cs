using Microsoft.EntityFrameworkCore;
using System;
using System.ComponentModel.DataAnnotations.Schema;
//using System.Data.Entity;
using System.Linq;

namespace WpfApp1
{
    public partial class ApplicationContext : DbContext
    {

        public virtual DbSet<ADDRESS> Address { get; set; }
        public virtual DbSet<PASSPORT> Passport { get; set; }
        public virtual DbSet<PERSON> Person { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer("Data Source=halwa\\sqlexpress;Initial Catalog=app1;Integrated Security=True");
        }

/*        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<ADDRESS>()
                .Property(e => e.country)
                .IsFixedLength();

            modelBuilder.Entity<ADDRESS>()
                .Property(e => e.city)
                .IsFixedLength();

            modelBuilder.Entity<ADDRESS>()
                .Property(e => e.street)
                .IsFixedLength();

            modelBuilder.Entity<PASSPORT>()
                .Property(e => e.serial)
                .IsFixedLength();

            modelBuilder.Entity<PERSON>()
                .Property(e => e.first_name)
                .IsFixedLength();

            modelBuilder.Entity<PERSON>()
                .Property(e => e.middle_name)
                .IsFixedLength();

            modelBuilder.Entity<PERSON>()
                .Property(e => e.last_name)
                .IsFixedLength();

            modelBuilder.Entity<PERSON>()
                .Property(e => e.phone)
                .IsFixedLength();
        }
*/    }
}
