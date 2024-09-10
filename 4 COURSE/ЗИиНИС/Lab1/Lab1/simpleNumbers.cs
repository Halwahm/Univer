using System.Collections.Generic;

namespace Lab1
{
    internal class simpleNumbers
    {
        public static string getSimpleNumbers(string aText, string bText)
        {
            string result;

            int a = aText == null ? 0 : int.Parse(aText);
            int b = bText == null ? 0 : int.Parse(bText);

            List<int> numb = new List<int> { };
            for (int i = 2; i <= b; i++)
            {
                numb.Add(i);
            }

            for (int i = 0; i < numb.Count; i++)
            {
                for (int j = 2; j < b; j++)
                    numb.Remove(numb[i] * j);
            }

            if (numb.Count != 0)
            {
                result = "Простые числа от " + a + " до " + b + ": ";
                int res=0;

                foreach (int w in numb)
                {
                    if (w > a)
                    {
                        result += w + ", ";
                        res++;
                    }
                }

                result += "\nКоличество простых чисел: " + res;
            }
            else
                result = "Простых чисел в данном диапозоне нет";
            
            return result;
        }
    }
}
