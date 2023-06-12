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
    /// Логика взаимодействия для Change
    /// .xaml
    /// </summary>
    public partial class ChangeProduct : Window
    {
        OpenFileDialog openFileDialog = new OpenFileDialog();
        OperationManager manager = OperationManager.Instance;

        public ChangeProduct()
        {
            InitializeComponent();
            openFileDialog.Filter = "Фотографии|*.jpg;*.png;*.jpeg;";

            name.Text = Control.Product.Name;
            price.Text = Convert.ToString(Control.Product.Price);
            typeOfProduct.Text = Control.Product.TypeOfProduct;
            rating.Value = Convert.ToDouble(Control.Product.Rating);
            description.Text = Control.Product.Description;
            ProductsPhoto.Source = new BitmapImage(new Uri(Control.Product.PhotoPath, UriKind.Absolute));
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
            Product Product = new Product(Convert.ToDouble(price.Text), typeOfProduct.Text, Math.Round(rating.Value, 2),
                                        name.Text, Control.Product.PhotoPath, description.Text);

            manager.AddOperation(new ChangeProducts(Control.Products[Control.Products.IndexOf(Control.Product)], Product));
            manager.ProcessOperations();
            Control.SaveToFile();
            Control.RefreshList(Control.Products);

            Close();
        }
    }
}
