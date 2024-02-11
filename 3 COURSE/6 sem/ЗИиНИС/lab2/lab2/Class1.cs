using System;
using System.Collections.Generic;
using System.Linq;

public static class IndividualEntropyCalculator
{
    // Метод для подсчета энтропии каждого символа в отдельности
    public static Dictionary<char, double> CalculateIndividualEntropies(string text, List<char> alphabet)
    {
        int totalCharacters = text.Length;
        Dictionary<char, int> frequencies = new Dictionary<char, int>();

        // Подсчет частоты появления каждого символа
        foreach (char c in text)
        {
            if (frequencies.ContainsKey(c))
                frequencies[c]++;
            else
                frequencies[c] = 1;
        }

        // Рассчет вероятности появления каждого символа
        Dictionary<char, double> probabilities = new Dictionary<char, double>();
        foreach (var kvp in frequencies)
        {
            probabilities[kvp.Key] = (double)kvp.Value / totalCharacters;
        }

        // Рассчет энтропии для каждого символа
        Dictionary<char, double> entropies = new Dictionary<char, double>();
        foreach (var kvp in probabilities)
        {
            double p = kvp.Value;
            if (p > 0)
                entropies[kvp.Key] = -p * Math.Log(p, 2);
            else
                entropies[kvp.Key] = 0; // Для символов с нулевой вероятностью энтропия будет равна 0
        }

        return entropies;
    }

    // Метод для вывода энтропии каждого символа
    public static void PrintIndividualEntropies(Dictionary<char, double> individualEntropies)
    {
        // Сортировка символов по алфавиту
        var sortedEntropies = individualEntropies.OrderBy(e => e.Key);

        // Вывод энтропии для каждого символа
        foreach (var kvp in sortedEntropies)
        {
            Console.WriteLine($"{kvp.Key} {kvp.Value}");
        }
    }
}
