//using lab5.WCF;
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.ServiceModel;
//using System.ServiceModel.Description;
//using System.Text;
//using System.Threading.Tasks;

//namespace lab5.WCF.Host
//{
//    internal class Program
//    {
//        static void Main(string[] args)
//        {
//            var uri = new Uri("http://localhost:8080/Design_Time_Addresses/lab5.WCF/SiplexService");
//            var tcpUri = new Uri("net.tcp://localhost:8081/Design_Time_Addresses/lab5.WCF/SiplexService");

//            using (var host = new ServiceHost(typeof(SiplexService), uri, tcpUri))
//            {
//                var smb = new ServiceMetadataBehavior
//                {
//                    HttpGetEnabled = true
//                };

//                host.Description.Behaviors.Add(smb);

//                //host.AddServiceEndpoint(typeof(IService1), new NetTcpBinding(), tcpUri);

//                host.Open();
//                Console.WriteLine("Service is running: \n{0}\n{1}", uri, tcpUri);
//                Console.WriteLine("Press Enter to close app...");

//                Console.ReadLine();

//                host.Close();
//            }
//        }
//    }
//}


using System;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace lab5.WCF.Host
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var uri = new Uri("http://localhost:8080/Design_Time_Addresses/lab5.WCF/SiplexService");

            using (var host = new ServiceHost(typeof(SiplexService), uri))
            {
                var webBinding = new WebHttpBinding();
                var endpoint = host.AddServiceEndpoint(typeof(IService1), webBinding, "");
                endpoint.Behaviors.Add(new WebHttpBehavior());

                host.Open();
                Console.WriteLine("Сервис запущен по адресу: {0}", uri);
                Console.WriteLine("Нажмите Enter для остановки сервиса...");

                Console.ReadLine();

                host.Close();
            }
        }
    }
}

