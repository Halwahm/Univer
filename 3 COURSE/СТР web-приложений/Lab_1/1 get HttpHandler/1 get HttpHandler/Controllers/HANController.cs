using Microsoft.AspNetCore.Mvc;

namespace _1_get_HttpHandler.Controllers
{
    [Route("api/HAN")]
    [ApiController]
    public class HanController : ControllerBase
    {

        [HttpGet]  // 1 task 
        public IActionResult GetHandler(string ParmA, string ParmB)
        {
            string response = $"GET-Http-HAN:ParmA = {ParmA},ParmB = {ParmB}";
            return Content(response, "text/plain");
        }

        [HttpPost]  // 2 task
        public IActionResult PostHandler(string ParmA, string ParmB)
        {
            string response = $"POST-Http-HAN:ParmA = {ParmA},ParmB = {ParmB}";
            return Content(response, "text/plain");
        }

        [HttpPut]  // 3 task
        public IActionResult PUTHandler(string ParmA, string ParmB)
        {
            string response = $"PUT-Http-HAN:ParmA = {ParmA},ParmB = {ParmB}";
            return Content(response, "text/plain");
        }

    }
}

// localhost:5050/api/HAN?ParmA=aaa&ParmB=bbb