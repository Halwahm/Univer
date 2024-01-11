using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    public partial class Product
    {
        //в одном из методов класса для работы с аргументами используйте ref - и out-параметры.
        public void Summing(out double Plus)
        {
            Plus = sum + 1;
            sum = Plus;
            Console.WriteLine("out " + sum);
        }
        public void Debiting(ref double Minus)
        {
            Minus = sum - 1;
            sum = Minus;
            Console.WriteLine("ref " + sum);
        }

        /* переопределяете методы класса Object: Equals, для сравнения объектов,
        GetHashCode - для алгоритма вычисления хэша руководствуйтесь 
        стандартными рекомендациями, ToString – вывода строки –
        информации об объекте.*/
        public override int GetHashCode() //override - для переопределения метода
        {
            Console.WriteLine($"Hashcode of name: {name.GetHashCode()}");
            return name.GetHashCode();
        }
        public override bool Equals(object obj)
        {
            if (obj.GetType() != this.GetType()) 
                return false;
            else 
                return true;
            //return base.Equals(obj);
        }
        public override string ToString()
        {
            return $"{id}\t{name}\t{UPC}\t{manufacturer}\t{price}\t{shelf_life}\t{amount}\t{sum}\t{city}";
        }
    }
}
