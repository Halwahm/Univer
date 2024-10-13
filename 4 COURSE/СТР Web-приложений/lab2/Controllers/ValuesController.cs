using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Web;
using System.Web.Http;

namespace WebClients.Controllers
{
    public class ValuesController : ApiController
    {
        // GET api/values
        [HttpGet]
        public HttpResponseMessage Get()
        {
            // Проверяем наличие значения "Result" в сессии
            int result = HttpContext.Current.Session["Result"] != null
                ? (int)HttpContext.Current.Session["Result"]
                : 0;

            // Возвращаем результат в формате JSON
            return Request.CreateResponse(HttpStatusCode.OK, new { Result = result });
        }

        // POST api/values
        [HttpPost]
        public HttpResponseMessage Post([FromUri] int result)
        {
            // Устанавливаем новое значение "Result" в сессии
            HttpContext.Current.Session["Result"] = result;
            return Request.CreateResponse(HttpStatusCode.OK, new { Message = $"Result изменен на: {result}" });
        }

        // PUT api/values
        [HttpPut]
        public HttpResponseMessage Put([FromUri] int add)
        {
            // Проверяем наличие стека в сессии и инициализируем его, если нужно
            Stack<int> stack = HttpContext.Current.Session["Stack"] as Stack<int> ?? new Stack<int>();
            stack.Push(add);

            // Сохраняем стек в сессии
            HttpContext.Current.Session["Stack"] = stack;

            return Request.CreateResponse(HttpStatusCode.OK, new { Message = $"Значение {add} добавлено в стек." });
        }

        // DELETE api/values
        [HttpDelete]
        public HttpResponseMessage Delete()
        {
            // Получаем стек из сессии
            Stack<int> stack = HttpContext.Current.Session["Stack"] as Stack<int> ?? new Stack<int>();

            // Проверяем, не пуст ли стек
            if (stack.Count == 0)
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest, new { Message = "Стек пуст." });
            }

            // Удаляем значение из стека и обновляем Result
            int popValue = stack.Pop();

            // Получаем текущее значение Result из сессии
            int result = HttpContext.Current.Session["Result"] != null
                ? (int)HttpContext.Current.Session["Result"]
                : 0;

            // Обновляем значение Result
            result += popValue;
            HttpContext.Current.Session["Result"] = result;
            HttpContext.Current.Session["Stack"] = stack;

            return Request.CreateResponse(HttpStatusCode.OK, new { Message = $"Значение {popValue} удалено из стека. Result = {result}" });
        }
    }
}
