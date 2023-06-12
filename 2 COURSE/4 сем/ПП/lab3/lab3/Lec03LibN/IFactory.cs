using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    public interface IFactory
    {
        IBonus GetA(float cost1Hour);
        IBonus GetB(float cost1Hour, float x);
        IBonus GetC(float cost1Hour, float x, float y);
    }
}