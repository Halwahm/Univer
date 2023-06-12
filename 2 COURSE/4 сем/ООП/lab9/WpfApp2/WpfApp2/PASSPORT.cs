namespace WpfApp2
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("PASSPORT")]
    public partial class PASSPORT
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public PASSPORT()
        {
            PERSON = new HashSet<PERSON>();
        }

        [Key]
        public int id_passport { get; set; }

        [StringLength(20)]
        public string serial { get; set; }

        public int? number { get; set; }

        [Column(TypeName = "image")]
        public byte[] photo { get; set; }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<PERSON> PERSON { get; set; }
    }
}
