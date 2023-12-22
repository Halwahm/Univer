using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Animation;
using WpfApp1.viewmodel;
using System.Security.Cryptography;

namespace WpfApp1
{
    public partial class loginWindow : Window
    {
        public static int IsAdmin;
        public static int UserID;
        public static courseEntities SushiDb;
        public static ModelMain _ModelMain;

        public loginWindow()
        {
            InitializeComponent();
            Loaded += LoginWindow_Loaded;
            SushiDb = new courseEntities();
            SushiDb.Category.Load();
            SushiDb.Comments.Load();
            SushiDb.Orders.Load();
            SushiDb.Products.Load();
            SushiDb.OrderDetails.Load();
            SushiDb.Comments.Load();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            textBoxEmail.Focus();
        }

        private void LoginWindow_Loaded(object sender, RoutedEventArgs e)
        {
            DoubleAnimation animation = new DoubleAnimation
            {
                From = 450,
                To = 100,
                AutoReverse = true,
                RepeatBehavior = RepeatBehavior.Forever,
                Duration = TimeSpan.FromSeconds(7)
            };

            signInButton.BeginAnimation(Button.WidthProperty, animation);
        }

        public static string HashPassword(string password)
        {
            using (SHA256 sha256 = SHA256.Create())
            {
                byte[] bytes = Encoding.UTF8.GetBytes(password);
                byte[] hash = sha256.ComputeHash(bytes);

                StringBuilder builder = new StringBuilder();
                for (int i = 0; i < hash.Length; i++)
                {
                    builder.Append(hash[i].ToString("x2"));
                }

                return builder.ToString();
            }
        }

        private void Button_Sign_Click(object sender, RoutedEventArgs e)
        {
            string userEmail = textBoxEmail.Text.Trim().ToLower();
            string userPassword = HashPassword(passwordBox.Password.Trim());

            if (userPassword.Length < 7)
            {
                passwordBox.ToolTip = "пароль слишком короткий";
                MessageBox.Show("ошибка в поле пароль");
                passwordBox.Focus();
            }
            else if (!userEmail.Contains("@mail.ru") && !userEmail.Contains("@gmail.com"))
            {
                textBoxEmail.ToolTip = "email должен содержать @mail.ru или @gmail.com";
                MessageBox.Show("ошибка в поле email");
                textBoxEmail.Focus();
            }
            else
            {
                textBoxEmail.ToolTip = "";
                passwordBox.ToolTip = "";

                var user = SushiDb.Clients.SingleOrDefault(c => 
                    c.Email == userEmail && c.PasswordHash == userPassword);

                if (user != null)
                {
                    UserID = user.ClientID;
                    if (user.Email == "admin@mail.ru")
                        IsAdmin = 1;
                    else 
                        IsAdmin = 0;
                    _ModelMain = new ModelMain(UserID, IsAdmin);
                    if (user.Email == "dostavka.2000@mail.ru")
                    {
                        CourierWindow toCourierWindow = new CourierWindow();
                        toCourierWindow.Show();
                        Hide();
                    }
                    else
                    {
                        SushiWindow toShushiWindow = new SushiWindow();
                        toShushiWindow.Show();
                        Hide();
                    }
                }
                else
                    MessageBox.Show("Некорректно введённые данные");
            }
        }

        private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                Button_Sign_Click(sender, e);
            }
        }

        private void To_sign_up_window(object sender, RoutedEventArgs e)
        {
            MainWindow toMainWindow = new MainWindow();
            toMainWindow.Show();
            Hide();

        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            Application.Current.Shutdown();
        }
    }
}
