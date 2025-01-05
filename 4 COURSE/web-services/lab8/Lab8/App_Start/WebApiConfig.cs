using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Http;
using Newtonsoft.Json;

namespace Lab8.App_Start
{
    public static class WebApiConfig
    {
        public static void Register(HttpConfiguration config)
        {
            // Конфигурация и службы веб-API

            // Игнорировать свойства со значением null
            config.Formatters.JsonFormatter.SerializerSettings.NullValueHandling = NullValueHandling.Ignore;
            // Красивое форматирование JSON
            config.Formatters.JsonFormatter.SerializerSettings.Formatting = Formatting.Indented;
            // Избежать циклических ссылок
            config.Formatters.JsonFormatter.SerializerSettings.ReferenceLoopHandling = ReferenceLoopHandling.Ignore;


            // Маршруты веб-API. Включить маршруты на основе атрибутов [Route]
            config.MapHttpAttributeRoutes();

            // Определить маршрут по умолчанию для Web API
            config.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}", // Шаблон URL
                defaults: new { id = RouteParameter.Optional }  // Параметр id необязателен
            );
        }
    }
}