using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4_5
{
    internal class Sort
    {
        private static List<Product> _Products = new List<Product>();

        public static void SortName()
        {
            _Products.Clear();
            var list = Control.Products.OrderBy(x => x.Name).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }

        public static void SortPrice()
        {
            _Products.Clear();
            var list = Control.Products.OrderBy(x => x.Price).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }

        public static void SortTypeOfProduct()
        {
            _Products.Clear();
            var list = Control.Products.OrderBy(x => x.TypeOfProduct).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }

        public static void SortRating()
        {
            _Products.Clear();
            var list = Control.Products.OrderBy(x => x.Rating).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }
    }
}
