using Microsoft.EntityFrameworkCore;


namespace WpfApp2
{
    public partial class StoreContext : DbContext
    {
        public virtual DbSet<Product> Products { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer("Server=halwa\\sqlexpress;Database=StoreDb;Encrypt=False;Trusted_Connection=SSPI");
        }
    }
}
