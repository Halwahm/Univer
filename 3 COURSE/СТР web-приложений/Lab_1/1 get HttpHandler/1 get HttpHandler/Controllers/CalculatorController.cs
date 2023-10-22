using Microsoft.AspNetCore.Mvc;

namespace _1_get_HttpHandler.Controllers
{
    [Route("api/calculator")]
    [ApiController]
    public class CalculatorController : ControllerBase
    {
/*        [HttpPost]  // 4 task
        [Route("add")]
        public IActionResult Add([FromBody] NumbersRequest request)
        {

            double sum = request.X + request.Y;
            return Ok(sum);
        }
*/

        [HttpGet]  // 5 task
        public IActionResult Get()
        {
            var filePath = Path.Combine(Directory.GetCurrentDirectory(), "wwwroot", "calculator.html");
            return PhysicalFile(filePath, "text/html");
        }

        [HttpPost]
        public IActionResult Post([FromBody] NumbersRequest request)
        {
            if (request == null)
            {
                return BadRequest("Invalid request body");
            }

            double result = request.X * request.Y;
            return Ok(result);
        }

        public class NumbersRequest
        {
            public double X { get; set; }
            public double Y { get; set; }
        }
    }
}

// http://localhost:5050  - for 4 task

// http://localhost:5050/api/calculator  - for 5 task