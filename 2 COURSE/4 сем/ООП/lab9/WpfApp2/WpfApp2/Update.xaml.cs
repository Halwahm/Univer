using Microsoft.Win32;
using Newtonsoft.Json.Linq;
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

namespace WpfApp2
{
    /// <summary>
    /// Логика взаимодействия для Update.xaml
    /// </summary>
    public partial class Update : Window
    {
        private OpenFileDialog openFileDialog;
        private Uri fileUri;
        byte[] array;
        int[] idArray;
        public Update(object item)
        {
            InitializeComponent();
            firstNameTextBox.Text = item.GetType().GetProperty("first_name").GetValue(item).ToString();
            middleNameTextBox.Text = item.GetType().GetProperty("middle_name").GetValue(item).ToString();
            lastNameTextBox.Text = item.GetType().GetProperty("last_name").GetValue(item).ToString();
            ageTextBox.Text = item.GetType().GetProperty("age").GetValue(item).ToString();
            phoneTextBox.Text = item.GetType().GetProperty("phone").GetValue(item).ToString();
            countryTextBox.Text = item.GetType().GetProperty("country").GetValue(item).ToString();
            cityTextBox.Text = item.GetType().GetProperty("city").GetValue(item).ToString();
            streetTextBox.Text = item.GetType().GetProperty("street").GetValue(item).ToString();
            houseTextBox.Text = item.GetType().GetProperty("house").GetValue(item).ToString();
            buildTextBox.Text = item.GetType().GetProperty("build").GetValue(item).ToString();
            flatTextBox.Text = item.GetType().GetProperty("flat").GetValue(item).ToString();
            serialTextBox.Text = item.GetType().GetProperty("serial").GetValue(item).ToString();
            numberTextBox.Text = item.GetType().GetProperty("number").GetValue(item).ToString();
            array = (byte[])item.GetType().GetProperty("photo").GetValue(item);
            idArray = new int[3] {(int)item.GetType().GetProperty("id_person").GetValue(item),
                (int)item.GetType().GetProperty("id_address").GetValue(item),
                (int)item.GetType().GetProperty("id_passport").GetValue(item)};
        }

        private byte[] B64Encode()
        {
            byte[] array = Encoding.ASCII.GetBytes(fileUri.ToString());
            return array;
        }

        private void imgButton_Click(object sender, RoutedEventArgs e)
        {
            openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image|*.jpg;*.jpeg;*.png;";
            if (openFileDialog.ShowDialog() == true)
            {
                fileUri = new Uri(openFileDialog.FileName);
            }
        }

        private void updateButton_Click(object sender, RoutedEventArgs e)
        {
            using (ApplicationContext db = new ApplicationContext())
            {
                using (var transaction = db.Database.BeginTransaction())
                {
                    try
                    {
                        var person = db.PERSON.Where(p => p.id_person == idArray[0]).FirstOrDefault();
                        var address = db.ADDRESS.Where(a => a.id_address == idArray[1]).FirstOrDefault();
                        var passport = db.PASSPORT.Where(p => p.id_passport == idArray[2]).FirstOrDefault();

                        person.first_name = firstNameTextBox.Text;
                        person.last_name = lastNameTextBox.Text;
                        person.middle_name = middleNameTextBox.Text;
                        person.age = int.Parse(ageTextBox.Text);
                        person.phone = phoneTextBox.Text;

                        address.country = countryTextBox.Text;
                        address.city = cityTextBox.Text;
                        address.street = streetTextBox.Text;
                        address.house = int.Parse(houseTextBox.Text);
                        address.build = int.Parse(buildTextBox.Text);
                        address.flat = int.Parse(flatTextBox.Text);

                        passport.serial = serialTextBox.Text;
                        passport.number = int.Parse(numberTextBox.Text);
                        passport.photo = fileUri == null ? array : B64Encode();
                        db.SaveChanges();
                        transaction.Commit();
                    }
                    catch (Exception ex)
                    {
                        transaction.Rollback();
                    }
                }
            }
        }
    }
}
