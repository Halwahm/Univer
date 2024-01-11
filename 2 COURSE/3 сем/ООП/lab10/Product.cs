namespace LW10
{
    partial class Product
    {
        const string Type = "product"; // поле константа
        public static readonly int NumberForHesh;
        public int Id { get; set; }
        public String? Name { get; set; }
        public int UPC { get; set; }
        public String? Producer { get; set; }
        public int Amount { get; set; }
        public int ShelfLife { get; set; }
        public int Price { get; set; }


        public override int GetHashCode()
        {
            Random x = new Random();
            return Id * 3 * x.Next(100) * NumberForHesh;
        }

        static Product() { NumberForHesh = 10; }
        public Product(int InputId, string? InputName, int InputPrice, int InputAmount, string? InputProd)
        {
            Id = InputId;
            Name = InputName;
            Price = InputPrice;
            Amount = InputAmount;
            Producer = InputProd;
            Id = this.GetHashCode();
        }

        protected float[] msf = new float[10];
        public float this[int j]
        {
            get
            {
                return msf[j];
            }
            set
            {
                msf[j] = value;
            }
        }
        public static void ClassInfo()
        {
            Console.WriteLine("Статическая информация о классе");
            Console.WriteLine("Это класс продукт");
            Console.WriteLine("Его тип: " + Type);
            Secret();
        }
        private static void Secret()
        {
            Console.WriteLine("Закрытый конструктор");
        }
        public void TotalAmountProduct()
        {
            Console.WriteLine($"Общая сумма продукта {Price * Amount}");
        }
        static void Menu()
        {
            Console.WriteLine("Ввод данных");

        }
        public void Interface()
        {

            Menu();
            Console.WriteLine("Ввести имя товара");
            Name = Console.ReadLine();
            Console.WriteLine("Ввести UPC(число) товара");
            UPC = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Ввести производителя товара");
            Producer = Console.ReadLine();
            Console.WriteLine("Ввести цену(число) товара");
            Price = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Ввести количество(число) товара");
            Amount = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Ввести срок хранения(колл дней) товара");
            ShelfLife = Convert.ToInt32(Console.ReadLine());

        }
        public void ShowInfo()
        {
            Console.WriteLine(Name + " имя товара");
            Console.WriteLine(UPC + " UPC товара");
            Console.WriteLine(Producer + " производитель товара");
            Console.WriteLine(Price + " цена товара");
            Console.WriteLine(Amount + " количество товара");
            Console.WriteLine(ShelfLife + " срок хранения товара");
            Console.WriteLine(Id + " ID");
        }
        public override string ToString()
        {
            return $"{Name}";
        }
        //override - Если было использовано это ключевое слово, на выходе будет использоваться переопределенный метод.
        //Вне зависимости от того, как было оформлено обращение к методу.
    }
}