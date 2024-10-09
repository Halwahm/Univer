using System.Collections.Generic;
using System.Web.Http;

namespace PWS_Lab2.Controllers
{
    // Route: localhost:PORT/api/pws
    public class PwsController : ApiController
    {
        private static int _result = 0;
        private static readonly Stack<int> _stack = new Stack<int>();


        [HttpGet]
        public IHttpActionResult Get()
        {
            int result = (_stack.Count > 0) ? (_result + _stack.Peek()) : _result;
            return Ok(new { result });
        }

        [HttpPost]
        public IHttpActionResult Post([FromUri] string result)
        {
            if (!int.TryParse(result, out int resultParameter))
                return BadRequest("[ERROR] Enter integer parameter.");
            _result = resultParameter;
            return Ok();
        }

        [HttpPut]
        public IHttpActionResult Put([FromUri] string add)
        {
            if (!int.TryParse(add, out int addParameter))
                return BadRequest("[ERROR] Enter integer parameter.");
            _stack.Push(addParameter);
            return Ok();
        }

        [HttpDelete]
        public IHttpActionResult Delete()
        {
            if (_stack.Count <= 0)
                return BadRequest("[ERROR] Stack is empty.");
            _stack.Pop();
            return Ok();
        }
    }
}