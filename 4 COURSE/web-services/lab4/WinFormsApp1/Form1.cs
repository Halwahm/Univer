using ServiceReference1;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        private readonly SimplexSoapClient _client;
        public Form1()
        {
            _client = new SimplexSoapClient();
            InitializeComponent();
        }

        private void btnCallSum_Click(object sender, EventArgs e)
        {
            try
            {
                // Создаем клиент для вызова веб-сервиса
                var client = new Simplex.SimplexSoapClient();

                // Читаем значения из текстовых полей
                int a = int.Parse(txtNumber1.Text);
                int b = int.Parse(txtNumber2.Text);

                // Вызываем метод Sum
                int result = client.Sum(a, b);

                // Отображаем результат
                lblResult.Text = "Result: " + result;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }
    }
}
