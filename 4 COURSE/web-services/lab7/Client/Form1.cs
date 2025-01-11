using System;
using System.Net.Http;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;
using Newtonsoft.Json;

namespace Client
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    string url = $"http://localhost:40125/SyndicationServiceLibrary/Feed1/students/{textBox1.Text}/notes/atom?format=rss";
                    HttpResponseMessage response = await client.GetAsync(url);
                    response.EnsureSuccessStatusCode();
                    string content = await response.Content.ReadAsStringAsync();
                    string formattedContent = FormatXml(content);
                    richTextBox1.Text = formattedContent;
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка: {ex.Message}");
                }
            }
        }

        private async void button2_Click(object sender, EventArgs e)
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    string url = $"http://localhost:40125/SyndicationServiceLibrary/Feed1/students/{textBox1.Text}/notes/json?format=atom";
                    HttpResponseMessage response = await client.GetAsync(url);
                    response.EnsureSuccessStatusCode();
                    string content = await response.Content.ReadAsStringAsync();
                    string formattedContent = FormatXml(content);
                    richTextBox1.Text = formattedContent;
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка: {ex.Message}");
                }
            }
        }

        private string FormatXml(string xmlContent)
        {
            try
            {
                XDocument doc = XDocument.Parse(xmlContent);
                using (var stringWriter = new System.IO.StringWriter())
                using (var xmlTextWriter = new XmlTextWriter(stringWriter))
                {
                    xmlTextWriter.Formatting = System.Xml.Formatting.Indented;
                    doc.Save(xmlTextWriter);
                    return stringWriter.ToString();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при форматировании XML: {ex.Message}");
                return xmlContent;
            }
        }

        private async void button3_Click(object sender, EventArgs e)
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    string url = $"http://localhost:40125/SyndicationServiceLibrary/Feed1/students/{textBox1.Text}/notes/json?format=atom";
                    HttpResponseMessage response = await client.GetAsync(url);
                    response.EnsureSuccessStatusCode();
                    string content = await response.Content.ReadAsStringAsync();
                    string jsonContent = ConvertAtomToJson(content);
                    richTextBox1.Text = FormatJson(jsonContent);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка: {ex.Message}");
                }
            }
        }

        private string ConvertAtomToJson(string atomContent)
        {
            try
            {
                XDocument doc = XDocument.Parse(atomContent);
                var items = doc.Descendants("{http://www.w3.org/2005/Atom}entry")
                               .Select(entry => new
                               {
                                   Title = entry.Element("{http://www.w3.org/2005/Atom}title")?.Value,
                                   Content = entry.Element("{http://www.w3.org/2005/Atom}content")?.Value
                               }).ToList();

                return JsonConvert.SerializeObject(items, Newtonsoft.Json.Formatting.Indented);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при конвертации Atom в JSON: {ex.Message}");
                return atomContent;
            }
        }

        private string FormatJson(string jsonContent)
        {
            try
            {
                var parsedJson = Newtonsoft.Json.Linq.JToken.Parse(jsonContent);
                return parsedJson.ToString(Newtonsoft.Json.Formatting.Indented);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при форматировании JSON: {ex.Message}");
                return jsonContent;
            }
        }


    }
}
