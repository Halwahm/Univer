using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lab8.Models
{
    public class ReqJsonRPC
    {
        public string Id { get; set; }
        public string JsonRPC { get; set; }
        public string Method { get; set; }
        public DataModel Params { get; set; }
    }
}