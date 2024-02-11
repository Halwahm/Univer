using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class EntropyCalculator
{
    // Метод для подсчета энтропии текста на основе заданного алфавита
    public static double CalculateEntropy(string text, List<char> alphabet)
    {
        int totalCharacters = text.Length;
        Dictionary<char, int> frequencies = new Dictionary<char, int>();

        // Подсчет частоты появления каждого символа
        foreach (char c in text)
        {
            char lowercaseChar = Char.ToLower(c);
            if (alphabet.Contains(lowercaseChar))
            {
                if (frequencies.ContainsKey(lowercaseChar))
                    frequencies[lowercaseChar]++;
                else
                    frequencies[lowercaseChar] = 1;
            }
        }

        // Расчет вероятности появления каждого символа
        Dictionary<char, double> probabilities = new Dictionary<char, double>();
        foreach (char c in alphabet)
        {
            char lowercaseChar = Char.ToLower(c);
            if (frequencies.ContainsKey(lowercaseChar))
                probabilities[lowercaseChar] = (double)frequencies[lowercaseChar] / totalCharacters;
            else
                probabilities[lowercaseChar] = 0;
        }

        // Расчет энтропии
        double entropy = 0;
        foreach (double p in probabilities.Values)
        {
            if (p > 0)
                entropy += -p * Math.Log(p, 2);
        }

        return entropy;
    }

    public static double CalculateBinaryEntropy(string binaryText)
    {
        int totalCharacters = binaryText.Length;
        int onesCount = binaryText.Count(c => c == '1');
        int zerosCount = totalCharacters - onesCount;

        double onesProbability = (double)onesCount / totalCharacters;
        double zerosProbability = (double)zerosCount / totalCharacters;

        return -(onesProbability * Math.Log(onesProbability, 2) + zerosProbability * Math.Log(zerosProbability, 2));
    }

    public static double CalculateInformationSize(double entropy, string message)
    {
        int totalCharacters = message.Length;
        return entropy * totalCharacters;
    }

    static void Main()
    {
        // Задание алфавитов для латышского и таджикского языков
        List<char> latvianAlphabet = new List<char> { 'a', 'ā', 'b', 'c', 'č', 'd', 'e', 'ē', 'f', 'g', 'ģ', 'h', 'i', 'ī', 'j', 'k', 'ķ', 'l', 'ļ', 'm', 'n', 'ņ', 'o', 'p', 'r', 's', 'š', 't', 'u', 'ū', 'v', 'z', 'ž' };
        List<char> tajikAlphabet = new List<char> { 'а', 'б', 'в', 'г', 'ғ', 'д', 'е', 'ё', 'ж', 'з', 'и', 'ӣ', 'й', 'к', 'қ', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ӯ', 'ф', 'х', 'ҳ', 'ч', 'ҷ', 'ш' };

        // Чтение текстов из файлов
        string latvianText = File.ReadAllText("latish.txt").ToLower();
        string tajikText = File.ReadAllText("tadzh.txt").ToLower();

        // Расчет энтропии для текстов на латышском и таджикском языках
        double latvianEntropy = CalculateEntropy(latvianText, latvianAlphabet);
        double tajikEntropy = CalculateEntropy(tajikText, tajikAlphabet);

        Console.WriteLine("Latvian Entropy: " + latvianEntropy);
        Console.WriteLine("Tajik Entropy: " + tajikEntropy);

        // Преобразование текстов в бинарный код
        string binaryLatvianText = StringToBinary(latvianText);
        string binaryTajikText = StringToBinary(tajikText);

        // Расчет бинарной энтропии для текстов на латышском и таджикском языках
        double binaryLatvianEntropy = CalculateBinaryEntropy(binaryLatvianText);
        double binaryTajikEntropy = CalculateBinaryEntropy(binaryTajikText);

        Console.WriteLine("Binary Latvian Entropy: " + binaryLatvianEntropy);
        Console.WriteLine("Binary Tajik Entropy: " + binaryTajikEntropy);

        // Пример подсчета количества информации в сообщении на основе латышского алфавита
        string message = "Halaleenko Andrejs Nikolajevičs ";
        double informationSize = CalculateInformationSize(latvianEntropy, message.ToLower());
        Console.WriteLine("Information Size (Name; Latvian alphabet): " + informationSize);

        // Преобразование текста в бинарный код (кодировка ASCII)
        string binaryMessage = StringToBinary(message.ToLower());
        double binaryInformationSize = CalculateInformationSize(1, binaryMessage); // При кодировке ASCII вероятность появления каждого символа равна 1

        Console.WriteLine("Latish (Based on ASCII): " + binaryInformationSize);

        // Пример подсчета количества информации в сообщении на основе таджикского алфавита
        string tajikMessage = "Халалеенко Андрей Николаевич";
        double tajikInformationSize = CalculateInformationSize(tajikEntropy, tajikMessage.ToLower());
        Console.WriteLine("Information Size (Name; Tajik alphabet): " + tajikInformationSize);

        // Преобразование текста в бинарный код (кодировка ASCII)
        string binaryTajikMessage = StringToBinary(tajikMessage.ToLower());
        double binaryTajikInformationSize = CalculateInformationSize(1, binaryTajikMessage); // При кодировке ASCII вероятность появления каждого символа равна 1

        Console.WriteLine("Tajik (Based on ASCII): " + binaryTajikInformationSize);

        // Дополнительные вычисления для пункта (г)
        double p1 = 0.1;
        double p2 = 0.5;
        double p3 = 1.0;

        double errorInformationSize1 = CalculateInformationSize(latvianEntropy, message.ToLower()) * p1;
        double errorInformationSize2 = CalculateInformationSize(latvianEntropy, message.ToLower()) * p2;
        double errorInformationSize3 = CalculateInformationSize(latvianEntropy, message.ToLower()) * p3;

        Console.WriteLine("Information Size with Error Probability 0.1: " + errorInformationSize1);
        Console.WriteLine("Information Size with Error Probability 0.5: " + errorInformationSize2);
        Console.WriteLine("Information Size with Error Probability 1.0: " + errorInformationSize3);


        // Вывод энтропии для каждого символа алфавитов
        Console.WriteLine("Individual Entropy for Latvian Alphabet:");
        var latvianIndividualEntropies = IndividualEntropyCalculator.CalculateIndividualEntropies(latvianText, latvianAlphabet);
        IndividualEntropyCalculator.PrintIndividualEntropies(latvianIndividualEntropies);

        Console.WriteLine("\n\n");

        Console.WriteLine("Individual Entropy for Tajik Alphabet:");
        var tajikIndividualEntropies = IndividualEntropyCalculator.CalculateIndividualEntropies(tajikText, tajikAlphabet);
        IndividualEntropyCalculator.PrintIndividualEntropies(tajikIndividualEntropies);

    }

    // Метод для преобразования строки в бинарный код
    public static string StringToBinary(string text)
    {
        string binary = "";
        foreach (char c in text)
        {
            binary += Convert.ToString(c, 2).PadLeft(8, '0');
        }
        return binary;
    }
}
