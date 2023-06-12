using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    internal class Parrot:Bird
    {
        public string animalName;
        public int animalAge;
     
        public string AnimalName { get => animalName; set => value = animalName; }
        public int AnimalAge { get => animalAge; set => value = animalAge; }

        public Parrot( string userAnimalName, int userAnimalAge) : base(userAnimalName)
        {
            animalName = userAnimalName;
            animalAge = userAnimalAge;
        }

        public override string ToString()
        {
            return "\n" + AnimalClass +"\nИмя: " + animalName + "\nВозраст: " + animalAge + "\n"+ Cluv; //+ Wings не доступно наследование из-за доступа
        }

        public void PoPug() 
        {
            Console.WriteLine("PoPug");
        }
    }
}
