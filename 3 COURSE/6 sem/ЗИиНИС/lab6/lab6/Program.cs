using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    class Program
    {
        static void Main(string[] args)
        {
            string Xk = "10010111000110101110000100";
            string Xr = "100101";
 
            int k = Xk.Length;
            int n = 31;
            int r = 5;

            int error;

            int[] masXk = new int[k];
            Operations.StringInArray(masXk, Xk);

            int[] masXr = new int[Xr.Length];
            Operations.StringInArray(masXr, Xr);

            Console.WriteLine("\t\tВходная строка xk: " + Xk);
            Console.WriteLine("\t\tПорождающий полином xr в двоичном виде: " + Xr);
            Console.WriteLine("\t\t\t k = {0}, r = {1}, n = {2}", k, r, n);
            Console.WriteLine("--------------------------------------------------------------------------------");

            int[,] generationMatrix = new int[k, n];
            Operations.CreateGenerationMatrix(generationMatrix, masXr, k, n);

            Console.WriteLine("\n\t\t\t\tПорождающая матрица\n");
            Operations.PrintMatrix(generationMatrix, k, n);

            Operations.CreateMatrixCanon(generationMatrix, k, n);
            Console.WriteLine("--------------------------------------------------------------------------------");

            Console.WriteLine("\n\t\t\t\tКаноническая матрица\n");
            Operations.PrintMatrix(generationMatrix, k, n);

            int[,] checkMatrix = new int[n, r];
            Operations.CreateMatrixForCheck(checkMatrix, generationMatrix, k, n);
            Console.WriteLine("--------------------------------------------------------------------------------");

            Console.WriteLine("\n\t\t\t\tПроверочная матрица канонической формы\n");
            Operations.PrintMatrix(checkMatrix, n, r);

            // Task 1.2

            int[] masXn = new int[n];
            Operations.ShiftR(masXn, masXk, r);

            Console.WriteLine("--------------------------------------------------------------------------------");

            // Task 2
            Console.WriteLine("\n\t\t\t\t\tДеление\n");
            Operations.SearchRes(masXn, masXr);

            Console.WriteLine("Остаток:");
            Operations.PrintArray(masXn);

            Console.WriteLine("--------------------------------------------------------------------------------");
            Console.WriteLine("\n\t\t\t\tИтоговая строка\n");
            Operations.ShiftR(masXn, masXk, r);
            Operations.PrintArray(masXn);

            Console.WriteLine("--------------------------------------------------------------------------------");
            try
            {
                Console.WriteLine("Введите место первой ошибки");
                error = Convert.ToInt32(Console.ReadLine()) - 1;
                if (masXn[error] == 1) masXn[error] = 0;
                else masXn[error] = 1;
            }
            catch { }

            Console.WriteLine("Ошибочная строка:");
            Operations.PrintArray(masXn);

            Operations.SearchingMistake(masXn, masXr, checkMatrix, r);

            Console.WriteLine("--------------------------------------------------------------------------------");
            try
            {
                Console.WriteLine("Место первой ошибки: ");
                error = Convert.ToInt32(Console.ReadLine()) - 1;
                if (masXn[error] == 1)
                    masXn[error] = 0;
                else masXn[error] = 1;

                Console.WriteLine("Место второй ошибки: ");
                error = Convert.ToInt32(Console.ReadLine()) - 1;
                if (masXn[error] == 1)
                    masXn[error] = 0;
                else masXn[error] = 1;
            }
            catch { }

            Console.WriteLine("Ошибочная строка:");
            Operations.PrintArray(masXn);

            Operations.SearchingMistake(masXn, masXr, checkMatrix, r);
        }
    }
}
