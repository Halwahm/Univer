using System.Collections.Generic;
using System.Linq;
using System;
using System.Net;
using System.Web.Http;
using System.Xml.Linq;
using RouteAttribute = System.Web.Http.RouteAttribute;
using RoutePrefixAttribute = System.Web.Http.RoutePrefixAttribute;

namespace lab3.Controllers
{
    [RoutePrefix("api/errors")]
    public class ErrorsController : ApiController
    {
        [HttpGet]
        [Route("{statusCode:int}")]
        public IHttpActionResult GetErrorDetails(int statusCode, string action = null, string errorMessage = null)
        {
            try
            {
                var errorMessages = new Dictionary<int, string>
                {
                    { 400, "Bad Request. The server could not understand the request due to invalid syntax." },
                    { 401, "Unauthorized. Access is denied due to invalid credentials." },
                    { 403, "Forbidden. You do not have permission to access this resource." },
                    { 404, "Not Found. The requested resource could not be found." },
                    { 500, "Internal Server Error. The server encountered an unexpected condition." }
                };

                string defaultMessage = errorMessages.ContainsKey(statusCode)
                    ? errorMessages[statusCode]
                    : "Unknown error occurred.";

                var responseMessage = !string.IsNullOrEmpty(errorMessage) ? $"{defaultMessage} Details: {errorMessage}" : defaultMessage;

                var response = new
                {
                    StatusCode = statusCode,
                    Message = responseMessage,
                    Links = new
                    {
                        Self = $"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/errors/{statusCode}?action={action ?? "GetErrorDetails"}&errorMessage={Uri.EscapeDataString(errorMessage ?? string.Empty)}"
                    }
                };

                if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
                {
                    return Content((HttpStatusCode)statusCode, new XElement("ErrorDetails",
                        new XElement("StatusCode", statusCode),
                        new XElement("Message", responseMessage),
                        new XElement("Links",
                            new XElement("Self", response.Links.Self)
                        )
                    ));
                }

                return Content((HttpStatusCode)statusCode, response);
            }
            catch (Exception ex)
            {
                return InternalServerError(new Exception("An unexpected error occurred while processing the request.", ex));
            }
        }

    }
}
