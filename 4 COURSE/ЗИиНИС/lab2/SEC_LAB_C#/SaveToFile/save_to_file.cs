using System.IO;

namespace SEC_LAB_C_.SaveToFile
{
    public class save_to_file
    {
        public static void save(string data, string filePath) {
            
            using (FileStream fileStream = new FileStream(filePath, FileMode.Create, FileAccess.Write, FileShare.None))
            {
                using (StreamWriter writer = new StreamWriter(fileStream))
                {
                    writer.Write(data);
                }
            }
        }
    }
}
