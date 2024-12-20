using System.Runtime.Serialization;

namespace lab5
{
    [DataContract]
    public class A
    {
        [DataMember]
        public string S { get; set; }

        [DataMember]
        public int K { get; set; }

        [DataMember]
        public float F { get; set; }

        // Параметрический конструктор для удобства
        public A() { }

        public A(string s, int k, float f)
        {
            S = s;
            K = k;
            F = f;
        }
    }
}