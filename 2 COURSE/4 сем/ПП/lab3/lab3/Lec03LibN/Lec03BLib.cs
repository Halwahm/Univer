using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    public static partial class Lec03BLib
    {
        static public IFactory GetL1()
        {
            return new Bonus1();
        }
        static public IFactory GetL2(float a)
        {
            return new Bonus2(a);
        }
        static public IFactory GetL3(float a, float b)
        {
            return new Bonus3(a, b);
        }
    }
}
