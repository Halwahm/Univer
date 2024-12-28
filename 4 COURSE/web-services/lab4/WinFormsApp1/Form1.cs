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
                // ������� ������ ��� ������ ���-�������
                var client = new Simplex.SimplexSoapClient();

                // ������ �������� �� ��������� �����
                int a = int.Parse(txtNumber1.Text);
                int b = int.Parse(txtNumber2.Text);

                // �������� ����� Sum
                int result = client.Sum(a, b);

                // ���������� ���������
                lblResult.Text = "Result: " + result;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }
    }
}
