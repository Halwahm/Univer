using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public abstract class document : object
    {
        public string _date;
        public string Date
        {
            get => _date;
            set => _date = value;
        }

        public int _CountRead;

        public document(int countRead, string date)
        {
            _CountRead = countRead;
            _date = date;
        }

        public int CountRead
        {
            get => _CountRead;
            set => _CountRead = value;
        }

        public virtual string PrintDate()
        {
            return _date;
        }

        public virtual void reading()
        {
            Console.WriteLine();
        }

        /*public override string ToString()
        {
            return $"this document has been read: {_CountRead} times";
        }*/
    }
}
