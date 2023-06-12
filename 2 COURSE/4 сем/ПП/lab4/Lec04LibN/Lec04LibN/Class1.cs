using System;
using System.IO;

namespace Lec04LibN
{
    // Интерфейс для регистрации сообщений в журнале
    public interface ILogger
    {
        void start(string title);
        void log(string message);
        void stop();
    }

    // Класс, реализующий интерфейс ILogger и позволяющий выводить сообщения в журнал
    public partial class Logger : ILogger
    {
        private static Logger instance = null;
        private string logFileName;

        private Logger()
        {
            // приватный конструктор, чтобы предотвратить создание экземпляров класса вне класса
        }

        public static ILogger create()
        {
            if (instance == null)
            {
                instance = new Logger();
            }
            return instance;
        }

        public void start(string title)
        {
            // начать новое пространство имён (имя файла журнала)
            logFileName = title + ".log";
            File.Create(logFileName).Close();
            Console.WriteLine("instance created");
        }

        public void log(string message)
        {
            // вывод сообщений в текущем пространстве имён
            using (StreamWriter writer = File.AppendText(logFileName))
            {
                writer.WriteLine(message);
            }
        }

        public void stop()
        {
            // завершить пространство имён (закрыть файл журнала)
            logFileName = null;
            Console.WriteLine("logfile exited");
        }
    }
}
