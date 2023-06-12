using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace WpfApp2
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private ObservableCollection<Product> _products;
        private ObservableCollection<Product> _cart;
        private ICommand _addToCartCommand;
        private ICommand _removeFromCartCommand;

        public ObservableCollection<Product> Products
        {
            get => _products;
            set
            {
                _products = value;
                OnPropertyChanged(nameof(Products));
            }
        }

        public ObservableCollection<Product> Cart
        {
            get => _cart;
            set
            {
                _cart = value;
                OnPropertyChanged(nameof(Cart));
            }
        }

        public decimal TotalPrice => GetTotalPrice();

        public ICommand AddToCartCommand
        {
            get
            {
                if (_addToCartCommand == null)
                {
                    _addToCartCommand = new RelayCommand(
                        param => AddToCart(param as Product),
                        param => CanAddToCart(param as Product));
                }

                return _addToCartCommand;
            }
        }

        public ICommand RemoveFromCartCommand
        {
            get
            {
                if (_removeFromCartCommand == null)
                {
                    _removeFromCartCommand = new RelayCommand(
                        param => RemoveFromCart(param as Product),
                        param => CanRemoveFromCart(param as Product));
                }

                return _removeFromCartCommand;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public MainViewModel()
        {
            using (var db = new StoreContext())
            {
                Products = new ObservableCollection<Product>(db.Products.ToList());
            }
            Cart = new ObservableCollection<Product>();
        }

        public void AddToCart(Product product)
        {
            if (product == null)
            {
                return;
            }
            product.IsSelected = true;
            Cart.Add(product);
            OnPropertyChanged(nameof(TotalPrice));
        }

        public bool CanAddToCart(Product product)
        {
            return product != null && !product.IsSelected;
        }

        public void RemoveFromCart(Product product)
        {
            if (product == null)
            {
                return;
            }
            product.IsSelected = false;
            Cart.Remove(product);
            OnPropertyChanged(nameof(TotalPrice));
        }

        public bool CanRemoveFromCart(Product product)
        {
            return product != null && product.IsSelected;
        }

        public decimal GetTotalPrice()
        {
            return Cart.Sum(p => p.Price);
        }
    }
}
