using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SyndicationServiceLibrary
{
    public class NoteResponse
    {
        [JsonProperty("value")]
        public List<Note> Value { get; set; }
    }

    public class Note
    {
        [JsonProperty("subject")]
        public string Subj { get; set; }

        [JsonProperty("note1")]
        public string Note1 { get; set; }
    }

}
