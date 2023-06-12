using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab04
{
    public abstract class data
    {
        public string _date;
        public string Date 
        {
            get => _date;
            set => _date = value;   
        }

        public int _price;
        public int Price
        {
            get => _price;
            set => _price = value;
        }

        public string _organizationName;
        public string OrganizationName
        {
            get => _organizationName;
            set => _organizationName = value;
        }

        public data(string date, int price, string organizename)
        {
            _date = date;
            _price = price;
            OrganizationName = organizename;
        }

        public virtual string PrintDate()
        {
            Console.WriteLine($"Date...");
            return $"Дата: {Date}";
        }

        public virtual string PrintPrice()
        {
            Console.WriteLine($"Price...");
            return $"";
        }

        public abstract string Organize();
        /*{
            Console.WriteLine($"Organize...");
            return $"";
        }*/

        /*public override string ToString()
        {
            Console.WriteLine("nothing");
            return "";
        }*/
    }
}
