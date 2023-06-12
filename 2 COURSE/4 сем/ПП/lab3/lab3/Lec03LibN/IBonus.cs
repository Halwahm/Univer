using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    public interface IBonus
    {
        float cost1hour { get; set; }
        float calc(float numberHours);
    }
}