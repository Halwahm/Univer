using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class Calculator
    {
        public static double Add(double num1, double num2) => num1 + num2;
        public static double Sub(double num1, double num2) => num1 - num2;
        public static double Mul(double num1, double num2) => num1 * num2;
        public static double Div(double num1, double num2)
        {
            if (num1 == 0 || num2 == 0)
            {
                throw new System.DivideByZeroException("Division by zero is not allowed.");
            }

            return num1 / num2;
        }
    }
}
