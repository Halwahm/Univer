using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Text.RegularExpressions;

namespace WpfApp1
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Loaded += loginWindow_Loaded;
        }

        private void loginWindow_Loaded(object sender, RoutedEventArgs e)
        {
            DoubleAnimation animation = new DoubleAnimation
            {
                From = 450,
                To = 180,
                AutoReverse = true,
                RepeatBehavior = RepeatBehavior.Forever,
                Duration = TimeSpan.FromSeconds(7)
            };

            registerButton.BeginAnimation(Button.WidthProperty, animation);
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

        public bool IsValidPhoneNumber(string phoneNumber)
        {
            phoneNumber = phoneNumber.Replace(" ", "").Replace("-", "");
            foreach (char c in phoneNumber)
            {
                if (!char.IsDigit(c))
                {
                    return false;
                }
            }
            Regex regex = new Regex(@"^\+?(?:\d{10,14})$");
            return regex.IsMatch(phoneNumber);
        }

        private void Button_Register(object sender, RoutedEventArgs e)
        {
            string userEmail = textBoxEmail.Text.Trim().ToLower();
            string userName = textBoxName.Text.Trim();
            string userLastName = textBoxLastName.Text.Trim();
            string userAddress = textBoxAddress.Text.Trim();
            string userPhone = textBoxPhoneNumber.Text.Trim();
            string userPassword = passwordBox.Password.ToString();
            string userPassword2 = passwordBox2.Password.Trim().ToString();

            if (userName.Length < 2)
            {
                textBoxName.ToolTip = "Имя слишком короткое";
                MessageBox.Show("Ошибка в поле имя");
                textBoxName.Focus();
                return;
            }
            else if (userLastName.Length < 3)
            {
                textBoxLastName.ToolTip = "Фамилия слишком короткая";
                MessageBox.Show("Ошибка в поле Фамилия");
                textBoxLastName.Focus();
                return;
            }
            else if (userAddress.Length < 5)
            {
                textBoxAddress.ToolTip = "Адрес слишком короткий";
                MessageBox.Show("Ошибка в поле Адресс");
                textBoxAddress.Focus();
                return;
            }
/*            else if (userPhone.Length != 12)
            {
                textBoxPhoneNumber.ToolTip = "некорректная длина";
                MessageBox.Show("Ошибка в поле номер телефона");
                textBoxPhoneNumber.Focus();
                return;
            }*/
            else if (!IsValidPhoneNumber(userPhone))
            {
                textBoxPhoneNumber.ToolTip = "номер телефона некорректный";
                MessageBox.Show("Ошибка в поле номер телефона");
                textBoxPhoneNumber.Focus();
                return;
            }
            else if (userPassword.Length < 7)
            {
                passwordBox.ToolTip = "Пароль должен быть длиннее";
                MessageBox.Show("Пароль слишком короткий");
                passwordBox.Focus();
                return;
            }
            else if (userPassword != userPassword2)
            {
                passwordBox2.ToolTip = "пароли должны совпадать";
                MessageBox.Show("Ошибка в поле пароль");
                passwordBox2.Focus();
                return;
            }
            else if (!userEmail.Contains("@mail.ru") && !userEmail.Contains("@gmail.com"))
            {
                textBoxEmail.ToolTip = "Email должен включать @mail.ru или @gmail.com";
                MessageBox.Show("Ошибка в поле email");
                textBoxEmail.Focus();
                return;
            }

            var existingUser = loginWindow.SushiDb.Clients.FirstOrDefault(c => c.Email == userEmail);
            if (existingUser != null)
            {
                MessageBox.Show("Пользователь с таким email уже существует.");
                textBoxEmail.Focus();
                textBoxEmail.ToolTip = "Email уже занят";
                return;
            }
            else
            {
                textBoxEmail.ToolTip = "";
                textBoxName.ToolTip = "";
                textBoxLastName.ToolTip = "";
                textBoxAddress.ToolTip = "";
                textBoxPhoneNumber.ToolTip = "";
                passwordBox.ToolTip = "";
                passwordBox2.ToolTip = "";

                userPassword = HashPassword(passwordBox.Password.Trim());
                Clients client = new Clients(userEmail, userName, userLastName, userAddress, userPhone, userPassword);
                loginWindow.SushiDb.Clients.Add(client);
                loginWindow.SushiDb.SaveChanges();
                loginWindow toLoginWindow = new loginWindow();
                MessageBox.Show("регистрация завершена");
                toLoginWindow.Show();
                Hide();
            }

        }

        private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                Button_Register(sender, e);
            }
        }

        private void To_Sign_In_Window(object sender, RoutedEventArgs e)
        {
            loginWindow toLoginWindow = new loginWindow();
            toLoginWindow.Show();
            Hide();
        }
    }
}
