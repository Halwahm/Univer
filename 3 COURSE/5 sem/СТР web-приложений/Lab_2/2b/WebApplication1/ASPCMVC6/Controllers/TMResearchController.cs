using Microsoft.AspNetCore.Mvc;
using System.Globalization;
using static System.Net.Mime.MediaTypeNames;

namespace ASPCMVC6.Controllers
{
    public class TMResearchController : Controller
    {
        public string M01(string id)
        {
            ViewBag.Id = id;
            return $"GET:M01:/{id}";
        }

        public string M02(string id)
        {
            ViewBag.Id = id;
            return $"GET:M02:/{id}";
        }

        public string M03(string id)
        {
            ViewBag.Id = id;
            return $"GET:M03:/{id}";
        }

        public string MXX()
        {
            return $"GET:MXX:/";
        }
    }
}
