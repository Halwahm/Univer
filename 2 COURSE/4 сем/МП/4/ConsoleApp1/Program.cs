class Programm
{
    static int Minimum(int a, int b, int c) => (a = a < b ? a : b) < c ? a : c;

    static int LevenshteinDistance(string text1, int len1, string text2, int len2)
    {
        if (len1 == 0)
        {
            return len2;
        }

        if (len2 == 0)
        {
            return len1;
        }

        var substitutionCost = 0;
        if (text1[len1 - 1] != text2[len2 - 1])
        {
            substitutionCost = 1;
        }

        var deletion = LevenshteinDistance(text1, len1 - 1, text2, len2) + 1;
        var insertion = LevenshteinDistance(text1, len1, text2, len2 - 1) + 1;
        var substitution = LevenshteinDistance(text1, len1 - 1, text2, len2 - 1) + substitutionCost;

        return Minimum(deletion, insertion, substitution);
    }

    static void Main(string[] args)
    {
        Console.Write("Первое слово: Ель");
        string s1 = "Ель";
        Console.Write("\tВторое слово: Дрель");
        string s2 = "Дрель";

        Console.WriteLine("\nРасстояние Левенштейна: {0}", LevenshteinDistance(s1, 3, s2, 5));
        Console.ReadLine();
    }
}