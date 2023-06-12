using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03BLib
{
    public class Employee
    {
        public IBonus Bonus { get; private set; }
        public Employee(IBonus bonus)
        {
            this.Bonus = bonus;
        }
        public float CalcBonus(float numberHours)
        {
            return Bonus.calc(numberHours);
        }
    }
}