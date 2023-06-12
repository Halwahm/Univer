/*
 Создать класс Программист с событиями Удалить и 
Мутировать. В main создать некоторое количество объектов
(списков). Подпишите объекты на события произвольным образом. 
Реакция на события может быть следующая: удаление 
первого/последнего элемента списка, случайное перемещение строк 
и т.п. Проверить результаты изменения состояния объектов после 
наступления событий, возможно не однократном
 */

namespace lab8
{
    class Programmer
    {
        private string WhoAmI = "Student";
        public delegate void SelfDestructHandler(string message);
        public event SelfDestructHandler SelfDestruct;

        public delegate void MutateHandler(string message);
        public event MutateHandler Mutate;

        public void RankUp()
        {
            if (WhoAmI == "Student")
            {
                WhoAmI = "Programmer";
                Mutate?.Invoke("Теперь ты раб\n");
            }
            else
            {
                WhoAmI = "Student";
                SelfDestruct?.Invoke("Ошибка, самоуничтожение\n");
            }
        }
    }

    delegate void AddPeopleHandler(string name, List<string> lst);

    public delegate void Action(List<string> lst);
    public delegate bool Predicate<in T>(string str, List<string> lst);

    class ProgrammLW8
    {
        static void Main()
        {
            //first
            Programmer Nikita = new Programmer();
            Nikita.Mutate += (string message) => Console.WriteLine(message);
            Nikita.RankUp();
            Nikita.SelfDestruct += (string message) => Console.WriteLine(message);
            Nikita.RankUp();


            //chast 2
            List<string> Students = new List<string>() { "3.14", "Door", "Bob" }; ;
            List<string> Progrmist = new List<string>() { "HuMan", "ЛиСиЦин", "ManHu" };

            AddPeopleHandler AddStud = (string name, List<string> lst) =>
                lst.Add(name);

            AddStud("Man1", Students);

            foreach (var person in Students)
                Console.WriteLine(person);

            Console.WriteLine("---------------");

            AddStud = (string name, List<string> lst) =>
                lst.Add(name);

            AddStud("ЛиСиЦин", Progrmist);

            foreach (var person in Progrmist)
                Console.WriteLine(person);

            Console.WriteLine("---------------");

            Predicate<string> DelElem = (string str, List<string> lst) => lst.Remove(str);
            DelElem("ЛиСиЦин", Progrmist);

            foreach (var person in Progrmist)
                Console.WriteLine(person);

            Func<List<string>, string> ReturnLastElem = (List<string> lst) =>
            {
                return lst.Last();
            };

            Console.WriteLine();

            Console.WriteLine(ReturnLastElem(Progrmist));
            Console.WriteLine("---------------");

            Action WatchList = (List<string> lst) =>
            {
                foreach (var person in lst)
                    Console.WriteLine(person);
            };

            WatchList(Students);


            var str = "I.   S- i?  T b-e,s t#3";
            Func<string, string> a;

            Console.WriteLine("--------------Working with strings--------------");
            a = Str.RemoveS;
            Console.WriteLine($"Without punctuation marks:\nBefore: {str}\nAfter: {a(str)}\n");
            a = Str.RemoveSpase;
            Console.WriteLine($"Remove spaces:\nBefore: {str}\nAfter: {a(str)}\n");
            a = Str.Upper;
            Console.WriteLine($"Capital letters:\nBefore: {str}\nAfter: {a(str)}\n");
            a = Str.Letter;
            Console.WriteLine($"Lowercase letters:\nBefore: {str}\nAfter: {a(str)}\n");
            a = Str.AddToString;
            Console.WriteLine($"Adding characters:\nBefore: {str}\nAfter: {a(str)}\n");
        }
    }
}