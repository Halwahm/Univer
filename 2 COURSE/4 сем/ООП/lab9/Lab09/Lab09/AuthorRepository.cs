using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab09.Models;
using Microsoft.EntityFrameworkCore;

namespace Lab09
{
    public class AuthorRepository
    {
        private readonly Lab09Context _context = new Lab09Context();

        public AuthorRepository()
        {
        }

        public async Task<IEnumerable<Author>> GetAllAuthors()
        {
            return await _context.Authors.Include(x => x.Books).ToListAsync();
        }

        public async Task<Author> GetAuthorById(int authorId)
        {
            return await _context.Authors.Include(x => x.Books).FirstOrDefaultAsync(x => x.AuthorId == authorId);
        }

        public async Task AddAuthor(Author author)
        {
            _context.Authors.Add(author);
            await _context.SaveChangesAsync();
        }

        public async Task UpdateAuthor(Author author)
        {
            _context.Entry(author).State = EntityState.Modified;
            await _context.SaveChangesAsync();
        }

        public async Task DeleteAuthor(int authorId)
        {
            var author = await _context.Authors.FindAsync(authorId);
            _context.Authors.Remove(author);
            await _context.SaveChangesAsync();
        }

        public async Task<IEnumerable<Author>> GetAuthors()
        {
            return await _context.Authors.ToListAsync();
        }

        public async Task<IEnumerable<Author>> GetAuthorsByName(string name)
        {
            return await _context.Authors.Where(a => a.Name.Contains(name)).ToListAsync();
        }

        public async Task<IEnumerable<Author>> GetAuthorsOrderedByName()
        {
            return await _context.Authors.OrderBy(a => a.Name).ToListAsync();
        }

        public async Task<Author> GetAuthorByName(string name)
        {
            return await _context.Authors.FirstOrDefaultAsync(a => a.Name == name);
        }



        public async Task SaveChangesAsync()
        {
            await _context.SaveChangesAsync();
        }

        public void BeginTransaction()
        {
            _context.Database.BeginTransaction();
        }

        public void CommitTransaction()
        {
            _context.Database.CommitTransaction();
        }

        public void RollbackTransaction()
        {
            _context.Database.RollbackTransaction();
        }

        public void ExecuteSqlCommand(string command)
        {
            _context.Database.ExecuteSqlRaw(command);
        }
    }
}
