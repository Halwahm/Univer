/*using System.Collections;
*/

/*Создать класс Product: id, Наименование, UPC,
Производитель, Цена, Срок хранения, Количество.
Свойства и конструкторы должны обеспечивать проверку
корректности. Добавить метод вывода общей суммы продукта.

Создать массив объектов. Вывести:
a) список товаров для заданного наименования;
b) список товаров для заданного наименования, цена которых не превосходит заданную;*/

namespace lab2
{
    //сделайте класс partial
    public partial class Product
    {
        private static int _idCounter;
        private readonly int id;
        private readonly string name;
        private readonly int UPC;
        private readonly string manufacturer;
        private int amount;
        //свойства(get, set)
        private double price;
        public double Price
        {
            get { return price; }
            set { price = value; }
        }
        private string shelf_life;
        public string Shelf_life
        {
            get { return shelf_life; }
            set { shelf_life = value; }
        }
        public int Amount
        {
            get { return amount; }
            set { amount = value; }
        }
        private double sum;
        public double Sum
        {
            get { return sum; }
            set
            {
                sum = value;
            }

        }

        //статический конструктор
        static Product()
        {
            _idCounter = 0;
            Console.WriteLine("Product_static:");
        }

        /*создайте в классе статическое поле, хранящее количество созданных 
        объектов (инкрементируется в конструкторе) и статический 
        метод вывода информации о классе.*/
        public static int count;

        //Не менее трех конструкторов
        public Product(int i, string n, int u, string m, double p, string sl, int a, double s) { id = i; name = n; UPC = u; manufacturer = m; price = p; shelf_life = sl; amount = a; sum = s; count++; _idCounter++; }
        public Product(int iii) { id = iii; name = "unknown"; UPC = 000000000; manufacturer = "unknown"; price = 0; shelf_life = "unknown"; amount = 0; count++; _idCounter = 0; }
        public Product(int ii, string nn, int uu, string mm) { id = ii; name = nn; UPC = uu; manufacturer = mm; price = 12; shelf_life = "3 months"; amount = 2; sum = 44; count++; _idCounter++; }

        //закрытый конструктор
        private Product()
        {
            //Console.WriteLine("Product_private:");
        }

        //поле- константу
        public const string city = "Minsk";

        //Создать массив объектов.
        public static void Array()
        {
            var Product = new Product[3];
            Product[0] = new Product(1, "Pechen'ka", 456789, "Tuk", 1.00, "6 months", 12, 120);
            Product[1] = new Product(2, "Oil", 1234987, "Shell", 25.00, "12 months", 5, 125);
            Product[2] = new Product(3, "Butter", 1203654, "Molo", 0.25, "1 week", 4, 1);
            Console.Write("Введите название (имеющиеся: Pechen'ka, Oil, Butter): ");
            string given_name = Console.ReadLine();
            string[] words = { Product[0].name, Product[1].name, Product[2].name };
            string a = words[0];
            string b = words[1];
            string c = words[2];
            // список товаров для заданного наименования, цена которых не превосходит заданную;
            Console.Write("Задайте цену(): ");
            double pr = Console.Read();
            if (a == given_name){
                Console.WriteLine(a);
                if (Product[0].price <= pr)
                    Console.WriteLine(Product[0].name + '-' + Product[0].price);
                else
                    Console.WriteLine("Товар с похожей ценой отсутствует");
            } 
            else Console.WriteLine("");

             if (b == given_name)
            {
                Console.WriteLine(b);
                if (Product[1].price <= pr)
                    Console.WriteLine(Product[1].name + '-' + Product[1].price);
                else
                    Console.WriteLine("Товар с похожей ценой отсутствует");
            }
            else Console.WriteLine("");

            if (c == given_name)
            {
                Console.WriteLine(c);
                if (Product[2].price <= pr)
                    Console.WriteLine(Product[2].name + '-' + Product[2].price);
                else
                    Console.WriteLine("Товар с похожей ценой отсутствует");
            }
            else Console.WriteLine("");
        }

        public void GetInfo()
        {
            Console.WriteLine("_______________________________________________________________________________________________________________");
            Console.WriteLine($"Id: {id} | Name: {name} | UPC: {UPC} | Manufacturer: {manufacturer} | Price: {price} | Shelf life: {shelf_life} | \n Amount: {amount} | City: {city} | _idcounter: {_idCounter}");
            Console.WriteLine("_______________________________________________________________________________________________________________");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Product pc = new Product(1, "Pavilion", 789456135, "Hp", 50.23, "24 months", 2, 100);
            Product laptop = new Product(2);
            laptop.Price = 32;
            double price = laptop.Price;
            Product lenovo = new Product(3, "Ideapad", 789456, "Lenovo");
            double y = 2.325;
            pc.Summing(out y);
            double x = 10.50;
            lenovo.Debiting(ref x);
            pc.GetInfo();
            laptop.GetInfo();
            lenovo.GetInfo();
            lenovo.GetHashCode();
            laptop.GetHashCode();
            Console.WriteLine(laptop.ToString());
            bool r = pc.Equals(lenovo);
            bool rr = lenovo.Equals(lenovo);
            Console.WriteLine($"laptop-pc : {r}\t pc-pc: {rr}");
            Console.WriteLine($"Количество: {Product.count}");
            Product.Array();
            //анонимный тип
            var user = new { lastname = "Kasperovich", name = "Artiom" };
            Console.WriteLine(user.name  + ' ' + user.lastname);
        }
    }
}
