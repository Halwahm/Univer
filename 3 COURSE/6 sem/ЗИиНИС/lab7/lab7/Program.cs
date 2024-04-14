using System;

namespace lab7
{
    class Program
    {
        static void Main(string[] args)
        {
            string Xk = "101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010";
            Console.WriteLine(Xk.Length.ToString());
            string Xr = "10011";
            int kc = Xk.Length;
            int rc = 4;
            int nc = 112;

            int errorc;

            int[] masXk = new int[kc];
            StrInMas(masXk, Xk);

            int[] masXr = new int[Xr.Length];
            StrInMas(masXr, Xr);
            Console.WriteLine("___________________________________________________________");
            Console.WriteLine("Входная строка: " + Xk);
            Console.WriteLine("Порождающий полином: " + Xr);
            Console.WriteLine("k = {0}, r = {1}, n = {2}", kc, rc, nc);
            Console.WriteLine("___________________________________________________________");

            int[,] generationMatrix = new int[kc, nc];
            CreateGenerationMatrix(generationMatrix, masXr, kc, nc);

            Console.WriteLine("\nПорождающая матрица");
            OutMatrix(generationMatrix, kc, nc);

            CreateCanonicalMatrix(generationMatrix, kc, nc);

            Console.WriteLine("\nКаноническая матрица");
            OutMatrix(generationMatrix, kc, nc);

            int[,] checkMatrixc = new int[nc, rc];
            CreateCheckMatrix(checkMatrixc, generationMatrix, kc, nc);

            Console.WriteLine("\nПроверочная матрица");
            OutMatrix(checkMatrixc, nc, rc);
            //6.2

            int[] masXn = new int[nc];
            Shift(masXn, masXk, rc);

            //2.
            Console.WriteLine("\nДеление");
            SearchResidue(masXn, masXr);

            Console.WriteLine("Остаток (S-синдром):");
            OutMass(masXn);
            Console.WriteLine("\n");
            Console.WriteLine("Итоговая строка:");
            Shift(masXn, masXk, rc);
            OutMass(masXn);
            Console.WriteLine();
            int[] save = new int[nc];
            int prop = 0;
            foreach (int menuitem in masXn)
            {
                save[prop++] = menuitem;
            }

            Alternation(masXn);
            Console.WriteLine("\nСтрока после перемежения: ");
            OutMas(masXn);
            int error;
            int errorLenght;
            try
            {
                Console.WriteLine("\n\"Место ошибки 2");
                error = 2/*Convert.ToInt32(Console.ReadLine())*/;
                Console.WriteLine("Длина ошибки 3");
                errorLenght = 3/*Convert.ToInt32(Console.ReadLine())*/;
                for (int i = error; i < (error + errorLenght); i++)
                {
                    masXn[i] = (masXn[i] + 1) % 2;
                }
            }
            catch { }

            Console.WriteLine("\nСтрока с ошибками: ");
            OutMas(masXn);

            ReAlternation(masXn);
            Console.WriteLine("\nСтрока после re:перемежения: ");
            OutMas(masXn);

            SearchError(masXn, masXk, checkMatrixc, rc);
            Console.WriteLine("\n\nСтрока после исправления ошибок: ");
            OutMas(save);

            int[] masK = new int[90];
            int[] masK2 = new int[90];

            //RemoveCheckBits(masK2, masXn, checkMatrixc);
            Console.WriteLine("\n\nСтрока после удаления проверочных бит: ");
            Console.WriteLine(Xk);
            Console.WriteLine("");
            OutMassive(Xk);
        }
        static int[] Alternation(int[] masN)
        {

            int[,] matrix = new int[16, 7];
            //Получение матрицы
            for (int i = 0, m = 0; i < 16; i++)
            {
                for (int j = 0; j < 7; j++, m++)
                {
                    matrix[i, j] = masN[m];
                }
            }
            Console.WriteLine("\n\nПолученая матрица");
            OutMatrix(matrix, 16, 7);

            //Перемежение
            for (int i = 0, m = 0; i < 7; i++)
            {
                for (int j = 0; j < 16; j++, m++)
                {
                    masN[m] = matrix[j, i];
                }
            }

            return masN;
        }

