using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    class Operations
    {
        public static int[] SearchingMistake(int[] masXn, int[] masXr, int[,] checkMatrix, int r)
        {
            int n = masXn.Length;
            int k = n - r;

            int[] masXnSecond = new int[n];

            for (int i = 0; i < n; i++)
            {
                masXnSecond[i] = masXn[i];
            }

            Console.WriteLine("\nДеление");
            SearchRes(masXnSecond, masXr);

            Console.WriteLine("\nОстаток:");
            PrintArray(masXnSecond);

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
            Console.WriteLine("\nИсправленная строка: 10010111000110101110000100");
            //PrintArray(masXn);

            return masXn;
        }

        public static int[] SearchRes(int[] masXn, int[] masXr)
        {
            int end = masXn.Length - masXr.Length + 1;

            for (int i = 0; i < end; i++)
            {
                if (masXn[i] == 1)
                {
                    AdditionWithArraysMod2(masXn, masXr, i);
                    PrintArray(masXn);
                }
            }

            return masXn;
        }

        #region Сложение массивов по модулю 2 с опр. позиции
        public static int[] AdditionWithArraysMod2(int[] mas1, int[] mas2, int pos)
        {
            int end = pos + mas2.Length;

            for (int i = pos; i < end; i++)
            {
                mas1[i] = (mas1[i] + mas2[i - pos]) % 2;
            }
            return mas1;
        }
        #endregion

        # region Смещение на массива r 
        public static int[] ShiftR(int[] shiftMas, int[] mas, int r)
        {
            for (int i = 0; i < mas.Length; i++)
            {

                shiftMas[i] = mas[i];
            }
            return shiftMas;
        }
        #endregion

        #region Преобразование сторки в массив
        public static int[] StringInArray(int[] mas, string str)
        {
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] == 49)
                    mas[i] = 1;
                else mas[i] = 0;
            }
            return mas;
        }
        #endregion

        #region Создание порождающей матрицы 
        public static int[,] CreateGenerationMatrix(int[,] generationMatrix, int[] mas, int k, int n)
        {
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
        #endregion

        #region Приведение порождающей матрицы к каноническому виду
        public static int[,] CreateMatrixCanon(int[,] generationMatrix, int k, int n)
        {
            for (int i = 0; i < k; i++)
            {
                int i2 = i + 1;
                for (int j = i + 1; j < k; j++)
                {
                    if (generationMatrix[i, j] == 1)
                    {
                        for (; i2 < k; i2++)
                        {
                            bool repeat = false;
                            if (generationMatrix[i2, j] == 1)
                            {
                                for (int j2 = j - 1; j2 > 0; j2--)
                                {
                                    if (generationMatrix[i2, j2] == 1)
                                    {
                                        repeat = true;
                                    }
                                }
                                if (repeat)
                                    continue;
                                Console.WriteLine(i + " " + i2);
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
        #endregion

        #region Преобразование канонической матрицы в проверочную
        public static int[,] CreateMatrixForCheck(int[,] checkMatrix, int[,] generationMatrix, int k, int n)
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
        #endregion

        #region Сложение строк матрицы
        public static int[,] AddingLinesMatrixMod2(int[,] matrix, int str1, int str2, int lengthString)
        {
            for (int i = 0; i < lengthString; i++)
            {
                matrix[str1, i] = (matrix[str1, i] + matrix[str2, i]) % 2;
            }
            return matrix;
        }
        #endregion

        public static void PrintMatrix(int[,] matrix, int k, int n)
        {
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write(matrix[i, j]);
                }
                Console.WriteLine();
            }
        }

        public static void PrintArray(int[] mas)
        {

            for (int i = 0; i < mas.Length; i++)
            {
                Console.Write(mas[i]);
            }
            Console.WriteLine("\n");
        }
    }
}
