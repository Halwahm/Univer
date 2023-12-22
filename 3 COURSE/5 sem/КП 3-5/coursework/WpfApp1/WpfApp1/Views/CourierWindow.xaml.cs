using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using WpfApp1.viewmodel;

namespace WpfApp1
{
    public partial class CourierWindow : Window
    {
        private Delivery _delivery;
        public CourierWindow()
        {
            InitializeComponent();
            _delivery = new Delivery();
            DataContext = _delivery;
        }

        private void DeliveredButton_Click(object sender, RoutedEventArgs e)
        {
            var button = (Button)sender;
            var dataContext = button.DataContext;

            if (dataContext is Orders selectedOrder)
            {
                using (var dbContext = new courseEntities())
                {
                    var existingOrder = dbContext.Orders.FirstOrDefault(o => o.OrderID == selectedOrder.OrderID);
                    if (existingOrder != null)
                    {
                        existingOrder.Status = "Доставлен";
                        dbContext.SaveChanges();

                        var delivery = (Delivery)DataContext;
                        delivery.OrderList.Remove(selectedOrder);
                    }
                }
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            Application.Current.Shutdown();
        }
    }
}
