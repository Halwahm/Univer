using System;
using System.IO;
using System.Net;
using System.Text;
using System.Windows.Forms;
using Newtonsoft.Json;


namespace lab4.WinForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void runBtn_Click(object sender, EventArgs e)
        {
            try
            {
                // Получение данных от пользователя
                var a1 = new A
                {
                    s = s1Value.Text,
                    k = int.Parse(k1Value.Text),
                    f = float.Parse(f1Value.Text)
                };

                var a2 = new A
                {
                    s = s2Value.Text,
                    k = int.Parse(k2Value.Text),
                    f = float.Parse(f2Value.Text)
                };

                // Создание объекта сервиса
                var simpleService = new Simplex();

                // Вызов метода сервиса
                var result = simpleService.Sum(a1, a2);

                // Показ результата
                MessageBox.Show($"Result: s = {result.s}, k = {result.k}, f = {result.f}");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка: " + ex.Message);
            }
        }

        //public class A
        //{
        //    public string s { get; set; }
        //    public int k { get; set; }
        //    public float f { get; set; }
        //}
    }
}
