using System;

namespace ЛР__5
{
    class Program
    {//генерируется сообщение
        static void IterativeMatrix(int height, int width)
        {
            Random rand = new Random();
            int[] itog = new int[16];//длинна инф слова
            int[] save = new int[16];

            int[,] generateMessage = new int[height, width];
            int[] sc = new int[width];

            int eachRow, i, j;
            int[] gorParity = new int[width];
            int[] verParity = new int[height];
            int result = 0;
            for (i = 0; i < width; i++) sc[i] = 0;
            for (i = 0; i < height; i++)
            {
                eachRow = 0;
                for (j = 0; j < width; j++)
                {

                    generateMessage[i, j] = rand.Next(0, 2);
                    Console.Write(generateMessage[i, j] + "  ");
                    eachRow += generateMessage[i, j];
                    result += generateMessage[i, j];
                    gorParity[i] = eachRow;
                    sc[j] += generateMessage[i, j];
                }
                int l = eachRow % 2;
                Console.WriteLine(" |" + l);

            }
            for (i = 0; i < width; i++)
                Console.Write("---");
            Console.Write("\n");
            for (i = 0; i < width; i++)
            {
                int z = sc[i] % 2;
                verParity[i] = z;
                Console.Write(z + "  ");
            }
            Console.WriteLine("\n");

            int itogreg = 0;
            int itogregd = 0;
            Console.Write("Xn=  ");
            for (i = 0; i < width; i++) sc[i] = 0;
            for (i = 0; i < height; i++)
            {

                for (j = 0; j < width; j++)
                {
                    Console.Write(generateMessage[i, j]);
                    itog[itogreg++] = generateMessage[i, j];
                    save[itogregd++] = generateMessage[i, j];
                }

            }
            // вертикальный паритет
            int o = 0;
            int[] savegor = new int[4];
            Console.Write("  ");
            foreach (int item in gorParity)
            {
                int l = item % 2;
                savegor[o++] = l;

                Console.Write(l);
            }
            int f = 0;
            int[] savever = new int[4];
            // горизонтальный паритет
            Console.Write("  ");
            Array.Reverse(verParity);
            foreach (int item in verParity)
            {
                savever[f++] = item;
                Console.Write(item);
            }
            int res = result % 2;
            Console.WriteLine(" " + res);
            foreach (int item in itog)
            {
                Console.Write(item);
            }
            //обработка ошибок    
            try
            {
                Console.WriteLine();
                var random = new Random();
                int error = random.Next(0, itog.Length);
                Console.WriteLine("Позиция ошибки:  " + error);
                if (itog[error] == 1) itog[error] = 0;
                else itog[error] = 1;
            }
            catch { }
            Console.Write("Yn=  ");
            foreach (int item in itog)
            {
                Console.Write(item);
            }
            Console.WriteLine();
            int iter = 0;
            for (i = 0; i < width; i++) sc[i] = 0;
            for (i = 0; i < height; i++)
            {
                eachRow = 0;
                for (j = 0; j < width; j++)
                {

                    generateMessage[i, j] = itog[iter++];
                    Console.Write(generateMessage[i, j] + "  ");
                    eachRow += generateMessage[i, j];
                    sc[j] += generateMessage[i, j];
                    gorParity[i] = eachRow;
                }
                int l = eachRow % 2;
                Console.WriteLine(" |" + l);

            }

            for (i = 0; i < width; i++)
                Console.Write("---");
            Console.Write("\n");
            for (i = 0; i < width; i++)
            {
                int z = sc[i] % 2;
                verParity[i] = z;
                Console.Write(z + "  ");
            }
            Console.WriteLine("\n");

            Console.WriteLine("Сравниваем паритеты:");
            Console.Write("  ");
            foreach (int item in gorParity)
            {
                int l = item % 2;

                Console.Write(l);
            }
            // горизонтальный паритет
            Console.Write("  ");
            Array.Reverse(verParity);
            foreach (int item in verParity)
            {

                Console.Write(item);
            }
            Console.WriteLine();
            Console.Write("  ");
            foreach (int it in savegor)
            {
                Console.Write(it);
            }
            Console.Write("  ");
            // Array.Reverse(savever);
            foreach (int it in savever)
            {
                Console.Write(it);
            }
            Console.WriteLine();
            Console.WriteLine("Исправляем, строка без ошибки:");

            Console.Write("Xn=  ");
            foreach (int item in save)
            {
                Console.Write(item);
            }

        }

