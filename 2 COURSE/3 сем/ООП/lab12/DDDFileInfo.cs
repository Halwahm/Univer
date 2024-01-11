namespace lab12
{
    public class DDDFileInfo
    {
        public static void GetFileInfo(string file)
        {
            Console.WriteLine("********************************");
            var fileInfo = new FileInfo(file);
            if (!fileInfo.Exists)
            {
                Console.WriteLine("File Wasn't Found");
                return;
            }

            Console.WriteLine($"Path: {fileInfo.FullName}");
            Console.WriteLine($"Length: {fileInfo.Length} byte");
            Console.WriteLine($"Name: {fileInfo.Name}");
            Console.WriteLine($"Extension: {fileInfo.Extension}");
            Console.WriteLine($"Creation Time: {fileInfo.CreationTime}");
            Console.WriteLine("********************************\n");

            DDDLog.WriteToLog("DDDFileInfo.GetFileInfo()", fileInfo.Name, fileInfo.FullName);

        }

    }
}