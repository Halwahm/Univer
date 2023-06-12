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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data.SqlClient;
using System.Data;
using System.Transactions;
using System.Data.Common;

namespace WpfApp1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            LoadGrid();


            vklad_type.Items.Add("Срочный вклад");
            vklad_type.Items.Add("Условный вклад");
            vklad_type.Items.Add("Вклад до востребования");
        }

        SqlConnection con = new SqlConnection(@"Data Source=HALWA\SQLEXPRESS;Initial Catalog=wpflabs;Integrated Security=True");

        public void clearData()
        {
            id.Clear();
            client_code.Clear();
            nomer.Clear();
            vklad_type.Items.Clear();
            amount.Clear();
            vklad_date.DisplayDate = DateTime.Today;
            search_txt.Clear();
        }

        public void LoadGrid()
        {
            SqlCommand cmd = new SqlCommand("select * from Вклады", con);
            DataTable dt = new DataTable();
            con.Open();
            SqlDataReader sdr = cmd.ExecuteReader();
            dt.Load(sdr);
            con.Close();
            datagrid.ItemsSource = dt.DefaultView;
        }

        private void ClearDataBtn_Click(object sender, RoutedEventArgs e)
        {
            clearData();
        }

        public bool isValid()
        {
            if (id.Text == string.Empty)
            {
                MessageBox.Show("ID неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (client_code.Text == string.Empty)
            {
                MessageBox.Show("Код клиента неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (nomer.Text == string.Empty)
            {
                MessageBox.Show("Номер счета неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (string.IsNullOrEmpty(vklad_type.Text))
            {
                MessageBox.Show("Вид вклада неправильный", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (amount.Text == string.Empty)
            {
                MessageBox.Show("Сумма вклада неправильная", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            if (vklad_date.SelectedDate == null)
            {
                MessageBox.Show("Дата вклада неправильная", "Failed", MessageBoxButton.OK, MessageBoxImage.Error);
                return false;
            }
            return true;
        }

        private void InsertBtn_Click(object sender, RoutedEventArgs e)
        {
            //SqlTransaction transaction = con.BeginTransaction();
            try
            {
                if (isValid())
                {
                    SqlCommand cmd = new SqlCommand("INSERT INTO Вклады(ID, Код_клиента, Номер_счёта, Вид_вклада, Сумма, Дата) VALUES (@ID, @Код_клиента, @Номер_счёта, @Вид_вклада, @Сумма, @Дата)", con);
                    cmd.CommandType = CommandType.Text;
                    cmd.Parameters.AddWithValue("@ID", id.Text);
                    cmd.Parameters.AddWithValue("@Код_клиента", client_code.Text);
                    cmd.Parameters.AddWithValue("@Номер_счёта", nomer.Text);
                    cmd.Parameters.AddWithValue("@Вид_вклада", vklad_type.Text);
                    cmd.Parameters.AddWithValue("@Сумма", amount.Text);
                    cmd.Parameters.AddWithValue("@Дата", vklad_date.SelectedDate);

                    //transaction.Commit();

                    con.Open();
                    cmd.ExecuteNonQuery();
                    con.Close();
                    LoadGrid();
                    MessageBox.Show("Успешно загружено", "Saved", MessageBoxButton.OK, MessageBoxImage.Information);
                    clearData();
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
            SqlCommand cmd = new SqlCommand("delete from Вклады where ID = " + search_txt.Text+" ", con);
            try
            {
                cmd.ExecuteNonQuery();
                MessageBox.Show("Успешно удалено", "Deleted", MessageBoxButton.OK, MessageBoxImage.Information);
                con.Close();
                clearData();
                LoadGrid();
                con.Close();
            }
            catch (SqlException ex)
            {
                MessageBox.Show("Not Deleted"+ ex.Message);
            }
            finally
            {
                con.Close();
            }
        }

        private void UpdateBtn_Click(object sender, RoutedEventArgs e)
        {
            con.Open();
            SqlCommand cmd = new SqlCommand("update Вклады set ID = '" + id.Text + "', Код_клиента = '" + client_code.Text + "', Номер_счёта = '" + nomer.Text + "', Вид_вклада = '"+ vklad_type.Text + "', Сумма = '" + amount.Text + "', Дата = '" + vklad_date.SelectedDate + "' WHERE ID = '"+search_txt.Text+"' ", con);
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
                clearData();
                LoadGrid();

            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Clients clients = new Clients();
            clients.Show();
        }
    }
}
