using Microsoft.EntityFrameworkCore;
using System;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;

namespace WpfApp2
{
    public partial class ApplicationContext : DbContext
    {
        public virtual DbSet<ADDRESS> ADDRESS { get; set; }
        public virtual DbSet<PASSPORT> PASSPORT { get; set; }
        public virtual DbSet<PERSON> PERSON { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer("Data Source=halwa\\sqlexpress;Initial Catalog=app1;Integrated Security=True");
        }
    }
}
