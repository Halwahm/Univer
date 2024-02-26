using System;
using System.Linq;
using System.Text;

namespace HammingCode
{
    class Program
    {
        static void Main(string[] args)
        {
            string input;
            string binaryInput;

            do
            {
                Console.Clear();
                Console.Write("Введите строку: ");
                input = Console.ReadLine();
                binaryInput = StringToBinary(ConvertToByteArray(input, Encoding.ASCII));
                Console.WriteLine("\nВаша строка в бинарном виде: " + binaryInput);
            } while (input.Length < 2);

            int dataLength = binaryInput.Length;
            int redundancyLength = CalculateRedundancyLength(dataLength);
            int totalLength = dataLength + redundancyLength;

            int[] data = new int[dataLength + redundancyLength];
            int[,] parityMatrix = new int[totalLength, redundancyLength];

            int errorPosition;

            data = StringToArray(binaryInput, dataLength);
            Console.Write("\nВходной массив: ");
            OutputArray(data, dataLength);

            parityMatrix = GenerateParityMatrix(dataLength);

            Console.WriteLine("\nПроверочная матрица:");
            OutputArray(parityMatrix, dataLength);

            // Добавление проверочных битов
            data = CalculateSyndrome(parityMatrix, data, dataLength);

            Console.WriteLine("\nПолный массив:");
            OutputArray(data, dataLength);

            try
            {
                Console.WriteLine("Введите номер первой ошибочной позиции: ");
                errorPosition = Convert.ToInt32(Console.ReadLine()) - 1;
                if (data[errorPosition] == 1) data[errorPosition] = 0;
                else data[errorPosition] = 1;

                Console.WriteLine("Введите номер второй ошибочной позиции: ");
                errorPosition = Convert.ToInt32(Console.ReadLine()) - 1;
                if (data[errorPosition] == 1) data[errorPosition] = 0;
                else data[errorPosition] = 1;
            }
            catch { }

            Console.WriteLine("\nМассив с ошибкой:");
            OutputArray(data, dataLength);

            Console.WriteLine("\nМассив с вектором ошибки:");
            data = CorrectErrors(data, parityMatrix, dataLength);
            Console.WriteLine("\nМассив без ошибок:");
            OutputArray(data, dataLength);
        }

        public static int CalculateRedundancyLength(int dataLength)
        {
            int redundancyLength = (int)(Math.Log(dataLength, 2) + 1.99f);
            return redundancyLength;
        }

        public static int[,] GenerateParityMatrix(int dataLength)
        {
            int redundancyLength = CalculateRedundancyLength(dataLength);
            int totalLength = dataLength + redundancyLength;
            double rDouble = redundancyLength - 1;
            int rPow = (int)(Math.Pow(2, rDouble));

            int[,] matrix = new int[totalLength, redundancyLength];

            int[,] combinations = new int[rPow, redundancyLength];

            for (int i = 0; i < rPow; i++)
                for (int j = 0; j < redundancyLength; j++)
                    combinations[i, j] = 0;

            foreach (int segmentLength in Enumerable.Range(0, redundancyLength - 2))
            {
                if (segmentLength * redundancyLength > dataLength) break;

                foreach (int i in Enumerable.Range(0, segmentLength + 2))
                    combinations[segmentLength * redundancyLength, i] = 1;

                foreach (int segmentPosition in Enumerable.Range(1, redundancyLength - 1))
                {
                    foreach (int i in Enumerable.Range(0, redundancyLength - 1))
                        combinations[segmentLength * redundancyLength + segmentPosition, i + 1] = combinations[segmentLength * redundancyLength + segmentPosition - 1, i];
                    combinations[segmentLength * redundancyLength + segmentPosition, 0] = combinations[segmentLength * redundancyLength + segmentPosition - 1, redundancyLength - 1];
                }

                if (segmentLength == redundancyLength - 3)
                {
                    foreach (int i in Enumerable.Range(0, redundancyLength))
                        combinations[rPow - 1, i] = 1;
                }
            }

            foreach (int i in Enumerable.Range(0, dataLength))
                foreach (int j in Enumerable.Range(0, redundancyLength))
                    matrix[i, j] = combinations[i, j];

            foreach (int i in Enumerable.Range(0, redundancyLength))
                matrix[i + dataLength, i] = 1;

            return matrix;
        }

