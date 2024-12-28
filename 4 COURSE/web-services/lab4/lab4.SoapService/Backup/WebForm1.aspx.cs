using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebFormsProxy
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        private Simplex2 _client;

        protected void Page_Load(object sender, EventArgs e)
        {
            _client = new Simplex2();
        }

        protected void SumClick(object sender, EventArgs e)
        {
            int first;
            int second;
            if (int.TryParse(x.Text.ToString(), out first) &&
               int.TryParse(y.Text.ToString(), out second))
            {
                result.Text = _client.Add(first, second).ToString();
            }
        }
    }
}