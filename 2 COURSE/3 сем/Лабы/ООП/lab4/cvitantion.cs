using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab04
{
    public class cvitantion: data, IDate, IInfo, INotInfo, IOrganize
    {
        public cvitantion(string date, int price, string organizationname) 
            : base(date, price, organizationname)   {   }

        string IDate.PrintDatе()
        {
            Console.WriteLine($"Дата поставки: {Date}");
            return "";
        }
        public override string PrintDate()
        {
            if (Date == "")
            {
                Console.WriteLine("no date");
                return "null date";
            }
            Console.WriteLine($"Date - {Date}");
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
            Console.WriteLine($"Date: {Date}, Price: {Price}, Organization name: {OrganizationName}");
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
