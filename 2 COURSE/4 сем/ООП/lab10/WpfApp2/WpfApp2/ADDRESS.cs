namespace WpfApp2
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("ADDRESS")]
    public partial class ADDRESS
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public ADDRESS()
        {
            PERSON = new HashSet<PERSON>();
        }

        [Key]
        public int id_address { get; set; }

        [StringLength(20)]
        public string country { get; set; }

        [StringLength(20)]
        public string city { get; set; }

        [StringLength(20)]
        public string street { get; set; }

        public int? house { get; set; }

        public int? build { get; set; }

        public int? flat { get; set; }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<PERSON> PERSON { get; set; }
    }
}
