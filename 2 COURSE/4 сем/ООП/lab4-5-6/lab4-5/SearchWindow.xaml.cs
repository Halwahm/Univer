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
    /// Логика взаимодействия для SearchWindow.xaml
    /// </summary>
    public partial class SearchWindow : Window
    {
        public SearchWindow()
        {
            InitializeComponent();
        }

        private void SearchByName_Click(object sender, RoutedEventArgs e)
        {
            Search.SearchName(name.Text);
        }

        private void SearchByPrice_Click(object sender, RoutedEventArgs e)
        {
            Search.SearchPrice(price.Value);
        }

        private void SearchByTypeOfProduct_Click(object sender, RoutedEventArgs e)
        {
            Search.SearchTypeOfProduct(typeOfProduct.Text);
        }

        private void SearchByRating_Click(object sender, RoutedEventArgs e)
        {
            Search.SearchRating(Convert.ToDouble(rating.Text));
        }
    }
}
