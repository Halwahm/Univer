using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace lab5.WCF.TcpClient
{
    // TCP быстрее HTTP, исп в лок сети
    // svcutil.exe net.tcp://localhost:8734/mex /out:GeneratedClient.cs

    internal class Program
    {
        static void Main(string[] args)
        {
            var binding = new NetTcpBinding();
            var endpoint = new EndpointAddress("net.tcp://localhost:8734/Design_Time_Addresses/lab5.WCF/SiplexService/");

            var client = new Service1Client(binding, endpoint);

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
