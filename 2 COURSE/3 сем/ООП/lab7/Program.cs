namespace lab7
{
    public class Program
    {
        public static void Main()
        {
            try
            {
                var mySet = new MySet<string>("test");
                Console.WriteLine(mySet[0]);

                var setData = new MySet<Data>(new Data ("16.02.2002", 16, "Darida"));

                var Data = new Data("15.01.2003", 15, "Confa");  
                setData.Add(Data);

                Console.WriteLine("--------------------------");
                Console.WriteLine("before delete show\n");
                setData.Show();

                Console.WriteLine("--------------------------");
                Console.WriteLine("after delete show\n");
                setData.Delete(Data);
                setData.Show();

                Console.WriteLine("--------------------------");
                MySet<Data>.WriteToFile(setData);
                Console.WriteLine("from file");
                MySet<Data>.ReadFromFile();

                Console.WriteLine(mySet[-1]); //для вызова исключения
            }
            catch (ArgumentOutOfRangeException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                Console.WriteLine("end try-catch-finally");
            }
        }
    }
}