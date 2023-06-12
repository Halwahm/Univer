using System.Text;

namespace lab1
{
    public static class Program
    {
        static void Main(string[] args)
        {
            //TYPES

            //1a
            bool a = true;
            Console.WriteLine("bool = " + a);

            byte b = 255;
            Console.WriteLine("byte = " + b);

            sbyte c = 127;
            Console.WriteLine("sbyte = " + c);

            char d = 'o';
            Console.WriteLine("char = " + d);

            decimal e = 6.974553m;
            Console.WriteLine("decimal = " + e);

            double f = 5.0855676567;
            Console.WriteLine("double = " + f);

            float g = 3.667f;
            Console.WriteLine("float = " + g);

            int h = 2147483647;
            Console.WriteLine("int = " + h);

            uint i = 4294967295;
            Console.WriteLine("uint = " + i);

            long l = 9223372036854775807;
            Console.WriteLine("long = " + l);

            ulong m = 18446744073709551615;
            Console.WriteLine("ulong = " + m);

            short n = 32767;
            Console.WriteLine("short = " + n);

            ushort o = 65535;
            Console.WriteLine("ushort = " + o);

            //1b
            float p = 4.56f;
            float q = 10.66f;
            byte r = (byte)(p + q); 
            sbyte x = (sbyte)(p + q);
            short y = (short)(p + q);
            int z = (int)p;
            long aa = (long)(p + q);
            Console.WriteLine("float-->byte: " + r);
            Console.WriteLine("float-->sbyte: " + x);
            Console.WriteLine("float-->short: " + y);
            Console.WriteLine("float-->int: " + z);
            Console.WriteLine("float-->long: " + aa);

            byte s = 8;
            short t = s;
            int u = t;
            long v = u;
            float w = v;
            Console.WriteLine("byte-->short-->int-->long-->float: " + w);

            Console.Write("Введите число: ");
            int bb = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Число: " + bb);

            //1c
            int cc = 5;
            object dd = cc; 
            int ee = (int)dd;
            Console.WriteLine("ее: " + ee);

            float ff = 5.948548f;
            object gg = ff;
            float hh = (float)gg;
            Console.WriteLine("hh: " + hh);

            //1d
            var ii = 2.68;
            var jj = 3.84;
            var kk = ii + jj;
            Console.WriteLine("kk: " + kk);

            //1e
            int? ll = null;
            int? mm = null;
            Console.WriteLine($"Сравнение nullable = {ll == mm}");

            //1f
            /* var num1 = 1;
             num1 = true;
             Console.WriteLine(num1);*/

            //STRING

            //2a
            string nn = "nn";
            string oo = "nn";
            string pp = "pp";
            Console.WriteLine($"Сравнение 1 и 2 строки: {nn == oo}");
            Console.WriteLine($"Сравнение 2 и 3 строки: {pp == oo}");

            //2b
            string qq = "the first string";
            string rr = "the second string";
            string ss = "the third string";
            string[] tt;
            Console.WriteLine($"Сцепление строк: {String.Concat(qq, " and " + rr)}");
            Console.WriteLine($"Копирование строки: {String.Copy(rr)}");
            Console.WriteLine($"Выделение подстроки: {ss.Substring(9)}");
            Console.WriteLine($"Разделение строки на слова: ");
            tt = qq.Split();
            for (int iii = 0; iii < tt.Length; iii++)
            {
                Console.WriteLine(tt[iii]);
            }
            Console.WriteLine($"Вставка подстроки в заданную позицию: {rr.Insert(4, qq)}");
            Console.WriteLine($"Удаление заданной подстроки: {ss.Remove(4)}");

            //2c
            string uu = "";
            string? vv = null;
            Console.WriteLine($"IsNullOrEmpty: {string.IsNullOrEmpty(uu)}");
            Console.WriteLine($"IsNullOrEmpty: {string.IsNullOrEmpty(vv)}");
            Console.WriteLine($"1 строка = 2 строка: {uu == vv}");
            Console.WriteLine($"Сцепление: {String.Concat(uu, vv)}");

            //2d
            StringBuilder ww = new StringBuilder("bbcd");
            ww.Append("e");
            ww.Insert(0, "a");
            ww.Remove(2, 1);
            Console.WriteLine($"StringBuilder: {ww}");

            //ARRAY

            //3a
            int[,] xx = { { 1, 1, 1 }, { 0, 0, 0 }, { 1, 0, 1 } };
            int rows = xx.GetUpperBound(0) + 1;
            int columns = xx.Length / rows; //либо xx.GetUpperBound(1) + 1;
            for (int rrr = 0; rrr < rows; rrr++)
            {
                for (int ccc = 0; ccc < columns; ccc++)
                {
                    Console.Write($"{xx[rrr, ccc]} \t");
                }
                Console.WriteLine();
            }

            //3b
            string[] zz = { "abc", "def", "ghi" };
            Console.WriteLine($"Длина массива: {zz.Length}");
            foreach (string oooo in zz)
            {
                Console.WriteLine(oooo);
            }
            zz[1] = "ddeeff";
            Console.WriteLine("--------");
            foreach (string oooo in zz)
            {
                Console.WriteLine(oooo);
            }

            //3c
            float[][] lll = new float[3][];
            lll[0] = new float[] { 1, 3 };
            lll[1] = new float[] { 1, 3, 5 };
            lll[2] = new float[] { 1, 3, 4, 7 };

            foreach (float[] row in lll)
            {
                foreach (int number in row)
                {
                    Console.Write($"{number} \t");
                }
                Console.WriteLine();
            }

            //3d
            var array = new object[0];
            var str = "";

            //TUPLE

            //4a
            (int, string, char, string, ulong) xxx = (5, "efgh", 'a', "abcd", 12345);

            //4b
            Console.WriteLine(xxx);
            Console.WriteLine(xxx.Item1);
            Console.WriteLine(xxx.Item3);
            Console.WriteLine(xxx.Item5);

            //4c
            (int www, string hhh, char ppp, string ttt, ulong jjj) = xxx;
            //(var www, var hhh, var ppp, var ttt, var jjj) = xxx;
            //var (www, hhh, ppp, ttt, jjj) = xxx;
            Console.WriteLine($"items: {www} {ttt}");
            (int wwwww, _, char hhhh, string pppp, ulong jjjj) = xxx;

            //4d
            (int, string, char, string, ulong) mmmm = (5, "efh", 'f', "abd", 1245);
            (int, string, char, string, ulong) ssss = (5, "efh", 'v', "abd", 1245);
            if (mmmm == ssss)
                Console.WriteLine("true");
            
            else
                Console.WriteLine("false");

            //FUNC

            (int, int, int, char) Localfunction(int[] numbers, string str1)
            { 
                int dddd = 0;
                int zzzz = Int32.MaxValue;
                int sum = 0;

                for (int iiii = 0; iiii < numbers.Length; iiii++)
                {
                    if (numbers[iiii] > dddd)
                    {
                        dddd = numbers[iiii];
                    }
                    if (numbers[iiii] < zzzz)
                    {
                        zzzz = numbers[iiii];
                    }
                    sum += numbers[iiii];
                }
                char smb = str1[0];
                var tuple1 = (dddd, zzzz, sum, smb);
                return tuple1;
            }
            int[] nums = new int[4];
            nums[0] = 20;
            nums[1] = 30;
            nums[2] = 40;
            nums[3] = 100;
            string str2 = "bcd";
            Console.WriteLine(Localfunction(nums, str2));

            //(UN)CHECKED

            int z22 = 100, z23 = 200;
            int localfunction2()
            {
                int z1 = Int32.MaxValue;
                unchecked
                {
                    z1 = z1 + z22;
                    Console.WriteLine(z1);
                }
                return z1;
            }
            int localfunction1()
            {
                int z1 = Int32.MaxValue;
                checked 
                {
                    z1 = z1 + z23;
                    Console.WriteLine(z1);
                }
                return z1;
            }
            Console.WriteLine(localfunction2());
            //Console.WriteLine(localfunction1());
        }
    }
}

