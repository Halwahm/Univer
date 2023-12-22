using System;
using System.Data.Entity;
using System.Linq;

namespace WpfApp1
{
    public class ModelLocal : DbContext
    {
        // Контекст настроен для использования строки подключения "ModelLocal" из файла конфигурации  
        // приложения (App.config или Web.config). По умолчанию эта строка подключения указывает на базу данных 
        // "WpfApp1.ModelLocal" в экземпляре LocalDb. 
        // 
        // Если требуется выбрать другую базу данных или поставщик базы данных, измените строку подключения "ModelLocal" 
        // в файле конфигурации приложения.
        public ModelLocal()
            : base("name=ModelLocal")
        {
        }
        public virtual DbSet<Category> Category { get; set; }
        public virtual DbSet<Clients> Clients { get; set; }
        public virtual DbSet<Comments> Comments { get; set; }
        public virtual DbSet<OrderDetails> OrderDetails { get; set; }
        public virtual DbSet<Orders> Orders { get; set; }
        public virtual DbSet<Products> Products { get; set; }
        public virtual DbSet<sysdiagrams> sysdiagrams { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Comments>()
                .Property(e => e.CommentText)
                .IsUnicode(false);

            modelBuilder.Entity<Orders>()
                .Property(e => e.TotalPrice)
                .HasPrecision(19, 4);

            modelBuilder.Entity<Orders>()
                .Property(e => e.Amount)
                .HasPrecision(19, 4);

            modelBuilder.Entity<Products>()
                .Property(e => e.Price)
                .HasPrecision(19, 4);
        }
    }
}