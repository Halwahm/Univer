namespace lab12
{
    public class DDDDirInfo
    {
        private static DirectoryInfo? GetParentDirs(DirectoryInfo? dirInfo)
        {
            while (true)
            {
                if (dirInfo == null) return dirInfo;

                Console.WriteLine($"{dirInfo.Name}");
                dirInfo = dirInfo.Parent;
            }
        }

        public static void GetDirInfo(string dir)
        {
            Console.WriteLine("********************************");
            var dirInfo = new DirectoryInfo(dir);
            if (!dirInfo.Exists)
            {
                Console.WriteLine("File Wasn't Found");
                return;
            }

            Console.WriteLine($"Count Of Subdirectories: {dirInfo.GetDirectories().Length}");
            Console.WriteLine($"Count Of SubFiles: {dirInfo.GetFiles().Length}");
            Console.WriteLine($"Creation Time: {dirInfo.CreationTime}");
            Console.WriteLine("\nParent Directory:");
            GetParentDirs(dirInfo.Parent);
            Console.WriteLine("********************************\n");

            DDDLog.WriteToLog("DDDDirInfo.GetDirInfo()", "", dir);
        }
    }
}