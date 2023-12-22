using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using WpfApp1.Annotations;

namespace WpfApp1.viewmodel
{
    public class Delivery : INotifyPropertyChanged
    {
        private ObservableCollection<Orders> _orderList;
        public ObservableCollection<Orders> OrderList
        {
            get { return _orderList; }
            set
            {
                if (_orderList != value)
                {
                    _orderList = value;
                    NotifyPropertyChanged("OrderList");
                }
            }
        }

        public Delivery()
        {
            LoadOrders();
        }

        public void LoadOrders()
        {
            using (var context = new courseEntities())
            {
                OrderList = new ObservableCollection<Orders>(
                    context.Orders
                           .Include("Clients")
                           .Where(order => order.Status == "Доставляется")
                           .ToList()
                );
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void NotifyPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}