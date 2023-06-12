using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public class developer
    {
        private readonly int id;
        private readonly string fio;
        private readonly string office;

        public developer(int id, string fio, string office)
        {
            this.id = id;
            this.fio = fio;
            this.office = office;
        }

        public void GetInfodev()
        {
            Console.WriteLine($"Developer - ID: {id}, FIO: {fio}, Office: {office}");
        }
    }
    public class dlist
    {
        private developer devep;
        public developer Devep 
        {
            get { return devep; }
            set { devep = value; }
        }

        public class production
        {
            private readonly int id;
            private readonly string organizeName;

            public production(int id, string organizeName)
            {
                this.id = id;
                this.organizeName = organizeName;
            }

            public void GetInfoprod()
            {
                Console.WriteLine($"Production - ID: {id}, Production name: {organizeName}");
            }
        }

        public List<string> mylist = new List<string>() { "Pavel", "Pavel", "petr", "Ksenia" };

        public void Show()
        {
            foreach (string item in mylist)
                Console.WriteLine(item);
        }

        public void Show_write()
        {
            foreach (string item in mylist)
                Console.Write(" " + item + " ");
        }

        public int GetSize()
        {
            int size = 0;
            foreach (string item in mylist)
            {
                size++;
            }
            return size;
        }

        public string GetItemByIndex(int index)
        {
            int size = -1;
            foreach (string item in mylist)
            {
                size++;
                if (size == index)
                    return item;
            }
            return "";
        }

        public static dlist operator -- (dlist set)
        {
            Console.WriteLine("Удаление первого элемента списка");
            set.mylist.RemoveAt(0);
            return set;
        }
        public static dlist operator ++ (dlist set)
        {
            Console.Write("Введите элемент списка для добавления в начало: ");
            string listItem = Console.ReadLine();
            set.mylist.Insert(0, listItem);
            return set;
        }
        public static bool operator == (dlist set1, dlist set2)
        {
            if (set1.mylist.Equals(set2.mylist))
                return true;
            else
                return false;
        }
        public static bool operator != (dlist set1, dlist set2)
        {
            if (set1.mylist.Equals(set2.mylist))
                return false;
            else
                return true;
        }
        public static dlist operator * (dlist set1, dlist set2)
        {
            set1.mylist.Concat(set2.mylist);
            return set2;
        }

        public void AddItem(string item)
        {
            mylist.Add(item);
        }
    }
}
