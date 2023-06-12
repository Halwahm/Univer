using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    public delegate void ReturnName(string name);
    internal interface I1
    {
        string Name2 { get; set; }
        public void ReturnNames( string nms );
        public event ReturnName ReturnNameEvent;
        public C2 this[int index]{ get; set; }
    }
}
