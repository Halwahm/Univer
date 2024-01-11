using System;
using System.Collections.Generic;
using System.Text;

namespace lab3
{
    static class StatisticOperations
    {
        public static int Max(this dlist set) 
        {
            int len = set.GetItemByIndex(0).Length;
            foreach (string item in set.mylist)
            {
                if (len < item.Length)
                    len = item.Length;
            }
            return len;
        }

        public static int Maxstr(this string set)
        {
            string input = set.ToString();
            string[] str = input.Split(new Char[] { ' ', ',', '.', ':', '!', '?', ';' }, StringSplitOptions.RemoveEmptyEntries);
            int maxlen = 0;
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i].Length > maxlen)
                    maxlen = str[i].Length;
            }
            return maxlen;
        }

        public static int Min(this dlist set) 
        {
            int len = set.GetItemByIndex(0).Length;
            foreach (string item in set.mylist)
            {
                if (len > item.Length)
                    len = item.Length;
            }
            return len;
        }

        public static int Minstr(this string set)
        {
            string input = set.ToString();
            string[] str = input.Split(new Char[] { ' ', ',', '.', ':', '!', '?', ';' }, StringSplitOptions.RemoveEmptyEntries);
            int minlen = 10100;
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i].Length < minlen)
                    minlen = str[i].Length;
            }
            return minlen;
        }

        public static int Dif(this dlist set) => Max(set) - Min(set);

        public static int Difstr(this string set) => Maxstr(set) - Minstr(set);

        public static int CountOfWords(this string str) 
        {
            int count = 0;
            string[] words = str.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            count += words.Length;
            return count;
        }

        public static int Sum(this dlist set) 
        {
            int len = 0;
            foreach (string item in set.mylist)
            {
                len += item.Length;
            }
            return len;
        }

        public static int CountOfBigLetters(this dlist set)
        {
            int count = 0;
            foreach (string item in set.mylist)
            {
                if (item[0] == item.ToUpper()[0])
                {
                    count++;
                }
            }
            return count;
        }

        public static int CountOfRepeat(this dlist set)
        {
            int count = 0;
            var a = set.mylist.Count();
            for (int i = 0; i < a; i++)
            {
                for (int j = i + 1; j < a; j++)
                {
                    if (set.mylist[i] == set.mylist[j])
                        count++;
                }
            }
            return count;
        }
    }
}
