using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba1
{
    public partial class BinCalc : Form
    {
        public string lowList = "abcdefghijklmnoprstuvwxyz23456789";

        public BinCalc()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            comboBox1.Text = "";
            comboBox2.Text = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Calculator result = new Calculator();
                if (textBox1.Text.IndexOfAny(lowList.ToCharArray()) != -1 || textBox2.Text.IndexOfAny(lowList.ToCharArray()) != -1)
                {
                    throw new Exception("Вводить можно только двоичные числа!");
                }

                int res;
                switch (comboBox1.Text)
                {
                    case "И (AND)":
                        res = result.And(Convert.ToInt32(textBox1.Text, 2), Convert.ToInt32(textBox2.Text, 2));
                        switch (comboBox2.Text)
                        {
                            case "двоичной":
                                textBox3.Text = Convert.ToString(res, 2);
                                break;

                            case "восьмеричной":
                                textBox3.Text = Convert.ToString(res, 8);
                                break;

                            case "десятичной":
                                textBox3.Text = Convert.ToString(res, 10);
                                break;

                            case "шестнадцатеричной":
                                textBox3.Text = Convert.ToString(res, 16);
                                break;
                        }
                        break;

                    case "ИЛИ (OR)":
                        res = result.Or(Convert.ToInt32(textBox1.Text, 2), Convert.ToInt32(textBox2.Text, 2));
                        switch (comboBox2.Text)
                        {
                            case "двоичной":
                                textBox3.Text = Convert.ToString(res, 2);
                                break;

                            case "восьмеричной":
                                textBox3.Text = Convert.ToString(res, 8);
                                break;

                            case "десятичной":
                                textBox3.Text = Convert.ToString(res, 10);
                                break;

                            case "шестнадцатеричной":
                                textBox3.Text = Convert.ToString(res, 16);
                                break;
                        }
                        break;

                    case "Искл. ИЛИ (XOR)":
                        res = result.Xor(Convert.ToInt32(textBox1.Text, 2), Convert.ToInt32(textBox2.Text, 2));
                        switch (comboBox2.Text)
                        {
                            case "двоичной":
                                textBox3.Text = Convert.ToString(res, 2);
                                break;

                            case "восьмеричной":
                                textBox3.Text = Convert.ToString(res, 8);
                                break;

                            case "десятичной":
                                textBox3.Text = Convert.ToString(res, 10);
                                break;

                            case "шестнадцатеричной":
                                textBox3.Text = Convert.ToString(res, 16);
                                break;
                        }
                        break;

                    case "НЕ (NOT)":
                        res = result.Not(Convert.ToInt32(textBox1.Text, 2));
                        switch (comboBox2.Text)
                        {
                            case "двоичной":
                                textBox3.Text = Convert.ToString(res, 2);
                                break;

                            case "восьмеричной":
                                textBox3.Text = Convert.ToString(res, 8);
                                break;

                            case "десятичной":
                                textBox3.Text = Convert.ToString(res, 10);
                                break;

                            case "шестнадцатеричной":
                                textBox3.Text = Convert.ToString(res, 16);
                                break;
                        }
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}