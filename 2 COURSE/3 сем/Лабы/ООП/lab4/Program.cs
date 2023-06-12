using System;
using System.Collections.Generic;

//Квитанция, Накладная, Документ, Чек, Дата, Организация.
namespace lab04
{
    class Program
    {
        static void Main(string[] args)
        {
            var doc1 = new cvitantion("20.02.2000", 142, "Darida");
            var docn = new cvitantion("20.04.2017", 124, "Sosedi");
            doc1.PrintDate();
            doc1.PrintPrice();
            doc1.Organize();

            Console.WriteLine("-------");
            ((IDate)doc1).PrintDatе();
            IDate iDate = doc1;
            iDate.PrintDatе();
            Console.WriteLine("-------");

            ((IInfo)doc1).PrintPrice();
            IInfo check1 = doc1;
            check1.PrintPrice();
            Console.WriteLine("");
            ((INotInfo)doc1).PrintPrice();
            Console.WriteLine("-------");

            ((IOrganize)doc1).Organize();
            Console.WriteLine("-------");

            Console.WriteLine("");
            doc1.ToString();
            doc1.Equals("20.02.2022");
            doc1.Equals(2022);
            doc1.GetHashCode();
            Console.WriteLine("");

            var doc2 = new consNote(1, "Evroopt", "Meat", "20.12.2005");
            ((IDate)doc2).PrintDatе();
            doc2.performed();
            //doc2.imperformed(); 
            doc2.reading();
            doc2.ToString();
            Console.WriteLine(doc2.statusShip);

            /*-----------------------------------*/
            var kopeechka = new cvitantion("16.09.2013", 1234, "Kopeechka");
            if(kopeechka is data)
            {
                Console.WriteLine("kopeechka is data");
            }
            else
            {
                Console.WriteLine("kopeechka isn't data");  
            }

            if(kopeechka is IDate)
            {
                Console.WriteLine("kopeechka is IDate");
            }
            else
            {
                Console.WriteLine("kopeechka isn't IDate");
            }
            /*-----------------------------------*/
            Console.WriteLine();
            IInfo iInfo = kopeechka;
            if (iInfo as data != null)
            {
                Console.WriteLine($"({iInfo}) as data\n");
            }
            else
            {
                Console.WriteLine($"({iInfo}) as not data\n");
            }
            /*-----------------------------------*/
            var array1 = new IDate[] {kopeechka, doc1};

            foreach (var item in array1)
            {
                Printer.IAmPrinting(item);
            }
        }
    }
}