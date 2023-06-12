using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    public class Calculator : ICalc
    {

        public int And(int a, int b)
        {
            return a & b;
        }

        public int Or(int a, int b)
        {
            return a | b;
        }

        public int Xor(int a, int b)
        {
            return a ^ b;
        }

        public int Not(int a)
        {
            return ~a;
        }
    }
}
