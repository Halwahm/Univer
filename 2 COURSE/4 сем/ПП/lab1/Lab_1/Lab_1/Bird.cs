using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    internal class Bird
    {
        public const string AnimalClass= "Птица";
        public string animalName;
        private string Wings = "Крылья";
        protected string Cluv = "Клюв";

        public string AnimalName { get => animalName; set => value = animalName; }
        public Bird( string userAnimalName ) 
        {
            animalName= userAnimalName;
        }

        public void Popug(string mes)
        {
            Console.WriteLine(mes);
        }

    }
}
