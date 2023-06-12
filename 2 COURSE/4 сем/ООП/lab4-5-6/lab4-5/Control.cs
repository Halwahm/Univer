using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace lab4_5
{
    internal static class Control
    {
        public static BindingList<Product> BLProducts = new BindingList<Product>();
        public static List<Product> Products = new List<Product>();
        public static Product Product = new Product();
        public static List<Product> ProductsUndoRedo = new List<Product>();
        static DataContractJsonSerializer jsonS = new DataContractJsonSerializer(typeof(List<Product>));
        public static ListView listView = new ListView();

        public static void Loading(ListView _listView)
        {
            ReadFromFile();
            listView = _listView;
            RefreshList(Products);
        }

        public static void SaveToFile()
        {
            using (FileStream fs = new FileStream("Products.json", FileMode.Create))
            {
                jsonS.WriteObject(fs, Products);
            }
        }

        private static void ReadFromFile()
        {
            try
            {
                using (FileStream fs = new FileStream("Products.json", FileMode.Open))
                {
                    Products = (List<Product>)jsonS.ReadObject(fs);
                }
            }
            catch (Exception)
            {

            }
        }

        public static void AddProduct(Product Product)
        {
            Products.Add(Product);
            SaveToFile();
            RefreshList(Products);
        }

        public static void DeleteProduct()
        {
            Products.Remove(Product);
            SaveToFile();
            RefreshList(Products);
        }

        public static void RefreshList(List<Product> list)
        {
            BLProducts.Clear();
            foreach (var item in list)
            {
                BLProducts.Add(item);
            }
            listView.ItemsSource = BLProducts;
        }

        public static void Undo()
        {
            if (Products.Count != 0)
            {
                ProductsUndoRedo.Add(Products.Last());
                Products.RemoveAt(Products.Count - 1);
            }
            SaveToFile();
            RefreshList(Products);
        }

        public static void Redo()
        {
            if (ProductsUndoRedo.Count != 0)
            {
                Products.Add(ProductsUndoRedo.Last());
                ProductsUndoRedo.RemoveAt(ProductsUndoRedo.Count - 1);
            }
            SaveToFile();
            RefreshList(Products);
        }
    }
}
