using System;
using System.ServiceModel;
using System.ServiceModel.Web;

namespace lab5
{
    public class WCFSiplex : IWCFSiplex
    {
        public int Add(int x, int y) => x + y;

        
        public string Concat(string s, double d) => $"{s} {d}";


        public A Sum(A a1, A a2)
        {
            if(a1 == null || a2 == null)
                throw new ArgumentNullException("Input objects cannot be null.");

            return new A
            {
                S = $"{a1.S}{a2.S}",
                K = a1.K + a2.K,
                F = a1.F + a2.F
            };
        }
    }
}