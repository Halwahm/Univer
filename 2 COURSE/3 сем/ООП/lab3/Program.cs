using System;

namespace lab3
{
    class Programm {
        public static void Main()
        {
            dlist item1 = new dlist();
            dlist item2 = new dlist();
            item2.AddItem("Егор");

            Console.WriteLine("--------- Перегрузка оператора ++ ---------"); //добавить элемент в начало списка
            item1++;
            item1.Show();

            Console.WriteLine("--------- Перегрузка оператора -- ---------"); //удалить первый элемент списка
            item1--;
            item1.Show();

            Console.WriteLine("--------- Перегрузка оператора != ---------"); //проверка на неравенство
            item1.Show_write(); Console.Write(" != "); item2.Show_write();
            Console.WriteLine("\n");
            Console.WriteLine(item1 != item2);

            Console.WriteLine("--------- Перегрузка оператора * ---------"); //объединение
            Console.WriteLine("Объединили два списка");
            item1 = item1 * item2;
            item1.Show();

            Console.WriteLine("-------------------------------------------");
            dlist dev1 = new dlist();
            dev1.Devep = new developer(1, "Vasya", "OOP");   
            dev1.Devep.GetInfodev();

            Console.WriteLine("-------------------------------------------");
            dlist.production prod1 = new dlist.production(2, "Halen");
            prod1.GetInfoprod();

            Console.WriteLine("------------- Расширение Dif ----------------"); //разница между макс и мин
            Console.Write("Введите несколько слов: ");
            string itemstr = Console.ReadLine();
            int ee = itemstr.Maxstr();
            Console.WriteLine($"Max str: {ee}");
            int yy = itemstr.Minstr();
            Console.WriteLine($"Min str: {yy}");
            int rr = itemstr.Difstr();
            Console.WriteLine($"Dif str: {rr}");
            item1.Show();
            int e = item1.Max();
            Console.WriteLine($"Max dlist: {e}");
            int y = item1.Min();
            Console.WriteLine($"Min dlist: {y}");
            int r = item1.Dif();
            Console.WriteLine($"Dif dlist: {r}");

            Console.WriteLine("---------------------------------------------");
            string abc = "awdg fseol  ajes";
            Console.WriteLine($"{abc}\tКоличество слов: {abc.CountOfWords()}");
            Console.WriteLine("---------------------------------------------");

            int r2 = item1.Sum();
            item1.Show();
            Console.WriteLine($"Количество букв в словах: {r2}");
            Console.WriteLine("---------------------------------------------");

            int coun = item1.CountOfBigLetters();
            item1.Show();
            Console.WriteLine($"Количество слов, начинающихся с заглавной буквы: {coun}");
            Console.WriteLine("---------------------------------------------");

            int repeat = item1.CountOfRepeat();
            item1.Show();
            Console.WriteLine($"Количество повторяющихся элементов: {repeat}");
        }
    }
}