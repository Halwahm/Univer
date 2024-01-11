namespace lab5
{
    public partial class cvitantion
    {
        consNote consNote;
        public cvitantion(DateTime date, int price, string organizationname) 
            : base(date, price, organizationname)   { consNote = new consNote(1, "Caffee.by", "Sosedi",
                "20122020", "Coffee1", (EnumOfNames)price); }
    }
}
