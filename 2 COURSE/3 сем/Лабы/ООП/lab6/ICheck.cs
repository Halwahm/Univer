using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public interface IDate //дата
    {
        string PrintDatе();
    }

    public interface IInfo //чек
    {
        string PrintPrice();
    }

    public interface INotInfo
    {
        string PrintPrice();
    }

    public interface IOrganize
    {
        string Organize();
    }
}
