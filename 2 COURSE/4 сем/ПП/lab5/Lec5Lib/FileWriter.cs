using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace Lec5Lib
{
    public class FileWriter : IWriter
    {
        string filename = Constant.FileName; 
        string FileName {  get { return this.filename; } }
        public FileWriter(string? filename = null)
        {
            this.filename = filename ?? Constant.FileName;
        }
        public string? Save(string? text)
        {
            try
            {
                using StreamWriter writer = new StreamWriter(filename);
                writer.WriteLine(text);
            }
            catch (Exception)
            {
                return null;
            }

            return filename;
        }
    }
}
