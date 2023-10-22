using System;
using System.Net.Http;
using System.Text;
using System.Windows.Forms;

namespace Calculator
{
    public partial class Form1 : Form
    {
        private readonly HttpClient _httpClient;

        public Form1()
        {
            InitializeComponent();
            _httpClient = new HttpClient();
            _httpClient.BaseAddress = new Uri("http://localhost:5050"); 
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private async void calculateButton_Click(object sender, EventArgs e)
        {
            double x, y;

            if (double.TryParse(textBoxX.Text, out x) && double.TryParse(textBoxY.Text, out y))
            {
                var request = new { X = x, Y = y };
                var jsonRequest = Newtonsoft.Json.JsonConvert.SerializeObject(request);
                var content = new StringContent(jsonRequest, Encoding.UTF8, "application/json");

                var response = await _httpClient.PostAsync("api/calculator/add", content);

                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                    resultTextBox.Text = result;
                }
                else
                {
                    resultTextBox.Text = "Ошибка при выполнении запроса.";
                }
            }
            else
            {
                resultTextBox.Text = "Неверный формат чисел X и/или Y.";
            }
        }
    }
}
