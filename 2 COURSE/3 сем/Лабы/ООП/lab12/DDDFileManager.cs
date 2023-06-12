using System.IO.Compression;

namespace lab12
{
    public class DDDFileManager
    {
        public static void GetAllDirsAndFilesOfDisk(string diskName)
        {
            var allDrives = DriveInfo.GetDrives();
            if (allDrives.Any(drive => drive.Name == diskName))
            {
                var dir = new DirectoryInfo(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12");
                if (dir.GetDirectories("DDDInspect").Length == 0)
                {
                    var subDir = dir.CreateSubdirectory("DDDInspect");
                    var dr = new DirectoryInfo(diskName);
                    using (var file = new StreamWriter(subDir.FullName + @"\" + "DDDDirInfo.txt"))
                    {
                        file.WriteLine("----------Directory----------");
                        foreach (var d in dr.GetDirectories())
                            file.WriteLine($"{d.Name}");
                        file.WriteLine("-------------------------------");

                        file.WriteLine("----------Files----------");
                        foreach (var d in dr.GetFiles())
                            file.WriteLine($"{d.Name}");
                        file.WriteLine("-------------------------");
                    }
                    var dirInfo = new FileInfo(subDir.FullName + @"\" + "DDDDirInfo.txt");
                    dirInfo.CopyTo(subDir.FullName + @"\" + "DDDDirInfoCOPY.txt");
                    dirInfo.Delete();
                }
            }

            DDDLog.WriteToLog("DDDFileManager.GetAllDirsAndFilesOfDisk()", "", diskName);
        }

        public static void GetAllFilesWithExtension(string dirPath, string extension)
        {
            var directory = new DirectoryInfo(dirPath);
            if (directory.Exists)
            {
                var temp = new DirectoryInfo(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12");
                if (temp.GetDirectories("DDDInspect")[0].GetDirectories("DDDFiles").Length == 0)
                {
                    var files = temp.CreateSubdirectory("DDDFiles");

                    foreach (var file in directory.GetFiles($"*{extension}"))
                        file.CopyTo(files.FullName + @"\" + file.Name);

                    files.MoveTo(temp.GetDirectories("DDDInspect")[0].FullName + "\\DDDFiles");
                }
            }

            DDDLog.WriteToLog("DDDFileManager.GetAllFilesWithExtension()", "", dirPath);
        }

        public static void CreateZip(string dir)
        {
            const string zipName = @"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12\DDDInspect\DDDFiles.zip";
            if (new DirectoryInfo(@"C:\Универ\2 COURSE\Лабы\ООП\3 сем\lab12\DDDInspect").GetFiles("*.zip").Length == 0)
            {
                ZipFile.CreateFromDirectory(dir, zipName);
                var direct = new DirectoryInfo(dir);
                foreach (var innerFile in direct.GetFiles())
                    innerFile.Delete();
                direct.Delete();
                ZipFile.ExtractToDirectory(zipName, dir);
            }

            DDDLog.WriteToLog("DDDFileManager.CreateZip()", "", dir);
        }
    }
}