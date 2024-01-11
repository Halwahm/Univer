using System.Text;

namespace lab5
{
    internal class Logger
    {
        string FileName = "Log.log";
        public void CreatFile(string Filename)
        {
            FileName = Filename;
            FileStream fileLog = new FileStream(FileName, FileMode.Create);
            fileLog?.Close();
        }

        public async void InputInFile(Exception ex)
        {
            string str = "Время: " + DateTime.Now + "\nИсключение: " + ex.Message + "\nМетод: " + ex.TargetSite + "\nМесто: " + ex.StackTrace + "\n";
            using (FileStream fileLog = new FileStream(FileName, FileMode.Append))
            {
                // преобразуем строку в байты
                byte[] buffer = Encoding.Default.GetBytes(str + "\n");
                // запись массива байтов в файл
                await fileLog.WriteAsync(buffer, 0, buffer.Length);
                fileLog?.Close();
            }
        }

        public void WriteInConsole(Exception ex)
        {
            Console.WriteLine($"Время: {DateTime.Now}");
            Console.WriteLine($"Исключение: {ex.Message}");
            Console.WriteLine($"Метод: {ex.TargetSite}");
            Console.WriteLine($"Место: {ex.StackTrace}");
        }
    }
}