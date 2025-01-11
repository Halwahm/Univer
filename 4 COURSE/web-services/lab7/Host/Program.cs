using System;
using System.ServiceModel;

namespace Host
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "WCF Host Service";
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("=====================================");
            Console.WriteLine("      WCF Host Service Started      ");
            Console.WriteLine("=====================================");
            Console.ResetColor();
            var host = new ServiceHost(typeof(SyndicationServiceLibrary.Feed1));

            try
            {
                host.Open();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("[{0}] Host Opened Successfully.", DateTime.Now);
                Console.ResetColor();
                Console.WriteLine("\nAvailable Endpoints:");
                foreach (var endpoint in host.Description.Endpoints)
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine($"  - Address: {endpoint.Address}");
                    Console.WriteLine($"    Binding: {endpoint.Binding.Name}");
                    Console.WriteLine($"    Contract: {endpoint.Contract.ContractType.Name}");
                    Console.ResetColor();
                }

                Console.WriteLine("\nPress any key to close the host...");
                Console.ReadKey();
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[{0}] Error: {1}", DateTime.Now, ex.Message);
                Console.WriteLine("Details: " + ex.StackTrace);
                Console.ResetColor();
            }
            finally
            {
                if (host.State == CommunicationState.Opened)
                {
                    host.Close();
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine("\n[{0}] Host Closed Successfully.", DateTime.Now);
                    Console.ResetColor();
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine("\n[{0}] Host was not opened.", DateTime.Now);
                    Console.ResetColor();
                }
            }
        }
    }
}