        static void IterativeMatrix2(int height, int width)
        {

            Random rand = new Random();
            int[] itog = new int[16];
            int[] save = new int[16];

            int[,] a = new int[height, width];

            int[] sc = new int[width];
            int s, i, j;
            int[] gor = new int[width];
            int[] ver = new int[height];
            int result = 0;
            for (i = 0; i < width; i++) sc[i] = 0;
            for (i = 0; i < height; i++)
            {
                s = 0;
                for (j = 0; j < width; j++)
                {

                    a[i, j] = rand.Next(0, 2);
                    Console.Write(a[i, j] + "  ");
                    s += a[i, j];
                    result += a[i, j];

                    sc[j] += a[i, j];
                }
                int l = s % 2;
                Console.WriteLine(" |" + l);

            }
            for (i = 0; i < width; i++)
                Console.Write("---");
            Console.Write("\n");
            for (i = 0; i < width; i++)
            {
                int z = sc[i] % 2;
                ver[i] = z;
                Console.Write(z + "  ");
            }
            Console.WriteLine("\n");

            int itogreg = 0;
            int itogregd = 0;
            Console.Write("Xn=  ");
            for (i = 0; i < width; i++) sc[i] = 0;
            for (i = 0; i < height; i++)
            {

                for (j = 0; j < width; j++)
                {
                    Console.Write(a[i, j]);
                    itog[itogreg++] = a[i, j];
                    save[itogregd++] = a[i, j];
                }
            }

            try
            {
                Console.WriteLine();
                var random = new Random();
                int error = random.Next(0, itog.Length);
                Console.WriteLine("Позиция ошибки:  " + error);
                if (itog[error] == 1) itog[error] = 0;
                else itog[error] = 1;
            }
            catch { }
            Console.Write("Yn=  ");
            foreach (int item in itog)
            {
                Console.Write(item);
            }
            Console.WriteLine();
            int iter = 0;
            for (i = 0; i < width; i++) sc[i] = 0;
            for (i = 0; i < height; i++)
            {
                s = 0;
                for (j = 0; j < width; j++)
                {

                    a[i, j] = itog[iter++];
                    Console.Write(a[i, j] + "  ");
                    s += a[i, j];
                    sc[j] += a[i, j];
                    //gor[i] = s;
                }
                int l = s % 2;
                Console.WriteLine(" |" + l);

            }

            for (i = 0; i < width; i++)
                Console.Write("---");
            Console.Write("\n");
            for (i = 0; i < width; i++)
            {
                int z = sc[i] % 2;
                ver[i] = z;
                Console.Write(z + "  ");
            }
            Console.WriteLine("\n");

            Console.Write("Xn=  ");
            foreach (int item in save)
            {
                Console.Write(item);
            }

        }
        //итеративная матрица
        static void IterativeMatrixWithDepth(int height, int width, int depth)
        {

            Random rand = new Random();
            int[] itog = new int[16];

            int[] sc = new int[width];

            int[] result = new int[16];
            int itogers = 0;
            for (int i = 0; i < depth; i++) sc[i] = 0;

            int[,,] array = new int[height, width, depth];
            for (int i = 0; i < array.GetLength(0); i++)
            {

                for (int j = 0; j < array.GetLength(1); j++)
                {

                    int slow = 0;
                    for (int k = 0; k < array.GetLength(2); k++)
                    {

                        array[i, j, k] = rand.Next(0, 2);
                        slow += array[i, j, k];
                        result[itogers++] += array[i, j, k];
                        Console.Write(array[i, j, k]);
                        sc[k] += array[i, j, k];

                    }

                    int l = slow % 2;
                    Console.WriteLine(" |" + l);

                }
                Console.WriteLine("---");
                for (int d = 0; d < depth; d++)
                {
                    int z = sc[d] % 2;

                    Console.Write(z + "");
                    sc[d] = 0;
                }

                Console.WriteLine();
                Console.WriteLine();

            }

            Console.WriteLine("Паритет 4 - 5 группы:");

            for (int i = 0; i < array.GetLength(0); i++)
            {

                for (int j = 0; j < array.GetLength(1); j++)
                {

                    for (int k = 0; k < array.GetLength(2); k++)
                    {
                        Console.Write(array[i, j, k]);
                    }
                }
                Console.WriteLine(" ");
            }

            int first = result[0] + result[5] + result[10] + result[15];
            int firstm = first % 2;
            int second = result[1] + result[6] + result[11] + result[12];
            int secondm = second % 2;
            int third = result[2] + result[7] + result[8] + result[13];
            int thirdm = third % 2;
            int fourth = result[3] + result[4] + result[9] + result[14];
            int fourthm = fourth % 2;

            int firstf = result[0] + result[7] + result[10] + result[13];
            int firstmf = firstf % 2;
            int secondf = result[1] + result[4] + result[11] + result[14];
            int secondmf = secondf % 2;
            int thirdf = result[2] + result[5] + result[8] + result[15];
            int thirdmf = thirdf % 2;
            int fourthf = result[3] + result[6] + result[9] + result[12];
            int fourthmf = fourthf % 2;

            Console.WriteLine("Паритет 5 группы:  " + firstm + secondm + thirdm + fourthm);
            Console.WriteLine("Паритет 4 группы:  " + firstmf + secondmf + thirdmf + fourthmf);

            int[] sresult = new int[16];
            Console.Write("Xn =  ");
            int inh = 0;
            foreach (var item in result)
            {
                sresult[inh++] = item;
                Console.Write(item);
            }

            try
            {
                Console.WriteLine();
                var random = new Random();
                int error = random.Next(0, itog.Length);
                Console.WriteLine("Позиция ошибки:  " + error);
                if (result[error] == 1) result[error] = 0;
                else result[error] = 1;
            }
            catch { }

            Console.Write("Yn =  ");
            foreach (var item in result)
            {
                Console.Write(item);
            }

            Console.WriteLine();

            int itogers2 = 0;
            int[] result2 = new int[16];
            int iter = 0;
            for (int i = 0; i < array.GetLength(0); i++)
            {

                for (int j = 0; j < array.GetLength(1); j++)
                {

                    int slow = 0;
                    for (int k = 0; k < array.GetLength(2); k++)
                    {

                        array[i, j, k] = result[iter++];
                        slow += array[i, j, k];
                        result2[itogers2++] += array[i, j, k];
                        Console.Write(array[i, j, k]);
                        sc[k] += array[i, j, k];

                    }
                    int l = slow % 2;
                    Console.WriteLine(" |" + l);
                }
                Console.WriteLine("---");
                for (int d = 0; d < depth; d++)
                {
                    int z = sc[d] % 2;

                    Console.Write(z + "");
                    sc[d] = 0;
                }

                Console.WriteLine();
                Console.WriteLine();


            }

            first = result2[0] + result2[5] + result2[10] + result2[15];
            firstm = first % 2;
            second = result2[1] + result2[6] + result2[11] + result2[12];
            secondm = second % 2;
            third = result2[2] + result2[7] + result2[8] + result2[13];
            thirdm = third % 2;
            fourth = result2[3] + result2[4] + result2[9] + result2[14];
            fourthm = fourth % 2;

            firstf = result2[0] + result2[7] + result2[10] + result2[13];
            firstmf = firstf % 2;
            secondf = result2[1] + result2[4] + result2[11] + result2[14];
            secondmf = secondf % 2;
            thirdf = result2[2] + result2[5] + result2[8] + result2[15];
            thirdmf = thirdf % 2;
            fourthf = result2[3] + result2[6] + result2[9] + result2[12];
            fourthmf = fourthf % 2;

            Console.WriteLine("Паритет 5 группы:  " + firstm + secondm + thirdm + fourthm);
            Console.WriteLine("Паритет 4 группы:  " + firstmf + secondmf + thirdmf + fourthmf);

            Console.WriteLine("Исправленное сообщение:");

            Console.Write("Xn =  ");
            foreach (var item in sresult)
            {
                Console.Write(item);
            }
        }

        static void Main()
        {
            IterativeMatrix(4, 4);
            Console.WriteLine();
            Console.WriteLine("______________________________________________________________________________");
            Console.WriteLine();
            IterativeMatrix2(8, 2);
            Console.WriteLine();
            Console.WriteLine("______________________________________________________________________________");
            Console.WriteLine();
            Console.WriteLine(); Console.WriteLine();
            Console.WriteLine("Размер 4 : 2 : 2");
            Console.WriteLine(); Console.WriteLine();
            IterativeMatrixWithDepth(4, 2, 2);
            Console.WriteLine();
            Console.WriteLine("______________________________________________________________________________");
            Console.WriteLine(); Console.WriteLine();
            IterativeMatrixWithDepth(2, 4, 2);
            Console.WriteLine();
            Console.WriteLine("______________________________________________________________________________");
        }
    }
}
