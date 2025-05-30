﻿using System;
using lab5;

namespace Client1
{
    internal class Program
    {
        static void Main()
        {
            Console.WriteLine("Работа с HTTP endpoint");
            string binding = "httpEndpoint";

            // Создание клиента WCF-сервиса
            WCFSiplexClient simpleClient = new WCFSiplexClient(binding);

            try
            {
                int sum = simpleClient.Add(1, 3);
                Console.WriteLine("Method add for ints: " + sum);

                string concatenated = simpleClient.Concat("str", 3);
                Console.WriteLine("Method concat for str and double: " + concatenated);

                A a = simpleClient.Sum(
                    new A { F = 3.2f, K = 1, S = "4" },
                    new A { F = 1.3f, K = 2, S = "12" }
                );
                Console.WriteLine($"Result of sum object: f = {a.F} k = {a.K} s = {a.S}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred: {ex.Message}");
            }
            finally
            {
                // Корректное закрытие клиента
                if (simpleClient.State == System.ServiceModel.CommunicationState.Faulted)
                {
                    simpleClient.Abort();
                }
                else
                {
                    simpleClient.Close();
                }
            }

            Console.ReadKey();
        }
    }
}