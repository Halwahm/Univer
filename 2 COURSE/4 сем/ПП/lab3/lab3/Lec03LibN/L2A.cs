using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    internal class L2A : IBonus
    {
        public L2A(float cost1hour, float a) 
        {
            this.cost1hour = cost1hour;
            this.a = a;
        }
        float a = 0.0f;
        public float cost1hour { get; set; } = 0;
        public float calc(float number_hours)
        {
            return (number_hours + a) * cost1hour;
        }
    }
}
