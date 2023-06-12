using System;
using Lec04LibN;

class Program
{
    static void Main(string[] args)
    {
        ILogger logger = Logger.create();
        logger.start("MyNamespace");

        logger.log("Сообщение 1");
        logger.log("Сообщение 2");

        logger.stop();
    }
}