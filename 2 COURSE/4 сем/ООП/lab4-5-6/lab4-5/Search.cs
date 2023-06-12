using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4_5
{
    internal static class Search
    {
        private static List<Product> _Products = new List<Product>();

        public static void SearchName(string name)
        {
            _Products.Clear();
            var list = Control.Products.Where(x => x.Name.Contains(name)).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }

        public static void SearchPrice(double price)
        {
            _Products.Clear();
            var list = Control.Products.Where(x => x.Price <= price).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }

        public static void SearchTypeOfProduct(string typeOfProduct)
        {
            _Products.Clear();
            var list = Control.Products.Where(x => x.TypeOfProduct.Contains(typeOfProduct)).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }

        public static void SearchRating(double rating)
        {
            _Products.Clear();
            var list = Control.Products.Where(x => x.Rating <= rating).Select(x => x);

            foreach (var Product in list)
            {
                _Products.Add(Product);
            }

            Control.RefreshList(_Products);
        }
    }
}
