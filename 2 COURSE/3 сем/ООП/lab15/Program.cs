using System.Collections.Concurrent;
using System.Diagnostics;

namespace OOP_Lab15
{
    class Program
    {
        public static int cus = 1;
        static void Number()
        {
            for (int i = 1; i < 20; i++)
            {
                Console.WriteLine(i);
                Thread.Sleep(200);
            }
        }
        static void Square(int num)
        {
            int u;
            u = num * num;

            Console.WriteLine($"Квадрат числа {num} равен {u}");
        }
        static void Display()
        {
            Console.WriteLine($"Выполняется задача {Task.CurrentId}");
            Thread.Sleep(2000);
        }
        static async void FactorialAsync()
        {
            Console.WriteLine("Начало метода FactorialAsync");
            await Task.Run(() => Square(5)); // эта задача будет выполняться асинхронно
            Console.WriteLine("Конец метода FactorialAsync\n");
        }
        static void Main(string[] args)
        {
            //1
            Task task1 = new Task(Number);
            Stopwatch stopwatch = new Stopwatch();
            task1.Start();
            Console.WriteLine("Id: " + task1.Id);
            Console.WriteLine("Is completed?: " + task1.IsCompleted);
            Console.WriteLine("Status: " + task1.Status);
            task1.Wait();
            stopwatch.Stop();
            Console.WriteLine("RunTime: " + stopwatch.Elapsed);
            Console.WriteLine();

            //2
            CancellationTokenSource CancelToken = new CancellationTokenSource();
            CancellationToken token = CancelToken.Token;
            Task task2 = new Task(Number, token);
            task2.Start();
            CancelToken.Cancel();
            if (token.IsCancellationRequested)
            {
                Console.WriteLine("Is canceled");
            }
            Console.WriteLine();

            //3
            Task<int> task3_1 = new Task<int>(() =>
            {
                int i = 1;
                while (i < 10)
                    i += 3;
                return i;
            });
            Task<int> task3_2 = new Task<int>(() =>
            {
                Random rnd = new Random();
                return rnd.Next(1, 20);
            });
            Task<string> task3_3 = new Task<string>(() =>
            {
                return "Result:";
            });
            task3_1.Start();
            task3_1.Wait();
            task3_2.Start();
            task3_2.Wait();
            task3_3.Start();
            task3_3.Wait();
            Task task3Result = new Task(() =>
            {
                Console.WriteLine($"{task3_3.Result} {task3_1.Result} + " +
                    $"{task3_2.Result} = {task3_1.Result + task3_2.Result}");
            });
            task3Result.Start();
            task3Result.Wait();
            Console.WriteLine();

            //4
            Task task4_1 = Task.WhenAll(task3Result, task3_3, task3_2, task3_1).ContinueWith(t =>
            {
                Console.WriteLine("Continue task4_1");
            });
            task4_1.Wait();
            Task<string> task4_2 = Task.Run(() =>
            {
                return "Continue task4_2";
            });
            var awaiter = task4_2.GetAwaiter();
            awaiter.OnCompleted(() =>
            {
                string result = awaiter.GetResult();
                Console.WriteLine(result);
            });
            Console.WriteLine();

            //5
            int[] arr1 = new int[1000000];
            int[] arr2 = new int[1000000];
            Stopwatch stopwatch2 = new Stopwatch();
            stopwatch2.Start();
            Parallel.For(0, arr1.Length, t => arr1[t] = t);
            stopwatch2.Stop();
            Console.WriteLine($"Parallel.For: {stopwatch2.Elapsed}");

            Stopwatch stopwatch3 = new Stopwatch();
            stopwatch3.Start();
            for (int i = 0; i < arr2.Length; i++)
                arr2[i] = i + 1;

            stopwatch3.Stop();
            Console.WriteLine("foreach: " + stopwatch3.Elapsed);
            Stopwatch stopwatch4 = new Stopwatch();
            stopwatch4.Start();
            Parallel.ForEach<int>(new List<int>() { 1, 2, 3, 4 }, Square);
            stopwatch4.Stop();
            Console.WriteLine("Parallel.Foreach: " + stopwatch4.Elapsed);

            Stopwatch stopwatch5 = new Stopwatch();
            stopwatch5.Start();
            foreach (var m in new List<int>() { 1, 2, 3, 4 })
            {
                Square(m);
            }
            stopwatch5.Stop();
            Console.WriteLine("foreach: " + stopwatch5.Elapsed);
            Console.WriteLine();

            //6
            Parallel.Invoke(Display,
                () => {
                    Console.WriteLine($"Выполняется задача {Task.CurrentId}");
                    Thread.Sleep(1000);
                },
            () => Square(4));
            Console.WriteLine();

            //7
            BlockingCollection<string> blockcoll = new BlockingCollection<string>();
            Task Seller = new Task(
                () =>
                {
                    List<string> Appliances = new List<string> 
                    { "Fridge", "Microwave", "Plate", "Washing machine", "Toaster" };
                    int choose = 0;
                    Random rnd = new Random();
                    for (int i = 0; i < 5; i++)
                    {
                        choose = rnd.Next(0, Appliances.Count - 1);
                        Console.WriteLine($"Add {Appliances[choose]}");
                        blockcoll.Add(Appliances[choose]);
                        Appliances.RemoveAt(choose);
                        Thread.Sleep(choose);
                    }
                    blockcoll.CompleteAdding();
                });

            Task Customer = new Task(
                () =>
                {
                    string str;
                    while (blockcoll.IsCompleted == false)
                    {
                        if (blockcoll.TryTake(out str) == true)
                            Console.WriteLine($"Selled: {str} to Customer{cus}");
                        else
                            Console.WriteLine($"Customer{cus} bought nothing and left");
                        cus++;
                    }

                });

            Seller.Start();
            Customer.Start();
            Customer.Wait();
            Seller.Wait();

            //8
            FactorialAsync();
        }
    }
}
