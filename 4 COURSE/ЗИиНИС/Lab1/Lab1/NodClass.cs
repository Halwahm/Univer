namespace Lab1
{
    internal class nodCreator
    {
        public static int nodeResult;

        public static string getNod(string aText, string bText, string? cText)
        {
            int a = aText == null ? 0 : int.Parse(aText);
            int b = bText == null ? 0 : int.Parse(bText);
            int c = cText == null ? 0 : int.Parse(cText);

            GetNodResult(a, b);

            if (c != 0)
            {
                GetNodResult(nodeResult, c);
            }

            return "НОД: " + nodeResult;
        }

        static void GetNodResult(int a, int b)
        {
            if (a != 0 && b != 0)
            {
                if (a > b)
                {
                    a = a % b;
                }
                else
                {
                    b = b % a;
                }
                GetNodResult(a, b);
            }
            else
                nodeResult = a + b;
        }
    }
}
