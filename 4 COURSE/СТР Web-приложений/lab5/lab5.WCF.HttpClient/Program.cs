using lab5.WCF.HttpClient.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5.WCF.HttpClient
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // reference
            var client = new Service1Client();
            var resultAdd = client.Add(5, 10);
            Console.WriteLine("Result Add: " + resultAdd);

            var resultConcat = client.Concat("Hello", 3.14);
            Console.WriteLine("Result Concat: " + resultConcat);

            var a1 = new A { s = "First", k = 10, f = 1.5 };
            var a2 = new A { s = "Second", k = 20, f = 2.5 };
            var resultSum = client.Sum(a1, a2);
            Console.WriteLine($"Result Sum: s = {resultSum.s}, k = {resultSum.k}, f = {resultSum.f}");

            client.Close();
        }
    }
}
