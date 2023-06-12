using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace lab4_5
{
    public interface IOperation
    {
        void Execute();
        public bool IsComplited { get; }
    }

    internal class Operations : Collection<IOperation> { }

    internal class OperationManager
    {
        static public OperationManager Instance;
        static OperationManager() => Instance = new OperationManager();
        private Operations operations;
        private OperationManager() => operations = new();

        public void AddOperation(IOperation operation) => operations.Add(operation);

        public void ProcessOperations()
        {
            operations.Where(op => !op.IsComplited)
                        .ToList()
                        .ForEach(op => op.Execute());
        }
    }

    internal class ChangeProducts : IOperation
    {
        private readonly Product Product;
        private readonly Product ProductChanged;
        private bool isComplited;
        public bool IsComplited { get => isComplited; }

        public ChangeProducts(Product Product, Product ProductChanged)
        {
            this.Product = Product;
            this.ProductChanged = ProductChanged;
            isComplited = false;
        }

        public void Execute()
        {
            Product.Name = ProductChanged.Name;
            Product.Price = ProductChanged.Price;
            Product.Description = ProductChanged.Description;
            Product.TypeOfProduct = ProductChanged.TypeOfProduct;
            Product.Rating = ProductChanged.Rating;
            Product.PhotoPath = ProductChanged.PhotoPath;

            isComplited = true;
        }
    }
}
