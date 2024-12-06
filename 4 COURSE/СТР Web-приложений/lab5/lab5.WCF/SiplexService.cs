using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace lab5.WCF
{
    // ПРИМЕЧАНИЕ. Команду "Переименовать" в меню "Рефакторинг" можно использовать для одновременного изменения имени класса "Service1" в коде и файле конфигурации.
    public class SiplexService : IService1
    {
        public int Add(int x, int y)
        {
            return x + y;
        }

        public string Concat(string s, double d)
        {
            return s + d.ToString();
        }

        // для работы клиентов
        //public A Sum(A a1, A a2)
        //{
        //    return new A
        //    {
        //        s = a1.s + a2.s,
        //        k = a1.k + a2.k,
        //        f = a1.f + a2.f
        //    };
        //}
        public A Sum(SumRequest request)
        {
            return new A
            {
                s = request.a1.s + request.a2.s,
                k = request.a1.k + request.a2.k,
                f = request.a1.f + request.a2.f
            };
        }

    }
}
