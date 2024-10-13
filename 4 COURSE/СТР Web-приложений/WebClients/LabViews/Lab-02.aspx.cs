using System;
using System.IO;
using System.Net;
using System.Text;
using System.Web.UI;
using Newtonsoft.Json;

namespace WebClients.LabViews
{
    public partial class Lab_02 : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                // Дополнительная логика при первом загрузке страницы
            }
        }

        // Обработчик для кнопки POST
        protected void POSTBtn_Click(object sender, EventArgs e)
        {
            try
            {
                int resultValue = int.Parse(Result.Text);
                var response = SendRequest("POST", $"http://localhost:88/api/Values?result={resultValue}", null);

                var jsonResponse = JsonConvert.DeserializeObject<dynamic>(response);
                customerr1.Visible = jsonResponse.Message == null;
                customerr1.Text = jsonResponse.Message;
            }
            catch (Exception ex)
            {
                customerr1.Visible = true;
                customerr1.Text = "Ошибка: " + ex.Message;
            }
        }

        // Обработчик для кнопки GET
        protected void GETBtn_Click(object sender, EventArgs e)
        {
            try
            {
                var response = SendRequest("GET", "http://localhost:88/api/Values", null);

                var jsonResponse = JsonConvert.DeserializeObject<dynamic>(response);
                GetResult.Text = jsonResponse.Result.ToString();
            }
            catch (Exception ex)
            {
                customerr1.Visible = true;
                customerr1.Text = "Ошибка: " + ex.Message;
            }
        }

        // Обработчик для кнопки PUT
        protected void PUTBtn_Click(object sender, EventArgs e)
        {
            try
            {
                int addValue = int.Parse(Add.Text);
                var response = SendRequest("PUT", $"http://localhost:88/api/Values?add={addValue}", null);

                var jsonResponse = JsonConvert.DeserializeObject<dynamic>(response);
                customerr2.Visible = jsonResponse.Message == null;
                customerr2.Text = jsonResponse.Message;
            }
            catch (Exception ex)
            {
                customerr2.Visible = true;
                customerr2.Text = "Ошибка: " + ex.Message;
            }
        }

        // Обработчик для кнопки DELETE
        protected void DELETEBtn_Click(object sender, EventArgs e)
        {
            try
            {
                var response = SendRequest("DELETE", "http://localhost:88/api/Values", null);

                var jsonResponse = JsonConvert.DeserializeObject<dynamic>(response);
                customerr2.Visible = jsonResponse.Message == null;
                customerr2.Text = jsonResponse.Message;
            }
            catch (Exception ex)
            {
                customerr2.Visible = true;
                customerr2.Text = "Ошибка: " + ex.Message;
            }
        }

        // Метод для отправки запросов
        private string SendRequest(string method, string url, string data)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Method = method;
            request.ContentType = "application/json";

            // Если запрос POST или PUT, нужно установить Content-Length
            if (method != "GET" && !string.IsNullOrEmpty(data))
            {
                byte[] postData = Encoding.UTF8.GetBytes(data);
                request.ContentLength = postData.Length;

                using (Stream stream = request.GetRequestStream())
                {
                    stream.Write(postData, 0, postData.Length);
                }
            }
            else
            {
                request.ContentLength = 0; // Если нет данных, Content-Length должен быть 0
            }

            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
            using (StreamReader reader = new StreamReader(response.GetResponseStream()))
            {
                return reader.ReadToEnd();
            }
        }
    }
}
