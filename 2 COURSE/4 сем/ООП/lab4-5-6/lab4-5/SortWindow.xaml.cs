using System;
using System.Collections.Generic;
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

namespace lab4_5
{
    /// <summary>
    /// Логика взаимодействия для SortWindow.xaml
    /// </summary>
    public partial class SortWindow : Window
    {
        public SortWindow()
        {
            InitializeComponent();
        }

        private void sortName_Click(object sender, RoutedEventArgs e)
        {
            Sort.SortName();
        }

        private void sortRating_Click(object sender, RoutedEventArgs e)
        {
            Sort.SortRating();
        }

        private void sortTypeOfProduct_Click(object sender, RoutedEventArgs e)
        {
            Sort.SortTypeOfProduct();
        }

        private void sortPrice_Click(object sender, RoutedEventArgs e)
        {
            Sort.SortPrice();
        }
    }
}
