//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан по шаблону.
//
//     Изменения, вносимые в этот файл вручную, могут привести к непредвиденной работе приложения.
//     Изменения, вносимые в этот файл вручную, будут перезаписаны при повторном создании кода.
// </auto-generated>
//------------------------------------------------------------------------------

namespace SyndicationServiceLibrary
{
    using System;
    using System.Collections.Generic;
    
    public partial class note
    {
        public int id { get; set; }
        public Nullable<int> stud_id { get; set; }
        public string subject { get; set; }
        public Nullable<int> note1 { get; set; }
    
        public virtual student student { get; set; }
    }
}
