using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public class Printer
    {
        public static void IAmPrinting(IDate element)
        {
            if(element is cvitantion)
            {
                Console.WriteLine($"Type object({element.GetType()}): " + element);
            }
            else
            {
                var temp = element as data;
                if (temp != null)
                {
                    Console.WriteLine($"Type object({temp.GetType()}): " + temp);
                }
            }
        }
    }
}
