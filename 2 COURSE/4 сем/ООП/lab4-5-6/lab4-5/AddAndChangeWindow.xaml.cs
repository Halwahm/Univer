using Microsoft.Win32;
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
    /// Логика взаимодействия для AddAndChangeWindow.xaml
    /// </summary>
    /// 
    public partial class AddAndChangeWindow : Window
    {
        OpenFileDialog openFileDialog = new OpenFileDialog();

        public AddAndChangeWindow()
        {
            InitializeComponent();
            openFileDialog.Filter = "Фотографии|*.jpg;*.png;*.jpeg;";
        }

        private void OpenExplorer(object sender, RoutedEventArgs e)
        {
            if (openFileDialog.ShowDialog() == true)
            {
                try
                {
                    ProductsPhoto.Source = new BitmapImage(new Uri(openFileDialog.FileName, UriKind.Absolute));
                }
                catch
                {
                    MessageBox.Show("Выберите файл формата", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void addProduct_Click(object sender, RoutedEventArgs e)
        {
            Product Product = new Product();

            Product.Name = name.Text;
            
            Product.Price = Convert.ToDouble(price.Text);
            Product.TypeOfProduct = typeOfProduct.Text;
            Product.Rating = Math.Round(rating.Value, 2);
            Product.PhotoPath = openFileDialog.FileName;
            Product.Description = description.Text;

            Control.AddProduct(Product);
            Close();
        }
    }
}
