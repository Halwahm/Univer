using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace Lab09.Models
{
    public class Author
    {
        public int AuthorId { get; set; }
        public string Name { get; set; }

        public ICollection<Book> Books { get; set; }
    }
}
