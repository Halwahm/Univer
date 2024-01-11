using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public partial class cvitantion: data, IDate, IInfo, INotInfo, IOrganize
    {
        string IDate.PrintDatе()
        {
            Console.WriteLine($"Дата поставки: {_date}");
            return "";
        }
        public override string PrintDate()
        {
            if (_date == null)
            {
                Console.WriteLine("no date");
                return "null date";
            }
            Console.WriteLine($"Date - {_date}");
            return "";
        }

        public override string PrintPrice()
        {
            Console.WriteLine($"Price - {Price}");
            return "";
        }
        string IInfo.PrintPrice()
        {
            Console.WriteLine($"Price: {Price}, Organization name: {OrganizationName}");
            return "";
        }
        string INotInfo.PrintPrice()
        {
            Console.WriteLine("Цена отсутствует");
            return "";
        }

        public override string Organize()
        {
            Console.WriteLine($"Organization - {OrganizationName}");
            return "";
        }
        string IOrganize.Organize()
        {
            Console.WriteLine($"Organization name: {OrganizationName}");
            return "";
        }

        public override string ToString()
        {
            Console.WriteLine($"Date: {_date}, Price: {Price}, Organization name: {OrganizationName}");
            return "";
        }

        public override bool Equals(object? obj)
        {
            if (obj is string)
            {
                Console.WriteLine("data type - string");
                return true;
            }
            Console.WriteLine("data type - not string");
            return false;
        }

        public override int GetHashCode()
        {
            Console.WriteLine(Price.GetHashCode());
            return 1;
        }
    }
}
