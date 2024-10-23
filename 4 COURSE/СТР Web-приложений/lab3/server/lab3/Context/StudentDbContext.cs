using lab3.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace lab3.Context
{
    public class StudentDbContext : DbContext
    {
        public StudentDbContext() : base("StudentDbConnection") { }

        public DbSet<Student> Students { get; set; }
    }

}