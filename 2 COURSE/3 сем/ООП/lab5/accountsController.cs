namespace lab5
{
    internal class accountsController
    {
        public void FoundByName(accounting account, string name)
        {
            foreach (var value in account.Accounts.Where(value => value.Name.Equals(name)))
            {
                switch (value)
                {
                    case consNote:
                        Console.WriteLine($"Found doc with name: {value.Name} and price: {value.Price}");
                        break;
                }
            }
        }

        public void CheckCount(accounting account)
        {
            Console.WriteLine($"Checks count: {account.Accounts.Count}");
        }

        public void SumCheck(accounting account)
        {
            int sum = 0;
            foreach(var value in account.Accounts)
                sum += (int)value.Price;

            Console.WriteLine($"Суммарная стоимость продукции по накладным = {sum}");
        }
    }
}
