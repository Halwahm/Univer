using System.ServiceModel;
using System.ServiceModel.Web;

namespace lab5
{
    //BodyStyle = WebMessageBodyStyle.Wrapped)]
    //Включает дополнительные метаданные в JSON(или XML).

    [ServiceContract]
    public interface IWCFSiplex
    {
        // REST Метод Add
        [OperationContract]
        [WebGet(UriTemplate = "/Add?x={x}&y={y}", 
            ResponseFormat = WebMessageFormat.Json, 
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        int Add(int x, int y);

        // REST Метод Concat
        [OperationContract]
        [WebGet(UriTemplate = "/Concat?s={s}&d={d}", 
            ResponseFormat = WebMessageFormat.Json, 
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        string Concat(string s, double d);

        // REST Метод Sum
        [OperationContract]
        [WebInvoke(Method = "POST", 
            UriTemplate = "/Sum", 
            RequestFormat = WebMessageFormat.Json, 
            ResponseFormat = WebMessageFormat.Json, 
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        A Sum(A a1, A a2);
    }
}