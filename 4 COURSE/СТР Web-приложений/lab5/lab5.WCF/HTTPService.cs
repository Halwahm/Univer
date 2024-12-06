using System.ServiceModel;
using System.ServiceModel.Web;

namespace lab5.WCF
{
    [ServiceContract]
    public interface IService2
    {
        [OperationContract]
        [WebGet(ResponseFormat = WebMessageFormat.Json, UriTemplate = "/Add?x={x}&y={y}")]
        int Add(int x, int y);

        [OperationContract]
        [WebGet(ResponseFormat = WebMessageFormat.Json, UriTemplate = "/Concat?s={s}&d={d}")]
        string Concat(string s, double d);

        [OperationContract]
        [WebInvoke(Method = "POST", RequestFormat = WebMessageFormat.Json, ResponseFormat = WebMessageFormat.Json, UriTemplate = "/Sum")]
        A Sum(A a1, A a2);
    }
}
