using lab3.Context;
using lab3.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using System.Xml.Linq;
using HttpDeleteAttribute = System.Web.Http.HttpDeleteAttribute;
using HttpGetAttribute = System.Web.Http.HttpGetAttribute;
using HttpPostAttribute = System.Web.Http.HttpPostAttribute;
using HttpPutAttribute = System.Web.Http.HttpPutAttribute;
using RouteAttribute = System.Web.Http.RouteAttribute;
using RoutePrefixAttribute = System.Web.Http.RoutePrefixAttribute;

namespace lab3.Controllers
{
    [RoutePrefix("api/students")]
    public class StudentsController : ApiController
    {
        private readonly StudentDbContext _dbContext = new StudentDbContext();

        [HttpGet]
        [Route("")]
        public IHttpActionResult FetchStudents(int limit = 10, string sort = null, int offset = 0,
            int? minid = null, int? maxid = null, string like = null, string columns = null)
        {
            try
            {
                var query = _dbContext.Students.AsQueryable();

                query = ApplyFilters(query, minid, maxid, like);
                query = ApplySorting(query, sort);
                query = ApplyPagination(query, offset, limit);

                var students = query.ToList();
                var studentList = CreateHateoasLinks(students);

                if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
                {
                    return Ok(new XElement("Students",
                        students.Select(s => new XElement("Student",
                            new XElement("ID", s.ID),
                            new XElement("Name", s.Name),
                            new XElement("Phone", s.Phone),
                            new XElement("Links",
                                new XElement("Self", $"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/students/{s.ID}"),
                                new XElement("Edit", $"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/students/{s.ID}"),
                                new XElement("Delete", $"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/students/{s.ID}"),
                                new XElement("AllStudents", $"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/students")
                            )
                        ))
                    ));
                }

                return Ok(studentList);
            }
            catch (Exception ex)
            {
                return CreateErrorResponse(HttpStatusCode.InternalServerError, ex.Message);
            }
        }

        private IQueryable<Student> ApplyFilters(IQueryable<Student> query, int? minid, int? maxid, string like)
        {
            if (minid.HasValue) query = query.Where(s => s.ID >= minid.Value);
            if (maxid.HasValue) query = query.Where(s => s.ID <= maxid.Value);
            if (!string.IsNullOrEmpty(like)) query = query.Where(s => s.Name.Contains(like));
            return query;
        }

        private IQueryable<Student> ApplySorting(IQueryable<Student> query, string sort)
        {
            return !string.IsNullOrEmpty(sort) && sort.ToUpper() == "NAME"
                ? query.OrderBy(s => s.Name)
                : query.OrderBy(s => s.ID);
        }

        private IQueryable<Student> ApplyPagination(IQueryable<Student> query, int offset, int limit)
        {
            return query.Skip(offset).Take(limit);
        }

        private IEnumerable<object> CreateHateoasLinks(List<Student> students)
        {
            var baseUri = new Uri($"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/students");

            return students.Select(s => new
            {
                s.ID,
                s.Name,
                s.Phone,
                links = new
                {
                    self = $"{baseUri}/{s.ID}",
                    edit = $"{baseUri}/{s.ID}",
                    delete = $"{baseUri}/{s.ID}",
                    all_students = $"{baseUri}"
                }
            });
        }

        [HttpGet]
        [Route("{id:int}")]
        public IHttpActionResult GetStudentById(int id)
        {
            var student = _dbContext.Students.Find(id);
            if (student == null) return CreateErrorResponse(HttpStatusCode.NotFound, "Student not found");

            var baseUri = new Uri($"{Request.RequestUri.Scheme}://{Request.RequestUri.Host}:{Request.RequestUri.Port}/api/students");

            var response = new
            {
                data = student,
                links = new
                {
                    self = $"{baseUri}/{id}",
                    edit = $"{baseUri}/{id}",
                    delete = $"{baseUri}/{id}",
                    all_students = $"{baseUri}"
                }
            };

            if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
            {
                return Ok(new XElement("Student",
                    new XElement("ID", student.ID),
                    new XElement("Name", student.Name),
                    new XElement("Phone", student.Phone),
                    new XElement("Links",
                        new XElement("Self", $"{baseUri}/{id}"),
                        new XElement("Edit", $"{baseUri}/{id}"),
                        new XElement("Delete", $"{baseUri}/{id}"),
                        new XElement("AllStudents", $"{baseUri}")
                    )
                ));
            }

            return Ok(response);
        }

        [HttpPost]
        [Route("")]
        public IHttpActionResult CreateNewStudent(Student student)
        {
            if (!ModelState.IsValid) return CreateErrorResponse(HttpStatusCode.BadRequest, "Invalid data provided.");

            _dbContext.Students.Add(student);
            _dbContext.SaveChanges();

            if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
            {
                return Created("api/students", new XElement("Student",
                    new XElement("ID", student.ID),
                    new XElement("Name", student.Name),
                    new XElement("Phone", student.Phone)
                ));
            }

            return Created("api/students", student);
        }

        [HttpPut]
        [Route("{id:int}")]
        public IHttpActionResult ModifyStudent(int id, Student student)
        {
            if (!ModelState.IsValid) return CreateErrorResponse(HttpStatusCode.BadRequest, "Invalid data provided.");

            var existingStudent = _dbContext.Students.Find(id);
            if (existingStudent == null) return CreateErrorResponse(HttpStatusCode.NotFound, "Student not found");

            existingStudent.Name = student.Name;
            existingStudent.Phone = student.Phone;
            _dbContext.SaveChanges();

            if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
            {
                return Ok(new XElement("Message", "Student updated successfully"));
            }

            return StatusCode(HttpStatusCode.NoContent);
        }

        [HttpDelete]
        [Route("{id:int}")]
        public IHttpActionResult RemoveStudent(int id)
        {
            var student = _dbContext.Students.Find(id);
            if (student == null) return CreateErrorResponse(HttpStatusCode.NotFound, "Student not found");

            _dbContext.Students.Remove(student);
            _dbContext.SaveChanges();

            if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
            {
                return Ok(new XElement("Message", "Student deleted successfully"));
            }

            return StatusCode(HttpStatusCode.NoContent);
        }

        private IHttpActionResult CreateErrorResponse(HttpStatusCode statusCode, string message)
        {
            if (Request.Headers.Accept.Any(a => a.MediaType == "application/xml"))
            {
                return Content(statusCode, new XElement("Error",
                    new XElement("Message", message),
                    new XElement("Link", Url.Link("DefaultApi", new { controller = "errors", action = "GetErrorDetails", id = (int)statusCode }))
                ));
            }

            return Content(statusCode, new
            {
                error = message,
                links = new
                {
                    self = Url.Link("DefaultApi", new { controller = "errors", action = "GetErrorDetails", id = (int)statusCode })
                }
            });
        }
    }
}
