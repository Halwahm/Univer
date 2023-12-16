using Microsoft.AspNetCore.Mvc;
using System;
using System.Globalization;
using System.Text.RegularExpressions;

namespace ASPCMVC7.Controllers
{
    public class TAResearchController : Controller
    {
        [HttpGet]
        [Route("it/{num:int}/{str}")]
        public string M04(int num, string str)
        {
            ViewBag.num = num;
            ViewBag.str = str;
            return $"GET:M04:/{num}/{str}";
        }

        [HttpGet]
        [Route("it/{flag:bool}/{let}")]
        public string M05(bool flag, string let)
        {
            ViewBag.flag = flag;
            ViewBag.let = let;
            return $"GET:M05:/{flag}/{let}";
        }

        [HttpPost]
        [Route("it/{flag:bool}/{let}")]
        public string M05_1(bool flag, string let)
        {
            ViewBag.flag = flag;
            ViewBag.let = let;
            return $"POST:M05:/{flag}/{let}";
        }

        [HttpGet]
        [Route("it/{fl:float}/{str:minlength(2):maxlength(5)}")]
        public string M06(float fl, string str)
        {
            ViewBag.fl = fl;
            ViewBag.str = str;
            return $"GET:M06:/{fl}/{str}";
        }

        [HttpDelete]
        [Route("it/{fl:float}/{str:minlength(2):maxlength(5)}")]
        public string M06_1(float fl, string str)
        {
            ViewBag.fl = fl;
            ViewBag.str = str;
            return $"DELETE:M06:/{fl}/{str}";
        }

        [HttpPut]
        [Route("it/{str:minlength(3):maxlength(4)}/{num:int:min(100):max(200)}")]
        public string M07(string str, int num)
        {
            ViewBag.num = num;
            ViewBag.str = str;
            return $"PUT:M07:/{str}/{num}";
        }

        [HttpPost]
        [Route("it/{mail:regex(^\\w+([[-+.']]\\w+)*@\\w+([[-.]]\\w+)*\\.\\w+([[-.]]\\w+)*$)}")]
        public string M08(string mail)
        {
            ViewBag.mail = mail;
            return $"POST:M08:/{mail}";
        }
    }
}
