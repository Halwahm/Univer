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

            var simpleService = new Simplex();
            result.Text = "Результат: " + simpleService.Add(x, y);
        }
    }
}