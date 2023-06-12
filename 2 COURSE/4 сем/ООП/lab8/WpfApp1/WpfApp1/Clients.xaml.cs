using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
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

namespace WpfApp1
{
    /// <summary>
    /// Логика взаимодействия для Clients.xaml
    /// </summary>
    public partial class Clients : Window
    {
        public Clients()
        {
            InitializeComponent();
            LoadGrid2();
        }

        SqlConnection con = new SqlConnection(@"Data Source=HALWA\SQLEXPRESS;Initial Catalog=wpflabs;Integrated Security=True");

        public void LoadGrid2()
        {
            SqlCommand cmd = new SqlCommand("select * from Клиенты", con);
            DataTable dt = new DataTable();
            con.Open();
            SqlDataReader sdr = cmd.ExecuteReader();
            dt.Load(sdr);
            con.Close();
            datagrid.ItemsSource = dt.DefaultView;
        }
        public void clearData2()
        {
            id.Clear();
            name.Clear();
            grazhdanstvo.Clear();
            adress.Clear();
            photo.Clear();
            search_txt.Clear();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        public bool isValid()
        {
            if (id.Text == string.Empty)
            {
                MessageBox.Show("ID неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (name.Text == string.Empty)
            {
                MessageBox.Show("Код клиента неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (grazhdanstvo.Text == string.Empty)
            {
                MessageBox.Show("Номер счета неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (adress.Text == string.Empty)
            {
                MessageBox.Show("Сумма вклада неправильная", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (photo.Text == string.Empty)
            {
                MessageBox.Show("Сумма вклада неправильная", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            return true;
        }

        private void InsertBtn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (isValid())
                {
                    SqlCommand cmd = new SqlCommand("INSERT INTO Клиенты(ID, ФИО, Гражданство, Адрес, Фото) VALUES (@ID, @ФИО, @Гражданство, @Адрес, @Фото)", con);
                    cmd.CommandType = CommandType.Text;
                    cmd.Parameters.AddWithValue("@ID", id.Text);
                    cmd.Parameters.AddWithValue("@ФИО", name.Text);
                    cmd.Parameters.AddWithValue("@Гражданство", grazhdanstvo.Text);
                    cmd.Parameters.AddWithValue("@Адрес", adress.Text);
                    cmd.Parameters.AddWithValue("@Фото", photo.Text);

                    con.Open();
                    cmd.ExecuteNonQuery();
                    con.Close();
                    LoadGrid2();
                    MessageBox.Show("Успешно загружено", "Saved", MessageBoxButton.OK, MessageBoxImage.Information);
                    clearData2();
                }
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void DeleteBtn_Click(object sender, RoutedEventArgs e)
        {
            con.Open();
            SqlCommand cmd = new SqlCommand("delete from Клиенты where ID = " + search_txt.Text + " ", con);
            try
            {
                cmd.ExecuteNonQuery();
                MessageBox.Show("Успешно удалено", "Deleted", MessageBoxButton.OK, MessageBoxImage.Information);
                con.Close();
                clearData2();
                LoadGrid2();
                con.Close();
            }
            catch (SqlException ex)
            {
                MessageBox.Show("Not Deleted" + ex.Message);
            }
            finally
            {
                con.Close();
            }
        }

        private void UpdateBtn_Click(object sender, RoutedEventArgs e)
        {
            con.Open();
            SqlCommand cmd = new SqlCommand("update Клиенты set ID = '" + id.Text + "', ФИО = '" + name.Text + "', Гражданство = '" + grazhdanstvo.Text + "', Адрес = '" + adress.Text + "', Фото = '" + photo.Text + "' WHERE ID = '" + search_txt.Text + "' ", con);
            try
            {
                cmd.ExecuteNonQuery();
                MessageBox.Show("Успешно обновлено", "Updated", MessageBoxButton.OK, MessageBoxImage.Information);

            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                con.Close();
                clearData2();
                LoadGrid2();
            }
        }

        private void ClearDataBtn_Click(object sender, RoutedEventArgs e)
        {
            clearData2();
        }
    }
}
