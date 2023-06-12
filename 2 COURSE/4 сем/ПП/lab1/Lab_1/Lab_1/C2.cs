using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    internal class C2 : I1
    {

        C2[] mass;
        private const int Age1 = 23;
        public const int Age2 = 18;
        protected const int Age3 = 22;

        private string name1;
        public string name2;
        protected string name3;

        public event ReturnName ReturnNameEvent;

        private string Name1 { get => name1; set => name1 = value; }
        public string Name2 { get => name2; set => name2 = value; }
        protected string Name3 { get => name3; set => name3 = value; }

        public C2() { }

        public C2( C2 prev )
        {
            Name1 = prev.Name1;
            Name2 = prev.Name2;
            Name3 = prev.Name3;

        }

        public C2( string name1, string name2, string name3 )
        {
            Name1 = name1;
            Name2 = name2;
            Name3 = name3;

        }
        
        //
      
        public void ReturnNames(string nms)
        {
            Console.WriteLine(nms);

        }

        public void FirstName( string nms )
        {
            ReturnNameEvent?.Invoke($"Первое имя= {nms}");
        }

        public void SecName( string nms )
        {
            ReturnNameEvent?.Invoke($"Второе имя= {nms}");

        }
        //
        private void ReturnName1()
        {
            Console.WriteLine($"Имя 1 = {Name1}");

        }

        public void ReturnName2()
        {
            Console.WriteLine($"Имя 2 = {Name2}");

        }
        protected void ReturnName3()
        {
            Console.WriteLine($"Имя 3 = {Name3}");

        }

        public void State()
        {
            Console.WriteLine($"Имя 1 = {Name1} | Имя 2 = {Name2} | Имя 3 = {Name3}");


        }
        public override string ToString()
        {
            return Name1 + " " + Name2 + " " + Name3;
        }


        public C2 this[int index] {
            get=> mass[index];
            set => mass[index]=value;
        }

    }
}
