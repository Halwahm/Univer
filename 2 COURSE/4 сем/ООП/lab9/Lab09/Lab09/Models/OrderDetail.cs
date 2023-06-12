﻿using System;
using System.Collections.Generic;

namespace Lab09.Models;

public partial class OrderDetail
{
    public int OrderId { get; set; }

    public string ProductName { get; set; } = null!;

    public int Quantity { get; set; }

    public decimal Price { get; set; }

    public virtual Order Order { get; set; } = null!;
}
