using lab3.Context;
using lab3.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using System.Web.Mvc;
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

                return Ok(studentList);
            }
            catch (Exception ex)
            {
                return InternalServerError(ex);
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
            return students.Select(s => new
            {
                s.ID,
                s.Name,
                s.Phone,
                links = new
                {
                    self = Url.Link("DefaultApi", new { controller = "students", id = s.ID })
                }
            });
        }

        [HttpGet]
        [Route("{id:int}")]
        public IHttpActionResult GetStudentById(int id)
        {
            var student = _dbContext.Students.Find(id);
            if (student == null) return NotFound();

            var response = new
            {
                data = student,
                links = new
                {
                    self = Url.Link("DefaultApi", new { controller = "students", id }),
                    all_students = Url.Link("DefaultApi", new { controller = "students" })
                }
            };

            return Ok(response);
        }

        [HttpPost]
        [Route("")]
        public IHttpActionResult CreateNewStudent(Student student)
        {
            if (!ModelState.IsValid) return BadRequest(ModelState);

            _dbContext.Students.Add(student);
            _dbContext.SaveChanges();

            return Created("api/students", student);
        }

        [HttpPut]
        [Route("{id:int}")]
        public IHttpActionResult ModifyStudent(int id, Student student)
        {
            if (!ModelState.IsValid) return BadRequest(ModelState);

            var existingStudent = _dbContext.Students.Find(id);
            if (existingStudent == null) return NotFound();

            existingStudent.Name = student.Name;
            existingStudent.Phone = student.Phone;
            _dbContext.SaveChanges();

            return StatusCode(HttpStatusCode.NoContent);
        }

        [HttpDelete]
        [Route("{id:int}")]
        public IHttpActionResult RemoveStudent(int id)
        {
            var student = _dbContext.Students.Find(id);
            if (student == null) return NotFound();

            _dbContext.Students.Remove(student);
            _dbContext.SaveChanges();

            return StatusCode(HttpStatusCode.NoContent);
        }
    }
}
