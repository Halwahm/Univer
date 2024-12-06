using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace lab5.WCF
{
    // ПРИМЕЧАНИЕ. Команду "Переименовать" в меню "Рефакторинг" можно использовать для одновременного изменения имени интерфейса "IService1" в коде и файле конфигурации.
    //  интерфейс определяет контракт WCF-службы.
    [ServiceContract]
    public interface IService1
    {
        // для работы клиентов
        // Задает метод как операцию службы, доступную клиентам.
        //[OperationContract]
        //int Add(int x, int y);

        //[OperationContract]
        //string Concat(string s, double d);

        //[OperationContract]
        //A Sum(A a1, A a2);

        // http://localhost:8080/Design_Time_Addresses/lab5.WCF/SiplexService/Add?x=10&y=20
        [OperationContract]
        [WebGet(ResponseFormat = WebMessageFormat.Json, UriTemplate = "/Add?x={x}&y={y}")]
        int Add(int x, int y);

        // http://localhost:8080/Design_Time_Addresses/lab5.WCF/SiplexService/Concat?s=Hello&d=3.14
        [OperationContract]
        [WebGet(ResponseFormat = WebMessageFormat.Json, UriTemplate = "/Concat?s={s}&d={d}")]
        string Concat(string s, double d);

        // postman
        [OperationContract]
        [WebInvoke(Method = "POST", RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json, UriTemplate = "/Sum")]
        A Sum(SumRequest request);
    }

    // Используйте контракт данных, как показано в примере ниже, чтобы добавить составные типы к операциям служб.
    // В проект можно добавлять XSD-файлы. После построения проекта вы можете напрямую использовать в нем определенные типы данных с пространством имен "lab5.WCF.ContractType".
    // класс используется для передачи данных между клиентом и сервером.
    [DataContract]
    public class A
    {
        //  Задает свойства класса, которые будут сериализованы и переданы клиенту
        [DataMember]
        public string s { get; set; }

        [DataMember]
        public int k { get; set; }

        [DataMember]
        public double f { get; set; }
    }

    [DataContract]
    public class SumRequest
    {
        [DataMember]
        public A a1 { get; set; }
        [DataMember]
        public A a2 { get; set; }
    }
}
