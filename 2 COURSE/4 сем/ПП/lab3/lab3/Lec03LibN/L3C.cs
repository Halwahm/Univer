using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    internal class L3C : IBonus
    {
        public L3C(float cost1hour, float a, float b, float x, float y)
        {
            this.cost1hour = cost1hour;
            this.a = a;
            this.b = b;
            this.x = x;
            this.y = y;
        }
        float a = 0.0f;
        float b = 0.0f;
        public float cost1hour { get; set; } = 0;
        public float x { get; set; } = 0;
        public float y { get; set; } = 0;
        public float calc(float number_hours)
        {
            return (number_hours + a) * (cost1hour + b) * x + y;
        }
    }
}
