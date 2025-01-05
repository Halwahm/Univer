using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lab8.Models
{
    public class ResJsonRPC
    {
        public string Id { get; set; }
        public string JsonRPC { get; set; }
        public string Method { get; set; }
        public int? Result { get; set; }
    }
}