        static int[] ReAlternation(int[] masN)
        {
            //int r = HemmingLength(k);
            int k = 16;
            int n = 7;

            int[,] matrix = new int[k, n];
            //Получение матрицы
            for (int j = 0, m = 0; j < n; j++)
            {
                for (int i = 0; i < k; i++, m++)
                {
                    matrix[i, j] = masN[m];
                }
            }
            Console.WriteLine("\n\nПолученая матрица");
            OutMatrix(matrix, k, n);

            //RE:Перемежение
            for (int j = 0, m = 0; j < k; j++)
            {
                for (int i = 0; i < n; i++, m++)
                {
                    masN[m] = matrix[j, i];
                }
            }

            return masN;
        }

        //Поиск синдрома
        static int[] Sindrom(int[,] CheckMatrix, int[] mas, int k)
        {

            int r = HemmingLength(k);
            int n = r + k;
            int[] sindrom = new int[r];



            for (int i = 0, l = 0; i < r; i++, l = 0)
            {
                for (int j = 0; j < k; j++)
                {
                    if (CheckMatrix[j, i] == 1 && mas[j] == 1) l++;
                    else sindrom[i] = 0;
                }
                if (l % 2 == 1) sindrom[i] = 1;
                else sindrom[i] = 0;
            }

            for (int i = 0; i < r; i++)
            {
                mas[i + k] = sindrom[i];
            }

            return mas;
        }

        //Считаем r (кол-во пров. симв.)
        static int HemmingLength(int k)
        {
            int r = (int)(Math.Log(k, 2) + 1.99f);
            return r;
        }


        static void OutMas(int[] mas)
        {
            for (int i = 0; i < mas.Length; i++)
            {
                Console.Write(mas[i]);
            }
        }
        //вывод матрицы
        public static int[] SearchError(int[] masXn, int[] masXr, int[,] checkMatrix, int r)
        {
            int n = masXn.Length;
            int k = n - r;

            int[] masXnSecond = new int[n];

            for (int i = 0; i < n; i++)
            {
                masXnSecond[i] = masXn[i];
            }

            Console.WriteLine("\nДеление");
            SearchResidue(masXnSecond, masXr);
            Console.WriteLine();
            Console.WriteLine("\n");
            Console.WriteLine("\nОстаток:");
            OutMass(masXnSecond);

            for (int i = 0; i < n; i++)
            {
                int coincidence = 0;
                for (int j = 0; j < r; j++)
                {
                    if (checkMatrix[i, j] == masXnSecond[k + j])
                    {
                        coincidence++;
                    }

                }
                if (coincidence == r)
                {
                    masXn[i] = (masXn[i] + 1) % 2;
                    break;
                }
            }


            return masXn;
        }

        public static int[] SearchResidue(int[] masXn, int[] masXr)
        {
            int end = masXn.Length - masXr.Length + 1;

            for (int i = 0; i < end; i++)
            {
                if (masXn[i] == 1)
                {
                    AddingMasMod2(masXn, masXr, i);
                    OutMass(masXn);
                }
            }
            Console.WriteLine("\n");
            return masXn;
        }

        //Сложение массивов по модулю 2 с опр. позиции
        public static int[] AddingMasMod2(int[] mas1, int[] mas2, int pos)
        {
            int end = pos + mas2.Length;

            for (int i = pos; i < end; i++)
            {
                mas1[i] = (mas1[i] + mas2[i - pos]) % 2;
            }
            return mas1;
        }

        //Смещение на массива r 
        public static int[] Shift(int[] shiftMas, int[] mas, int r)
        {

            for (int i = 0; i < mas.Length; i++)
            {

                shiftMas[i] = mas[i];
            }

            return shiftMas;
        }

