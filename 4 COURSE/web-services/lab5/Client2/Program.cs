﻿using System;
using lab5;


//  & "C:\Program Files (x86)\Microsoft SDKs\Windows\v10.0A\bin\NETFX 4.8 Tools\SvcUtil.exe"
//  "http://localhost:8733/Design_Time_Addresses/lab5/WCFSiplex/?wsdl" /out:WCFSimplexProxy.cs /config:WCFSimplexProxy.config

namespace Client2
{
    internal class Program
    {
        static void Main()
        {
            Console.WriteLine("Работа с TCP endpoint");
            string binding = "tcpEndpoint";

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