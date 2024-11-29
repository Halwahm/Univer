using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace _22
{
    public class EllipticCurve
    {
        public BigInteger a;
        public BigInteger b;
        public BigInteger modulo;
        public BigInteger order;

        public EllipticCurve(BigInteger a, BigInteger b, BigInteger modulo, BigInteger order)
        {
            this.modulo = modulo;
            this.order = order;
            while (!CheckCurveParameters(a, b))
            {
                b = (b++) % modulo;
            }
            this.a = a;
            this.b = b;
        }

        private bool CheckCurveParameters(BigInteger a, BigInteger b)
        {
            return (4 * BigInteger.Pow(a, 3) + 27 * BigInteger.Pow(b, 2)) != 0;
        }
    }

    public class Dott
    {
        public BigInteger x;
        public BigInteger y;

        public Dott()
        {
            this.x = 0;
            this.y = 0;
        }

        public Dott(BigInteger x, BigInteger y)
        {
            this.x = x;
            this.y = y;
        }

        public Dott(BigInteger x, EllipticCurve curve)
        {
            BigInteger y = 0;
            x--;
            while (BigInteger.Pow(y, 2) % curve.modulo != ((BigInteger.Pow(x, 3) + curve.a * x + curve.b) % curve.modulo)
                    && x < curve.modulo)
            {
                if (x == curve.modulo - 1)
                    x = 1;
                x++;
                y = 0;
                while (BigInteger.Pow(y, 2) % curve.modulo != ((BigInteger.Pow(x, 3) + curve.a * x + curve.b) % curve.modulo)
                        && y < curve.modulo)
                {
                    y++;
                }
            }
            this.x = x;
            this.y = y;
        }

        public Dott(BigInteger x, BigInteger y, EllipticCurve curve)
        {
            if (x < 0)
                x += curve.modulo;
            if (y < 0)
                y += curve.modulo;
            this.x = x;
            this.y = y;
        }

        public static Dott GetDottNegativeByY(Dott left, EllipticCurve curve)
        {
            left.y = curve.modulo - left.y;
            return left;
        }

        //public Dott(BigInteger x, BigInteger y, EllipticCurve curve)
        //{
        //    while (!IsDottBelongsToCurve(new Dott(x, y), curve))
        //    {
        //        while (!IsDottBelongsToCurve(new Dott(x, y), curve) && y < curve.modulo)
        //            y++;
        //        if (!IsDottBelongsToCurve(new Dott(x, y), curve) && x < curve.modulo)
        //            x++;
        //    }

        //    if (IsDottBelongsToCurve(new Dott(x, y), curve))
        //    {
        //        this.x = x;
        //        this.y = y;
        //    }
        //    else
        //    {
        //        this.x = 0;
        //        this.y = 0;
        //    }
        //}
        public static bool IsDottBelongsToCurve(Dott dott, EllipticCurve curve)
        {
            return (dott.y < curve.modulo &&
                    (BigInteger.Pow(dott.y, 2) % curve.modulo == (BigInteger.Pow(dott.x, 3) + curve.a * dott.x + curve.b) % curve.modulo));
        }

        public static Dott Addition(Dott left, Dott right, EllipticCurve curve)
        {
            Dott result = new Dott();
            BigInteger lambda;

            if (left.x == -1 && left.y == -1)
            {
                result.x = right.x;
                result.y = curve.modulo - right.y;
            }
            else if (right.x == -1 && right.y == -1)
            {
                result.x = left.x;
                result.y = curve.modulo - left.y;
            }
            else if (left.x == right.x && left.y != right.y)
            {
                result.x = -1;
                result.y = -1;
            }
            else
            {
                if (left == right)
                {
                    if ((3 * (BigInteger.Pow(left.x, 2)) + curve.a) % (2 * left.y) == 0)
                        lambda = (3 * (BigInteger.Pow(left.x, 2)) + curve.a) / (2 * left.y);
                    else
                        lambda = (3 * (BigInteger.Pow(left.x, 2)) + curve.a) * BigInteger.ModPow(2 * left.y, curve.modulo - 2, curve.modulo);
                }
                else
                {
                    if ((right.y - left.y) % (right.x - left.x) == 0)
                        lambda = (right.y - left.y) / (right.x - left.x);
                    else
                        lambda = ((right.y - left.y) > 0 ? (right.y - left.y) : (right.y - left.y) + curve.modulo)
                            * (BigInteger.ModPow(right.x - left.x, curve.modulo - 2, curve.modulo) % curve.modulo >= 0
                              ? BigInteger.ModPow(right.x - left.x, curve.modulo - 2, curve.modulo) % curve.modulo
                              : BigInteger.ModPow(right.x - left.x, curve.modulo - 2, curve.modulo) % curve.modulo + curve.modulo)
                              % curve.modulo;
                }
                result.x = ((lambda * lambda - left.x - right.x) % curve.modulo) >= 0
                            ? ((lambda * lambda - left.x - right.x) % curve.modulo)
                            : ((lambda * lambda - left.x - right.x) % curve.modulo) + curve.modulo;
                result.y = ((lambda * (left.x - result.x) - left.y) % curve.modulo) >= 0
                            ? ((lambda * (left.x - result.x) - left.y) % curve.modulo)
                            : ((lambda * (left.x - result.x) - left.y) % curve.modulo) + curve.modulo;
            }
            return result;
        }

        public static Dott DottMultiplication(Dott dott, BigInteger number, EllipticCurve curve)
        {
            Dott result = dott;
            List<int> operations = new List<int>();
            while (number > 1)
            {
                if (number % 2 == 1)
                {
                    operations.Insert(0, 1);
                    operations.Insert(0, 2);
                    number -= 1;
                    number /= 2;
                }
                else
                {
                    operations.Insert(0, 2);
                    number /= 2;
                }
            }
            for (int i = 0; i < operations.Count; i++)
            {
                if (operations[i] == 2)
                {
                    result = Dott.Addition(result, result, curve);
                }
                else
                {
                    result = Dott.Addition(result, dott, curve);
                }
            }
            return result;
        }

        public static bool operator ==(Dott left, Dott right)
        {
            if (left is null && right is null)
                return true;
            else if (left is null && !(right is null))
                return false;
            else if (!(left is null) && right is null)
                return false;
            return (left.x == right.x) && (left.y == right.y);
        }

        public static bool operator !=(Dott left, Dott right)
        {
            if (left is null && right is null)
                return false;
            else if (left is null && !(right is null))
                return true;
            else if (!(left is null) && right is null)
                return true;
            return !(left.x == right.x) && (left.y == right.y);
        }
    }
}
