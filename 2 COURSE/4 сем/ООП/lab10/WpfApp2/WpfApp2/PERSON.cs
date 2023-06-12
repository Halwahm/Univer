namespace WpfApp2
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("PERSON")]
    public partial class PERSON
    {
        [Key]
        public int id_person { get; set; }

        [StringLength(10)]
        public string first_name { get; set; }

        [StringLength(10)]
        public string middle_name { get; set; }

        [StringLength(10)]
        public string last_name { get; set; }

        public int? age { get; set; }

        [StringLength(10)]
        public string phone { get; set; }

        [ForeignKey("ADDRESS")]
        public int? id_address { get; set; }
        
        [ForeignKey("PASSPORT")]
        public int? id_passport { get; set; }

        public virtual ADDRESS ADDRESS { get; set; }

        public virtual PASSPORT PASSPORT { get; set; }
    }
}
