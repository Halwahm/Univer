//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан по шаблону.
//
//     Изменения, вносимые в этот файл вручную, могут привести к непредвиденной работе приложения.
//     Изменения, вносимые в этот файл вручную, будут перезаписаны при повторном создании кода.
// </auto-generated>
//------------------------------------------------------------------------------

namespace WpfApp1
{
    using System;
    using System.Collections.Generic;
    
    public partial class Comments
    {
        public int CommentID { get; set; }
        public Nullable<int> ProductID { get; set; }
        public Nullable<int> ClientID { get; set; }
        public string CommentText { get; set; }
    
        public virtual Clients Clients { get; set; }
        public virtual Products Products { get; set; }
    }
}
