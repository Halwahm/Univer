namespace lab5
{
    public sealed class consNote: document, IDate //накладная
    {
        public string Owner;
        public string Customer;
        public bool statusShip;
        public string Name;
        public EnumOfNames Price;

        string IDate.PrintDatе()
        {
            Console.WriteLine($"Дата поставки: {Date}");
            return "";
        }

        public void performed() //выполнено
        {
            statusShip = true;
            Console.WriteLine("done ");
        }

        public void imperformed() //не выполнено
        {
            statusShip = false;
            Console.WriteLine("not done ");
        }

        public override void reading()
        {
            _CountRead++;
            if (_CountRead < 0)
                Console.WriteLine("Кол-во прочтений не может быть < 0, ведь ты читаешь это сейчас)");
            else if (_CountRead >= 0)
            Console.WriteLine($"Кто-то уже читал этот документ, поэтому, кол-во чтений: {_CountRead})");
        }

        public consNote(int countRead, string owner, string customer, string date,
           string name, EnumOfNames price) : base(countRead, date)
        {
            _CountRead = countRead;
            Owner = owner;
            Customer = customer;
            Date = date;
            Name = name;
            Price = price;
        }

        public override string ToString()
        {
            Console.WriteLine($"Owner: {Owner} \t Customer: {Customer}");
            return "";
        }
    }
}
