namespace LW10
{
    class Home
    {
        public static void Main()
        {
            //Quest 1
            Console.WriteLine("\t\t\t 1 TASK\n");
            string[] month = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

            var selectedMonthN = from m in month
                                 where m.Length == 7
                                 select m;
            Console.WriteLine("Month len 7:");
            foreach (var str in selectedMonthN)
            {
                Console.Write(str + ",  ");
            }

            var selectedMonthWinSum = from m in month
                                      where Array.IndexOf(month, m) < 2 ||
                                            Array.IndexOf(month, m) > 4 && Array.IndexOf(month, m) < 8 ||
                                            Array.IndexOf(month, m) == 11
                                      select m;

            Console.WriteLine("\n\nWinter and summer months:");
            foreach (var str in selectedMonthWinSum)
            {
                Console.Write(str + ",  ");
            }

            var selectedMonthAlfa = from m in month
                                    orderby m
                                    select m;
            Console.WriteLine("\n\nMonth by alphabet:");
            foreach (var str in selectedMonthAlfa)
            {
                Console.Write(str + ",  ");
            }

            var selectedMonthU4 = from m in month
                                  where m.Contains('u') && m.Length > 3
                                  select m;
            Console.WriteLine("\n\nMonths with letter 'u', len >= 4:");
            foreach (var str in selectedMonthU4)
            {
                Console.Write(str + ",  ");
            }

            Console.WriteLine();

            //Quest 2 - 3
            Console.WriteLine("\n\t\t\t 2-3 TASK\n");
            List<Product> ListOne = new List<Product>();
            ListOne.Add(new Product(1, "CSGO", 100, 1, "Valve"));
            ListOne.Add(new Product(1, "Dota2", 0, 1, "Valve"));
            ListOne.Add(new Product(1, "Rust", 150, 1, "FacePunch"));
            ListOne.Add(new Product(1, "CyberPunk 2077", 200, 1, "Cd Project Red"));
            ListOne.Add(new Product(1, "Project Zomboid", 100, 4, "Hz"));
            ListOne.Add(new Product(1, "Don't starve together", 10, 4, "Hz2"));
            ListOne.Add(new Product(1, "The Long Dark", 70, 1, "Hz3"));
            ListOne.Add(new Product(1, "PUBG", 100, 1, "BattleStateGame"));
            ListOne.Add(new Product(1, "ARK", 30, 2, "Debili"));
            ListOne.Add(new Product(1, "Dark Souls 3", 170, 1, "Genius"));

            //список товаров для заданного наименования;
            Console.WriteLine("Cписок товаров для заданного наименования: ");
            IEnumerable<Product> FindCompany = from n in ListOne
                                               where n.Producer == "Valve"
                                               select n;

            Console.WriteLine("FindCompany");
            foreach (var obj in FindCompany)
                Console.WriteLine(obj.Name + "\t" + obj.Producer);
            Console.WriteLine();

            //список товаров для заданного наименования, цена которых не 
            //превосходит заданную;
            Console.WriteLine("Cписок товаров для заданного наименования, цена которых не превосходит заданную: ");
            IEnumerable<Product> FindPrice = from n in ListOne
                                             where n.Price <= 100
                                             select n;

            Console.WriteLine("FindPrice");
            foreach (var obj in FindPrice)
                Console.WriteLine(obj.Name + "\t" + obj.Price);
            Console.WriteLine();

            //количество наименований цена которых больше 100
            Console.WriteLine("Количество наименований цена которых больше 100: ");
            IEnumerable<Product> FindPriceLimit = from n in ListOne
                                                  where n.Price >= 100
                                                  select n;
            Console.WriteLine("FindPriceLimit");
            foreach (var obj in FindPriceLimit)
                Console.WriteLine(obj.Name + "\t" + obj.Price);
            Console.WriteLine();

            //максимальный товар (ваш критерий максимальности)
            Console.WriteLine("Товар с наибольшим значением цены: ");
            IEnumerable<Product> MaxProduct = from n in ListOne
                                              orderby n.Price
                                              select n;

            Console.WriteLine("MaxProductPrice");
            int max = 0;
            foreach (var obj in MaxProduct)
                if (max < obj.Price)
                    max = obj.Price;

            Console.WriteLine(max + "\n");

            //упорядоченный набор товаров по производителю, а потом по 
            //количеству
            Console.WriteLine("Упорядоченный набор товаров по производителю, а потом по количеству: ");
            IEnumerable<Product> SortedByProducer = from n in ListOne
                                                    orderby n.Producer
                                                    select n;
            Console.WriteLine("SortedByProducer");
            foreach (var obj in SortedByProducer)
                Console.WriteLine(obj.Name + "\t" + obj.Producer);

            Console.WriteLine("\n\nSortedByAmount");
            IEnumerable<Product> SortedByAmount = from n in ListOne
                                                  orderby n.Amount
                                                  select n;

            foreach (var obj in SortedByAmount)
                Console.WriteLine(obj.Name + "\t" + obj.Amount);
            Console.WriteLine();


            //Quest 4
            Console.WriteLine("\n\t\t\t 4 TASK\n");
            IEnumerable<Product> CustomFiltered = from n in ListOne
                                                  where n.Producer.StartsWith("V")
                                                  where n.Name.Contains("D")
                                                  orderby n.Price
                                                  join c in FindPrice on n.Price equals c.Price
                                                  select n;
            Console.WriteLine("CustomFiltered");
            foreach (var obj in CustomFiltered)
                Console.WriteLine(obj.Name + "\t" + obj.Producer);
            Console.WriteLine();


            //Quest 5
            IEnumerable<Product> PartOne = from n in ListOne
                                           where n.Price >= 170
                                           select n;

            IEnumerable<Product> PartTwo = from n in ListOne
                                           where n.Price <= 170
                                           join c in PartOne on n.Price equals c.Price
                                           select n;

            Console.WriteLine("\t\t\t 5 TASK\n");
            Console.WriteLine("Join");
            foreach (var obj in PartTwo)
                Console.WriteLine(obj.Name + "\t" + obj.Price);
            Console.WriteLine();

        }
    }
}