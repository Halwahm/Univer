using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    internal class Bonus1 : IFactory
    {
        public IBonus GetA(float cost1Hour)
        {
            return new L1A(cost1Hour);
        }

        public IBonus GetB(float cost1Hour, float x)
        {
            return new L1B(cost1Hour, x);
        }

        public IBonus GetC(float cost1Hour, float x, float y)
        {
            return new L1C(cost1Hour, x, y);
        }
    }

    internal class Bonus2 : IFactory
    {
        float a = 0;
        public Bonus2(float a)
        {
            this.a = a;
        }
        public IBonus GetA(float cost1Hour)
        {
            return new L2A(cost1Hour, a);
        }

        public IBonus GetB(float cost1Hour, float x)
        {
            return new L2B(cost1Hour, a, x);
        }

        public IBonus GetC(float cost1Hour, float x, float y)
        {
            return new L2C(cost1Hour, a, x, y);
        }
    }

    internal class Bonus3 : IFactory
    {
        float a = 0;
        float b = 0;
        public Bonus3(float a, float b)
        {
            this.a = a;
            this.b = b;
        }

        public IBonus GetA(float cost1Hour)
        {
            return new L3A(cost1Hour, a, b);
        }

        public IBonus GetB(float cost1Hour, float x)
        {
            return new L3B(cost1Hour, a, b, x);
        }

        public IBonus GetC(float cost1Hour, float x, float y)
        {
            return new L3C(cost1Hour, a, b, x, y);
        }
    }
}