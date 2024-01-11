namespace lab5
{
    public class accounting //бухгалтерия
    {
        private List<consNote> _accounts;

        public accounting()
        {
            _accounts = new List<consNote>();
        }

        public List<consNote> Accounts { 
            get => _accounts; 
            set => _accounts = value; 
        }

        public void Add(object name)
        {
            if (name is consNote data)
            {
                _accounts.Add(data);
            }
        }

        public void Remove(object name)
        {
            if (name is consNote data)
            {
                _accounts.Remove(data);
            }
        }

        public void Print()
        {
            foreach (var value in _accounts)
            {
                switch (value)
                {
                    case consNote:
                        Console.WriteLine($"Object with name: {value.Name}");
                        break;
                    default:
                        Console.WriteLine($"Name: {value.Name}");
                        break;
                }
            }
        }
    }
}
