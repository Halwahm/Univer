using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    internal class L1C : IBonus
    {
        public L1C(float cost1hour, float x, float y)
        {
            this.cost1hour = cost1hour;
            this.x = x;
            this.y = y;
        }
        public float cost1hour { get; set; } = 0;
        public float x { get; set; } = 0;
        public float y { get; set; } = 0;
        public float calc(float number_hours)
        {
            return number_hours * cost1hour * x + y;
        }
    }
}
