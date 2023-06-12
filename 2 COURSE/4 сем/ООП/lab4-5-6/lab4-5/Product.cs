using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace lab4_5
{
    [Serializable]
    internal class Product

    {
        [DataMember]
        public double Price { get; set; }
        [DataMember]
        public string TypeOfProduct { get; set; }
        [DataMember]
        public double Rating { get; set; }
        [DataMember]
        public string Name { get; set; }
        [DataMember]
        public string PhotoPath { get; set; }
        [DataMember]
        public string Description { get; set; }

        public Product()
        {
            Price = 0;
            TypeOfProduct = "Default";
            Rating = 0;
            Name = "Default";
            PhotoPath = "";
            Description = "Default";
        }

        public Product(double price, string typeOfProduct, double rating, string name, string photoPath, string description)
        {
            Price = price;
            TypeOfProduct = typeOfProduct;
            Rating = rating;
            Name = name;
            PhotoPath = photoPath;
            Description = description;
        }

        public override string ToString()
        {
            return $"Название: {Name}, цена: {Price}";
        }
    }
}
