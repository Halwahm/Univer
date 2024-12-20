using lab4.WebForm.ServiceReference1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace lab4.WebForm
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            
        }

        protected void calcBtn_Click(object sender, EventArgs e)
        {
            var isSuccessed = int.TryParse(xValue.Text, out var x);
            if (!isSuccessed)
            {
                result.Text = "X должен быть числом";
                return;
            }

            isSuccessed = int.TryParse(yValue.Text, out var y);
            if (!isSuccessed)
            {
                result.Text = "Y должен быть числом";
                return;
            }

            //var simpleService = new Simplex();
            //result.Text = "Результат: " + simpleService.Add(x, y);

            // Создайте объект клиента
            SimplexSoapClient client = new SimplexSoapClient();
            result.Text = "Результат: " + client.Add(x, y);

            // Вызовите методы сервиса
            //int result = client.AddS(5, 10); // Вызов метода AddS
            //Response.Write($"Результат сложения: {result}");

            //// Пример использования другого метода
            //string concatenated = client.Concat("Hello", 42.5);
            //Response.Write($"Конкатенация строки: {concatenated}");
        }
    }
}