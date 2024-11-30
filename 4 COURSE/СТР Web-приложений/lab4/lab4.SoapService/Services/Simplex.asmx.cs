using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.Http.Cors;
using System.Web.Script.Services;
using System.Web.Services;

namespace lab4.SoapService.Services
{
    /// <summary>
    /// Сводное описание для Simplex
    /// </summary>
    /// wsdl out:SimplexProxy.cs Services/Simplex.asmx
    /// 
    [WebService(Namespace = "http://HAN/", Description = "Это SOAP-сервис для выполнения арифметических операций и обработки объектов")]
    // compability standart
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    [System.Web.Script.Services.ScriptService]
    public class Simplex : System.Web.Services.WebService
    {
        // MessageName to make this method unique within WSDL
        [WebMethod(Description = "Возвращает сумму двух чисел", MessageName = "AddMethod")]
        public int Add(int x, int y)
        {
            return x + y;
        }

        [WebMethod(Description = "Возвращает сумму двух чисел для AJAX запроса")]
        [ScriptMethod(ResponseFormat = ResponseFormat.Json)]
        public int AddS(int x, int y)
        {
            return x + y;
        }

        [WebMethod(Description = "Возвращает конкатенацию строки и числа", MessageName = "ConcatMethod")]
        public string Concat(string s, double d)
        {
            return s + d.ToString();
        }

        public class A
        {
            public string s { get; set; }
            public int k { get; set; }
            public float f { get; set; }
        }

        [WebMethod(Description = "Возвращает объект A", MessageName = "SumMethod")]
        public A Sum(A a1, A a2)
        {
            // Получение тела запроса
            var context = HttpContext.Current;
            context.Request.InputStream.Position = 0; // Сбрасываем позицию потока для чтения
            using (var reader = new StreamReader(context.Request.InputStream))
            {
                string requestBody = reader.ReadToEnd();
                // Вывод тела запроса в отладочную консоль
                System.Diagnostics.Debug.WriteLine("Request Body: " + requestBody);
            }

            // Возвращаем результат сложения
            return new A
            {
                s = a1.s + a2.s,
                k = a1.k + a2.k,
                f = a1.f + a2.f
            };
        }
    }
}
