using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    interface ICalc
    {
        public int And(int a, int b);
        public int Or(int a, int b);
        public int Xor(int a, int b);
        public int Not(int a);
    }
}
