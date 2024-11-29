using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace _22
{
    public static class ECDSA
    {
        private static Stopwatch stopWatch = new Stopwatch();
        public static List<long> getOpenKeyTicks = new List<long>();
        public static List<long> createSignatureTicks = new List<long>();
        public static List<long> verifySignatureTicks = new List<long>();

        public static Random rand = new Random();
        public static BigInteger getRandom(int length)
        {
            byte[] data = new byte[length];
            rand.NextBytes(data);
            return BigInteger.Abs(new BigInteger(data));
        }

        public static bool AreNumbersCoprime(BigInteger left, BigInteger right)
        {
            return BigInteger.GreatestCommonDivisor(left, right) == 1 ? true : false;
        }

        public static BigInteger ModInverse(BigInteger number, BigInteger mod)
        {
            BigInteger i = mod, v = 0, d = 1;
            while (number > 0)
            {
                BigInteger t = i / number, x = number;
                number = i % x;
                i = x;
                x = d;
                d = v - t * x;
                v = x;
            }
            v %= mod;
            if (v < 0) v = (v + mod) % mod;
            return v;
        }

        public static Dott GetOpenKey(Dott baseDott, BigInteger privateKey, EllipticCurve curve)
        {
            Dott dott;
            stopWatch.Restart();
            dott = Dott.DottMultiplication(baseDott, privateKey, curve);
            stopWatch.Stop();
            getOpenKeyTicks.Add(stopWatch.ElapsedTicks);
            //Console.WriteLine("GetOpenKey Ticks        " + stopWatch.ElapsedTicks);
            //Console.WriteLine("GetOpenKey Seconds      " + stopWatch.Elapsed);
            return dott;
            //return Dott.DottMultiplication(baseDott, privateKey, curve);
        }

        public static Dott CreateSignatureWithKandOrder(BigInteger data, BigInteger privateKey, Dott baseDott, EllipticCurve curve, BigInteger k, BigInteger order)
        {
            stopWatch.Restart();

            //BigInteger k = 0;
            Dott dott;
            BigInteger r = 0;
            BigInteger s = 0;
            while (s == 0)
            {
                r = 0;
                while (r == 0 || k == 0)
                {
                    //k = getRandom(32);
                    //k = rand.Next(1, (int)curve.order - 1);
                    //Console.WriteLine("k =     " + k);
                    //Console.WriteLine("order = " + curve.order);

                    dott = Dott.DottMultiplication(baseDott, k, curve);
                    r = dott.x % order;
                }

                if ((data + r * privateKey) % k == 0)
                    s = ((data + r * privateKey) / k) % order;
                else if (AreNumbersCoprime(k, order))
                {
                    s = ((data + r * privateKey) * ModInverse(k, order)) % order;
                }
                else
                    s = 0;
            }
            stopWatch.Stop();
            createSignatureTicks.Add(stopWatch.ElapsedTicks);
            //Console.WriteLine("CreateSignature Ticks   " + stopWatch.ElapsedTicks);
            //Console.WriteLine("CreateSignature Seconds " + stopWatch.Elapsed);
            return new Dott(r, s, curve);
        }

        public static Dott CreateSignatureWithK(BigInteger data, BigInteger privateKey, Dott baseDott, EllipticCurve curve, BigInteger k)
        {
            stopWatch.Restart();

            //BigInteger k = 0;
            Dott dott;
            BigInteger r = 0;
            BigInteger s = 0;
            while (s == 0)
            {
                r = 0;
                while (r == 0 || k == 0)
                {
                    //k = getRandom(32);
                    //k = rand.Next(1, (int)curve.order - 1);
                    //Console.WriteLine("k =     " + k);
                    //Console.WriteLine("order = " + curve.order);

                    dott = Dott.DottMultiplication(baseDott, k, curve);
                    r = dott.x % curve.order;
                }

                if ((data + r * privateKey) % k == 0)
                    s = ((data + r * privateKey) / k) % curve.order;
                else if (AreNumbersCoprime(k, curve.order))
                {
                    s = ((data + r * privateKey) * ModInverse(k, curve.order)) % curve.order;
                }
                else
                    s = 0;
            }
            //Console.WriteLine("r = " + r);
            //Console.WriteLine("s = " + s);
            stopWatch.Stop();
            createSignatureTicks.Add(stopWatch.ElapsedTicks);
            //Console.WriteLine("CreateSignature Ticks   " + stopWatch.ElapsedTicks);
            //Console.WriteLine("CreateSignature Seconds " + stopWatch.Elapsed);
            return new Dott(r, s, curve);
        }

        public static Dott CreateSignature(BigInteger data, BigInteger privateKey, Dott baseDott, EllipticCurve curve)
        {
            stopWatch.Restart();

            BigInteger k = 0;
            Dott dott;
            BigInteger r = 0;
            BigInteger s = 0;
            while (s == 0)
            {
                r = 0;
                while (r == 0 || k == 0)
                {
                    k = getRandom(32) % curve.order;
                    //k = rand.Next(1, (int)curve.order - 1);
                    //Console.WriteLine("k =     " + k);
                    //Console.WriteLine("order = " + curve.order);

                    dott = Dott.DottMultiplication(baseDott, k, curve);
                    r = dott.x % curve.order;
                }

                if ((data + r * privateKey) % k == 0)
                    s = ((data + r * privateKey) / k) % curve.order;
                else if (AreNumbersCoprime(k, curve.order))
                {
                    s = ((data + r * privateKey) * ModInverse(k, curve.order)) % curve.order;
                }
                else
                    s = 0;
            }
            //Console.WriteLine("r = " + r);
            //Console.WriteLine("s = " + s);
            stopWatch.Stop();
            createSignatureTicks.Add(stopWatch.ElapsedTicks);
            //Console.WriteLine("CreateSignature Ticks   " + stopWatch.ElapsedTicks);
            //Console.WriteLine("CreateSignature Seconds " + stopWatch.Elapsed);
            return new Dott(r, s, curve);
        }

        public static bool VerifySignatureWithOrder(BigInteger data, Dott openKey, Dott signature, Dott baseDott, EllipticCurve curve, BigInteger order)
        {
            stopWatch.Restart();
            if (signature.x > order - 1 || signature.y > order - 1)
            {
                Console.WriteLine("wrong params");
                return false;
            }
            BigInteger w = 0;
            if (AreNumbersCoprime(signature.y, order))
            {
                w = ModInverse(signature.y, order);
                BigInteger u = (data * w) % order;
                BigInteger v = (signature.x * w) % order;

                Dott left = Dott.DottMultiplication(baseDott, u, curve);
                Dott right = Dott.DottMultiplication(openKey, v, curve);
                Dott dott = Dott.Addition(left, right, curve);

                stopWatch.Stop();
                verifySignatureTicks.Add(stopWatch.ElapsedTicks);
                return (signature.x % order) == (dott.x % order);
            }
            else
                return false;
        }

        public static bool VerifySignature(BigInteger data, Dott openKey, Dott signature, Dott baseDott, EllipticCurve curve)
        {
            stopWatch.Restart();
            if (signature.x > curve.order - 1 || signature.y > curve.order - 1)
            {
                Console.WriteLine("wrong params");
                return false;
            }
            BigInteger w = 0;
            if (AreNumbersCoprime(signature.y, curve.order))
            {
                w = ModInverse(signature.y, curve.order);
                //Console.WriteLine("w = " + w);

                BigInteger u = (data * w) % curve.order;
                //Console.WriteLine("u = " + u);

                BigInteger v = (signature.x * w) % curve.order;
                //Console.WriteLine("v = " + v);

                Dott left = Dott.DottMultiplication(baseDott, u, curve);
                Dott right = Dott.DottMultiplication(openKey, v, curve);
                Dott dott = Dott.Addition(left, right, curve);

                stopWatch.Stop();
                verifySignatureTicks.Add(stopWatch.ElapsedTicks);
                return signature.x == (dott.x % curve.order);
            }
            else
                return false;
        }
    }
}