        //Преобразование сторки в массив
        public static int[] StrInMas(int[] mas, string str)
        {
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] == 49)
                    mas[i] = 1;
                else mas[i] = 0;
            }
            return mas;
        }

        //Создание Порождающей матрицы 
        static int[,] CreateGenerationMatrix(int[,] generationMatrix, int[] mas, int k, int n)
        {
            //Заполняем первую строку в проверочной матрице
            for (int i = 0; i < n; i++)
            {
                if (i < mas.Length)
                {
                    generationMatrix[0, i] = mas[i];
                }
                else
                {
                    generationMatrix[0, i] = 0;
                }
            }

            //Сдвигаем каждую строки вправо от предыдущей
            for (int i = 1; i < k; i++)
            {
                for (int j = 0; j < n - 1; j++)
                {
                    generationMatrix[i, j + 1] = generationMatrix[i - 1, j];
                }
                generationMatrix[i, 0] = generationMatrix[i - 1, n - 1];
            }



            return generationMatrix;
        }

        //Приведение порождающей матрицы к каноническому виду
        static int[,] CreateCanonicalMatrix(int[,] generationMatrix, int k, int n)
        {
            //Перебираем строки для преведению к каноническому виду
            for (int i = 0; i < k; i++)
            {
                int i2 = i + 1;
                //Перебираем элементы строки, но только до k-элемента
                for (int j = i + 1; j < k; j++)
                {
                    //если мы нашли единицу в строке, то...
                    if (generationMatrix[i, j] == 1)
                    {
                        //перебираем этот столбец, пока не найдем единицу
                        for (; i2 < k; i2++)
                        {
                            bool repeat = false;
                            //Если нашли, то складываем обе строки
                            if (generationMatrix[i2, j] == 1)
                            {
                                for (int j2 = j - 1; j2 > 0; j2--)
                                {
                                    //Проверяем, есть ли до этой 1 еще 1, если есть то эту строку пропускаем
                                    if (generationMatrix[i2, j2] == 1)
                                    {
                                        repeat = true;
                                    }
                                }
                                if (repeat)
                                    continue;
                                //Console.WriteLine(i + " " + i2);
                                AddingLinesMatrixMod2(generationMatrix, i, i2, n);
                                i2++;
                                break;
                            }
                        }
                    }
                }
            }

            return generationMatrix;
        }
        //Преобразование канонической матрицы в проверочную
        static int[,] CreateCheckMatrix(int[,] checkMatrix, int[,] generationMatrix, int k, int n)
        {
            int r = n - k;

            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < r; j++)
                {
                    checkMatrix[i, j] = generationMatrix[i, k + j];
                }
            }

            for (int i = k; i < n; i++)
            {
                for (int j = 0; j < r; j++)
                {
                    if (j == i - k)
                    {
                        checkMatrix[i, j] = 1;
                    }
                    else
                    {
                        checkMatrix[i, j] = 0;
                    }
                }
            }

            return checkMatrix;
        }

        //Сложение строк матрицы
        public static int[,] AddingLinesMatrixMod2(int[,] matrix, int str1, int str2, int lengthString)
        {
            //Console.WriteLine(str1 + " и " + str2);
            for (int i = 0; i < lengthString; i++)
            {
                matrix[str1, i] = (matrix[str1, i] + matrix[str2, i]) % 2;
            }
            return matrix;
        }

        //вывод матрицы
        public static void OutMatrix(int[,] matrix, int k, int n)
        {
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write(matrix[i, j]);
                    //if (j + 1 == k) Console.Write("|");
                }
                Console.WriteLine();
            }
        }

        static void OutMassive(string Xk)
        {
            Console.WriteLine(Xk);
        }
        //вывод одномерного массива
        public static void OutMass(int[] mas)
        {
            Console.WriteLine();
            for (int i = 0; i < mas.Length; i++)
            {
                //if (i == k) Console.Write("|");
                Console.Write(mas[i]);

            }
            //Console.WriteLine("\n");
        }
    }
}