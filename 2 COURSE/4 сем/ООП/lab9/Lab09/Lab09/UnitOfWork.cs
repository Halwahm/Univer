using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Microsoft.EntityFrameworkCore;

namespace Lab09
{
    public class UnitOfWork : IDisposable
    {
        private readonly MyContext _context;
        private bool _disposed;

        public UnitOfWork()
        {
            _context = new MyContext();
        }

        public void SaveChanges()
        {
            _context.SaveChanges();
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    _context.Dispose();
                }
            }
            _disposed = true;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
    }

}
