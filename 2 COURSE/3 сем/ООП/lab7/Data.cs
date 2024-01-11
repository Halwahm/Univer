namespace lab7
{
    public class Data
    {
        private string _date;
        public string Date
        {
            get => _date;
            set => _date = value;
        }

        private int _price;
        public int Price
        {
            get => _price;
            set => _price = value;
        }

        public string _organizationName;
        public string OrganizationName
        {
            get => _organizationName;
            set => _organizationName = value;
        }

        public Data(string date, int price, string organizename)
        {
            _date = date;
            _price = price;
            _organizationName = organizename;
        }

        public override string ToString()
        {
            return $"Document data\n Date: {_date}\t Price: {_price}\t OrgName: {_organizationName}";
        }
    }
}
