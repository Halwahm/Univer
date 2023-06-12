using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    class Program
    {
        static void Main(string[] args)
            {

            /*
             2.	Разработайте программный код для создания объекта этого класса,
             продемонстрируйте работоспособность конструкторов, 
             методов, использования полей и свойств.     
             */
            C1 c1 = new C1("Влад","Сеня","Таня");
            C1 c2 = new C1(c1);

            Console.WriteLine(c2.ToString());

            //Console.WriteLine(C1.Age1);
            Console.WriteLine(C1.Age2);
            //Console.WriteLine(C1.Age3);


            //Console.WriteLine(c1.Name1);
            Console.WriteLine(c1.Name2);
            //Console.WriteLine(c1.Name3);


            // c1.ReturnName1(); нельзя из-за модификатора
            c1.ReturnName2();
            //c1.ReturnName3();

            Console.WriteLine();
            c1.State();
            c1.Name2 = "Арсений";
            c1.State();

            Console.WriteLine("\n\n\n");

            //8
            C2 notifInterf=new C2();
            notifInterf.ReturnNameEvent += notifInterf.ReturnNames;
            notifInterf.FirstName("Женя");
            notifInterf.SecName("Саша");

            C2 c2names=new C2("Китти","Сидней","Санни");
            C2 c2names2 = new C2(c2names);

            Console.WriteLine(c2names.ToString());


            //Console.WriteLine(C2.Age1);
            Console.WriteLine(C2.Age2);
            //Console.WriteLine(C2.Age3);


            //Console.WriteLine(c2names.Name1);
            Console.WriteLine(c2names.Name2);
            //Console.WriteLine(c2names.Name3);


            // c2names.ReturnName1(); нельзя из-за модификатора
            c2names.ReturnName2();
            //c2names.ReturnName3();

            Console.WriteLine();
            c2names.State();
            c2names.Name2 = "Арсений";
            c2names.State();


            Parrot popug1 = new Parrot("Попуг",5);
            Console.WriteLine(popug1.ToString());
            popug1.PoPug();
            popug1.Popug("Piastra!");

        }

    }
}

