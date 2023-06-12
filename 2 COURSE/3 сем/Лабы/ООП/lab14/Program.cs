using System.Diagnostics;


namespace OOP_Lab14
{
    class Program
    {
        public static void Numbers()
        {
            Console.WriteLine("Number: ");
            int length = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < length; i++)
            {
                if (i == 4)
                {
                    Console.WriteLine("Name: " + Thread.CurrentThread.Name);
                    Console.WriteLine("Id: " + Thread.CurrentThread.ManagedThreadId);
                    Console.WriteLine("Priority: " + Thread.CurrentThread.Priority);
                    Console.WriteLine("Status: " + Thread.CurrentThread.ThreadState);
                }

                Thread.Sleep(400);
                Console.WriteLine(i);
            }
        }

        public static void Even()
        {
            for (int i = 0; i < 10; i++)
            {
                if (i % 2 == 0)
                {
                    Console.Write(i + " ");
                }
                Thread.Sleep(100);
            }
        }
        public static void Odd()
        {
            for (int i = 0; i < 10; i++)
            {
                if (i % 2 != 0)
                {
                    Console.Write(i + " ");
                }
                Thread.Sleep(100);
            }
        }

        public static void PushNumber(object obj)
        {
            Random num = new Random();
            Console.WriteLine(num.Next());
        }

        static void Main(string[] args)
        {
            //1
            using (StreamWriter stream =
                new StreamWriter(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab14\Processes.txt", false))
            {
                foreach (var proc in Process.GetProcesses())
                {
                    stream.WriteLine("Name: " + proc.ProcessName);
                    stream.WriteLine("Id: " + proc.Id);
                    stream.WriteLine("Priority: " + proc.BasePriority);
                    try
                    {
                        stream.WriteLine("Start time: " + proc.StartTime);
                    }
                    catch (Exception ex)
                    {
                        stream.WriteLine(ex.Message);
                    }
                    stream.WriteLine();
                }
            }

            //2
            using (StreamWriter stream = 
                new StreamWriter(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab14\Domain.txt", false))
            {
                var domain = AppDomain.CurrentDomain;
                stream.WriteLine("Name: " + domain.FriendlyName);
                stream.WriteLine();
                stream.WriteLine("Configuration:");
                stream.WriteLine("Conficuration file name: " + domain.SetupInformation.ToString());
                stream.WriteLine();
                stream.WriteLine("Assemblies:");
                foreach (var l in domain.GetAssemblies())
                {
                    stream.WriteLine(l);
                }
            }

            //3
            /*AppDomain MyDomain = AppDomain.CreateDomain("HANDomain");
            MyDomain.Load("OOP_Lab14");
            AppDomain.Unload(MyDomain);

            Console.WriteLine();

            Thread thread = new Thread(Numbers)
            {
                Name = "Numbers thread"
            };
            thread.Start();
            thread.Join();

            Console.WriteLine();*/

            //4
            Thread thread1 = new Thread(Even);
            Thread thread2 = new Thread(Odd);
            thread1.Start();
            thread2.Start();
            thread1.Join();
            thread2.Join();
            Console.WriteLine();

            Thread thread3 = new Thread(Odd)
            {
                Priority = ThreadPriority.Highest
            };
            Thread thread4 = new Thread(Even);
            thread3.Start();
            thread3.Join();
            thread4.Start();
            thread4.Join();
            Console.WriteLine();

            //5
            object obj = new object();
            Console.WriteLine("\nPress any button to stop");
            TimerCallback time = new TimerCallback(PushNumber);
            Timer timer = new Timer(time, 0, 0, 1000);
            Console.ReadLine();
        }
    }
}
