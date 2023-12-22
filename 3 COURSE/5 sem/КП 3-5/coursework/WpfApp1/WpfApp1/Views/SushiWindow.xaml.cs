using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApp1
{
    public partial class SushiWindow : Window
    {
        public static courseEntities SushiDb;
        public SushiWindow()
        {
            InitializeComponent();
            DataContext = loginWindow._ModelMain;

            if (loginWindow.IsAdmin == 1)
            {
                loginWindow._ModelMain.AdminPanel = 320;
            }
            else
            {
                loginWindow._ModelMain.AdminPanel = 0;
            }

            Closed += (sender, args) =>
            {
                loginWindow.SushiDb.SaveChanges();
            };
        }

        private void SushiWindow_Closed(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            Application.Current.Shutdown();
        }

        private void Changing_user(object sender, RoutedEventArgs e)
        {
            loginWindow toLoginWindow = new loginWindow();
            toLoginWindow.Show();
            Hide();
        }
    }
    public class NonNegativeValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            if (decimal.TryParse(value as string, out decimal result))
            {
                if (result < 0)
                {
                    return new ValidationResult(false, "Цена не может быть отрицательной");
                }
            }
            return ValidationResult.ValidResult;
        }
    }
}
