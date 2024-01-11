namespace lab12
{
    public class Program
    {
        public static void Main()
        {
            DDDDiskInfo.GetFreeDrivesSpace();

            DDDFileInfo.GetFileInfo(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12\dddLog.txt");

            DDDDirInfo.GetDirInfo(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12\");

            DDDFileManager.GetAllDirsAndFilesOfDisk(@"C:\");

            DDDFileManager.GetAllFilesWithExtension(@"C:\Универ\2 COURSE\Лабы\ПВС", ".pdf");

            DDDFileManager.CreateZip(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12\DDDInspect\DDDFiles");

            DDDLog.SearchByDate(DateTime.Now);
        }
    }
}