using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.DynamicData;
using System.Web.Http;
using System.Web.Mvc;
using System.Web.SessionState;
using Lab8.Models;

namespace Lab8.Controllers
{
    [SessionState(SessionStateBehavior.Required)]
    public class JRServiceController : ApiController
    {
        private static bool ignoreMethods = false;

        [System.Web.Http.HttpPut]
        public object[] Multi([FromBody] ReqJsonRPC[] body)
        {
            // принимает массив запросов JSON-RPC (ReqJsonRPC[])
            if (body == null)
            {
                throw new ArgumentNullException(nameof(body), "Request body is null");
            }

            int length = body.Length;
            object[] result = new object[length];
            bool methodsIgnored = false;

            for (int i = 0; i < length; i++)
            {
                if (methodsIgnored)
                {
                    result[i] = GetError(body[i].Id, body[i].JsonRPC, new ErrorJsonRPC
                    {
                        Code = -32601,
                        Message = "Methods are ignored after ErrorExit",
                        Data = null
                    });
                    continue;
                }

                // Каждый запрос обрабатывается через метод Single.
                var singleResult = Single(body[i]);
                result[i] = singleResult;

                // Если один из запросов содержит метод ErrorExit, текущая сессия очищается, а остальные методы игнорируются.
                if (body[i].Method == "ErrorExit")
                {
                    HttpContext.Current.Session.Clear();
                    methodsIgnored = true;
                }
            }

            return result;
        }

        [System.Web.Http.HttpPost]
        public object Single(ReqJsonRPC body)
        {
            // Проверяется, не включен ли режим игнорирования методов (ignoreMethods).
            if (ignoreMethods)
                return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = "Methods are not available", Code = -32601 });

            // Проверяется, что параметры (Params) и ключ (Key) не равны null.
            if (body.Params == null)
            {
                return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = "Params is null", Code = -32602 });
            }

            string method = body.Method;
            DataModel param = body.Params;

            string key = param.Key;
            if (key == null)
            {
                return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = "Key is null", Code = -32602 });
            }

            int value;
            try
            {
                value = int.Parse(param.Value == null || param.Value == "" ? "0" : param.Value);
            }
            catch (FormatException)
            {
                return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = "Invalid value format", Code = -32602 });
            }

            int? result = null;

            switch (method)
            {
                case "SetM":
                    {
                        result = SetM(key, value);
                        break;
                    }
                case "GetM":
                    {
                        result = GetM(key);
                        break;
                    }
                case "AddM":
                    {
                        result = AddM(key, value);
                        break;
                    }
                case "SubM":
                    {
                        result = SubM(key, value);
                        break;
                    }
                case "MulM":
                    {
                        result = MulM(key, value);
                        break;
                    }
                case "DivM":
                    {
                        if (value == 0)
                            return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = "Attempt to divide by zero", Code = -32602 });
                        result = DivM(key, value);
                        break;
                    }
                case "ErrorExit":
                    {
                        ErrorExit();
                        break;
                    }
                default:
                    {
                        return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = string.Format("Function {0} is not found", body.Method), Code = -32601 });
                    }
            }

            if (result == null)
            {
                return GetError(body.Id, body.JsonRPC, new ErrorJsonRPC { Message = "No result available", Code = -32603 });
            }

            return new ResJsonRPC()
            {
                Id = body.Id,
                JsonRPC = body.JsonRPC,
                Method = body.Method,
                Result = result
            };
        }


        ////////////////////////////////////
        private object GetError(string id, string jsonRPC, ErrorJsonRPC error)
        {
            return new ResJsonRPCError()
            {
                Id = id,
                JsonRPC = jsonRPC,
                Error = error
            };
        }
        ////////////////////////////////////
        private int? SetM(string k, int x)
        {
            HttpContext.Current.Session[k] = x;
            return GetM(k);
        }

        private int? GetM(string k)
        {
            object result = HttpContext.Current.Session[k];
            if (result == null)
                return null;
            else
                return int.Parse(result.ToString());
        }

        private int? AddM(string k, int x)
        {
            int? value = GetM(k);
            HttpContext.Current.Session[k] = value == null ? x : value + x;
            return GetM(k);
        }

        private int? SubM(string k, int x)
        {
            int? value = GetM(k);
            HttpContext.Current.Session[k] = value == null ? x : value - x;
            return GetM(k);
        }

        private int? MulM(string k, int x)
        {
            int? value = GetM(k);
            HttpContext.Current.Session[k] = value == null ? x : value * x;
            return GetM(k);
        }

        private int? DivM(string k, int x)
        {
            int? value = GetM(k);

            HttpContext.Current.Session[k] = value == null ? x : value / x;
            return GetM(k);
        }

        private void ErrorExit()
        {
            HttpContext.Current.Session.Clear();
            ignoreMethods = true;
        }
    }
}