using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Controls;

namespace WpfApp1.viewmodel
{
    partial class ModelMain
    {
        private Commands _showOrdered;
        private Orders _orderedProduct;
        private Visibility _visibilityFrameOrdered = Visibility.Hidden;
        private Commands _delOrdered;
        private ObservableCollection<Orders> _orderedProducts = new ObservableCollection<Orders> { };

        public ModelMain(int userId, int isAdmin) 
        {
            using (var context = new courseEntities())
            {
                if (isAdmin == 1)
                {
                    OrderedProducts = new ObservableCollection<Orders>(context.Orders
                        .Where(o => o.Status.ToUpper() == "Доставляется")
                        .ToList());
                }
                else
                {
                    OrderedProducts = new ObservableCollection<Orders>(context.Orders
                        .Where(o => o.ClientID == userId && o.Status.ToUpper() == "Доставляется")
                        .ToList());
                }
            }
        }

        public Visibility VisibilityFrameOrdered
        {
            get => _visibilityFrameOrdered;
            set
            {
                _visibilityFrameOrdered = value;
                OnPropertyChanged("VisibilityFrameOrdered");
            }
        }

        public Orders OrderedProduct
        {
            get => _orderedProduct;
            set
            {
                if (value != null)
                {
                    _orderedProduct = value;
                    OnPropertyChanged("OrderedProduct");
                }
            }
        }

        public ObservableCollection<Orders> OrderedProducts
        {
            get => _orderedProducts;
            set
            {
                _orderedProducts = value;
                OnPropertyChanged("OrderedProducts");
            }
        }

        public Commands DelOrdered
        {
            get
            {
                return _delOrdered ??
                    (_delOrdered = new Commands(obj =>
                    {
                        if (obj is Orders selectedOrder)
                        {
                            using (var dbContext = new courseEntities())
                            {
                                var existingOrder = dbContext.Orders
                                    .Include("OrderDetails")
                                    .FirstOrDefault(o => o.OrderID == selectedOrder.OrderID);

                                if (existingOrder != null)
                                {
                                    existingOrder.Status = "Отменён";
                                    dbContext.SaveChanges();
                                    OrderedProducts.Remove(selectedOrder);
                                    OnPropertyChanged("OrderedProducts");
                                }
                            }
                        }
                    }));
            }
        }

        public Commands ShowOrdered
        {
            get
            {
                return _showOrdered ??
                    (_showOrdered = new Commands(obj =>
                    {
                        if (VisibilityFrameOrdered == Visibility.Hidden)
                        {
                            VisibilityFrameOrdered = Visibility.Visible;
                        }
                        else
                        {
                            VisibilityFrameOrdered = Visibility.Hidden;
                        }
                    }));
            }
        }
    }
}
