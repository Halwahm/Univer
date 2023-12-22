using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Collections;
using Microsoft.Win32;
using WpfApp1.Annotations;
using System.Collections.Generic;
using WpfApp1.viewmodel;
using WpfApp1;
using System;
using System.Text;

namespace WpfApp1.viewmodel
{
    public partial class ModelMain
    {
        private Commands _delProductBasket;
        private Commands _addProductBasket;
        private Commands _showBasket;
        private double _fullPrice = 0;
        private Visibility _visibilityFrameBasket = Visibility.Hidden;
        private ObservableCollection<Products> _basketProduct = new ObservableCollection<Products> { };
        private Commands _acceptOrder;
        private Commands _clearBasket;

        public Commands AcceptOrder
        {
            get
            {
                return _acceptOrder ??
                    (_acceptOrder = new Commands(obj =>
                    {
                        StringBuilder productNames = new StringBuilder();
                        foreach (var product in _basketProduct)
                        {
                            productNames.Append(product.product_name);
                            productNames.Append("; ");
                        }
                        int index;
                        Orders order = new Orders();
                        order.TotalPrice = (decimal)FullPrice;
                        order.ClientID = loginWindow.UserID;
                        order.Status = "Доставляется";
                        order.ProductName = productNames.ToString();

                        string clientAddress = loginWindow.SushiDb.Clients
                            .Where(client => client.ClientID == order.ClientID)
                            .Select(client => client.Address)
                            .FirstOrDefault();

                        if (loginWindow.SushiDb.Orders.Count() != 0)
                        {
                            int maxOrderId = loginWindow.SushiDb.Orders.Max(o => o.OrderID);
                            order.OrderID = maxOrderId + 1;
                        }
                        else
                            order.OrderID = 0;

                        if (loginWindow.SushiDb.OrderDetails.Local.Count() != 0)
                            index = loginWindow.SushiDb.OrderDetails.Local.Last().DetailID + 1;
                        else
                            index = 0;

                        foreach (var product in _basketProduct)
                        {
                            var orderDetails = new OrderDetails();
                            orderDetails.ProductID = product.ProductID;
                            orderDetails.OrderID = order.OrderID;
                            orderDetails.DetailID = index++;
                            orderDetails.Address = clientAddress;
                            loginWindow.SushiDb.OrderDetails.Add(orderDetails);
                            order.OrderDetails.Add(orderDetails);
                            order.Amount = product.product_quantity;
                        }
                        _orderedProducts.Add(order);
                        if (_orderedProducts != null)
                            MessageBox.Show("Заказ оформлен");

                        loginWindow.SushiDb.Orders.Add(order);
                        loginWindow.SushiDb.SaveChanges();

                        BasketProduct.Clear();
                        FullPrice = 0;
                    }));
            }
        }

        public Commands ClearBasket
        {
            get
            {
                return _clearBasket ??
                    (_clearBasket = new Commands(obj =>
                    {
                        if (_basketProduct.Count != 0)
                            _basketProduct.Clear();
                        FullPrice = 0;
                    }));
            }
        }

        public double FullPrice
        {
            get => _fullPrice;
            set
            {
                _fullPrice = value;
                OnPropertyChanged("FullPrice");
            }

        }
        public Visibility VisibilityFrameBasket
        {
            get => _visibilityFrameBasket;
            set
            {
                _visibilityFrameBasket = value;
                OnPropertyChanged("VisibilityFrameBasket");
            }
        }

        public ObservableCollection<Products> BasketProduct
        {
            get => _basketProduct;
            set
            {
                _basketProduct = value;
                OnPropertyChanged("BasketProduct");
            }
        }

        public Commands AddBasket
        {
            get
            {
                return _addProductBasket ??
                    (_addProductBasket = new Commands(obj =>
                    {
                        Products newProduct = new Products
                        {
                            product_name = SelectedProduct.product_name,
                            price = SelectedProduct.price,
                            product_quantity = SelectedProduct.product_quantity
                        };

                        BasketProduct.Add(newProduct);

                        FullPrice += newProduct.price * newProduct.product_quantity;
                    }));
            }
        }


        public Commands DelBasket
        {
            get
            {
                return _delProductBasket ??
                    (_delProductBasket = new Commands(obj =>
                    {
                        BasketProduct.Remove(SelectedProduct);
                    }));
            }
        }
        public Commands ShowBasket
        {
            get
            {
                return _showBasket ??
                    (_showBasket = new Commands(obj =>
                    {
                        if (VisibilityFrameBasket == Visibility.Hidden)
                        {
                            VisibilityFrameBasket = Visibility.Visible;

                        }
                        else
                            VisibilityFrameBasket = Visibility.Hidden;
                    }));
            }
        }
    }
}