        public static int[] CorrectErrors(int[] data, int[,] parityMatrix, int dataLength)
        {
            int redundancyLength = CalculateRedundancyLength(dataLength);
            int totalLength = dataLength + redundancyLength;

            int[] originalParityBits = new int[redundancyLength];

            foreach (int i in Enumerable.Range(dataLength, totalLength - dataLength))
                originalParityBits[i - dataLength] = data[i];

            data = CalculateSyndrome(parityMatrix, data, dataLength);

            foreach (int i in Enumerable.Range(dataLength, totalLength - dataLength))
            {
                if (originalParityBits[i - dataLength].Equals(data[i]))
                {
                    data[i] = 0;
                    if (Enumerable.Range(dataLength, totalLength - dataLength).Count(index => originalParityBits[index - dataLength].Equals(data[index])) == redundancyLength)
                    {
                        foreach (int k in Enumerable.Range(dataLength, totalLength - dataLength))
                            data[k] = originalParityBits[k - dataLength];
                        return data;
                    }
                }
                else
                {
                    data[i] = 1;
                }
            }

            foreach (int i in Enumerable.Range(0, totalLength))
            {
                int count = 0;
                foreach (int j in Enumerable.Range(0, redundancyLength))
                {
                    if (parityMatrix[i, j].Equals(data[j + dataLength]))
                        count++;
                }
                if (count == redundancyLength)
                    data[i] = (data[i] + 1) % 2;
            }

            OutputArray(data, dataLength);
            data = CalculateSyndrome(parityMatrix, data, dataLength);

            return data;
        }

        public static int[] CalculateSyndrome(int[,] parityMatrix, int[] data, int dataLength)
        {
            int redundancyLength = CalculateRedundancyLength(dataLength);
            int totalLength = dataLength + redundancyLength;
            int[] syndrome = new int[redundancyLength];

            foreach (int i in Enumerable.Range(0, redundancyLength))
            {
                int l = 0;
                foreach (int j in Enumerable.Range(0, dataLength))
                {
                    if (parityMatrix[j, i] == 1 && data[j] == 1)
                        l++;
                    else
                        syndrome[i] = 0;
                }
                if (l % 2 == 1)
                    syndrome[i] = 1;
                else
                    syndrome[i] = 0;
            }

            foreach (int i in Enumerable.Range(0, redundancyLength))
            {
                data[i + dataLength] = syndrome[i];
            }

            return data;
        }

        public static int[] StringToArray(string binaryString, int dataLength)
        {
            int redundancyLength = CalculateRedundancyLength(dataLength);
            int[] array = new int[binaryString.Length + redundancyLength];

            foreach (int i in Enumerable.Range(0, binaryString.Length))
            {
                if (binaryString[i] == '1')
                    array[i] = 1;
                else
                    array[i] = 0;
            }
            return array;
        }

        public static void OutputArray(int[,] array, int dataLength)
        {
            int redundancyLength = CalculateRedundancyLength(dataLength);
            int totalLength = dataLength + redundancyLength;

            foreach (int i in Enumerable.Range(0, redundancyLength))
            {
                foreach (int j in Enumerable.Range(0, totalLength))
                {
                    Console.Write(array[j, i]);
                    if (j + 1 == dataLength)
                        Console.Write("|");
                }
                Console.WriteLine();
            }
        }

        public static void OutputArray(int[] array, int dataLength)
        {
            int totalLength = CalculateRedundancyLength(dataLength) + dataLength;

            foreach (int i in Enumerable.Range(0, totalLength))
            {
                if (i == dataLength)
                    Console.Write("|");
                Console.Write(array[i]);
            }
            Console.WriteLine("\n");
        }

        public static byte[] ConvertToByteArray(string binaryString, Encoding encoding)
        {
            return encoding.GetBytes(binaryString);
        }

        public static string StringToBinary(byte[] data)
        {
            return string.Join("", data.Select(byt => Convert.ToString(byt, 2).PadLeft(8, '0')));
        }
    }
}
