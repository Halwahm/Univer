using System.Text;
using System.IO;
using Newtonsoft.Json;

//Квитанция, Накладная, Документ, Чек, Дата, Организация.
namespace lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            #region task from lab4
            /*
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

            //var doc2 = new consNote(1, "Evroopt", "Meat", "20.12.2005");
            //((IDate)doc2).PrintDatе();
            //doc2.performed();
            //doc2.reading();
            //doc2.ToString();
            //Console.WriteLine(doc2.statusShip);

            //-----------------------------------
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
            //-----------------------------------
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
            //-----------------------------------
            var array1 = new IDate[] {kopeechka, doc1};

            foreach (var item in array1)
            {
                Printer.IAmPrinting(item);
            }
            */
            #endregion

            var account = new accounting();

            using (var file = new FileStream("note.txt", FileMode.OpenOrCreate))
            {
                var buffer = new byte[file.Length];
                file.Read(buffer, 0, buffer.Length);
                var textFromFile = Encoding.Default.GetString(buffer);
                var accountArray = textFromFile.Split("\r\n");

                foreach (var being in accountArray)
                {
                    var data = being.Split(" ");

                    switch (data.Length)
                    {
                        case 6:
                            account.Add(new consNote(Convert.ToInt32(data[0]), data[1],
                                data[2], data[3], data[4],
                                (EnumOfNames)Convert.ToInt32(data[5])));
                            break;
                        case 3:
                            account.Add(new cvitantion(new DateTime(Convert.ToInt32(data[0])), 
                                Convert.ToInt32(data[1]), data[2]));
                            break;
                    }
                }
            }

            Console.WriteLine("-----------struct-------------");
            var doc11 = new DocStruct("Document1", new DateTime(2016, 05, 16), "Water from Darida");
            Console.WriteLine($"Name: {doc11.Name}, Age: {doc11.Age}, Description: {doc11.Description}");

            Console.WriteLine();

            Console.WriteLine("-----------Print1-------------");
            account.Print();

            Console.WriteLine();

            Console.WriteLine("-----------Print2-------------");
            var doc21 = new consNote(1, "Darida", "Kopeechka", "12022022", 
                "MineralWater", EnumOfNames.Price);
            account.Remove(doc21);

            var accController = new accountsController();
            accController.SumCheck(account);

            Console.WriteLine();

            Console.WriteLine("-----------CheckCount-------------");
            accController.CheckCount(account);

            Console.WriteLine();

            Console.WriteLine("-----------FoundByName-------------");
            accController.FoundByName(account, "Caffee");

            Console.WriteLine();

            Console.WriteLine("-----------JSON-------------");

            var output = JsonConvert.SerializeObject(account);
            Console.WriteLine(output);
            using (var writer = new StreamWriter("JSON.txt", false)) //перезапись
            {
                writer.Write(output);
            }

            string input;
            using (var reader = new StreamReader("JSON.txt"))
            {
                input = reader.ReadToEnd();
            }

            var deserializedAcc = JsonConvert.DeserializeObject<accounting>(input);
            deserializedAcc.Print();
        }
    }
}