using System;
using System.Data.SqlTypes;
using System.IO;
using Microsoft.SqlServer.Server;

public class FileOperations
{
    [SqlProcedure]
    public static void DeleteFile(SqlString directoryPath, SqlString fileName)
    {
        try
        {
            string path = Path.Combine(directoryPath.Value, fileName.Value);
            if (File.Exists(path))
            {
                File.Delete(path);
                SqlContext.Pipe.Send("File deleted successfully.");
            }
            else
            {
                SqlContext.Pipe.Send("File not found.");
            }
        }
        catch (Exception ex)
        {
            SqlContext.Pipe.Send("Error: " + ex.Message);
        }
    }
}
