using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WinFormsApp1
{
    public partial class Bank : Form
    {
        public Bank()
        {
            InitializeComponent();
            Balans_trackBar.Scroll += Balans_trackBar_Scroll;

            Random rand = new Random();
            int x = rand.Next(100000, 999999);
            Nomer_scheta_textBox.Text = x.ToString();

            Tip_vklada_comboBox.Text = "";
        }

        public static Class1 bank = new Class1();

        private void Bank_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form form = new Form2();
            form.Show();
        }

        private void Nomer_scheta_textBox_TextChanged(object sender, EventArgs e)
        {
            bank.Number = Nomer_scheta_textBox.Text;
        }

        private void Tip_vklada_comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bank.Vklad = Tip_vklada_comboBox.Items[Tip_vklada_comboBox.SelectedIndex].ToString();
        }

        private void Balans_trackBar_Scroll(object sender, EventArgs e)
        {
            label9.Text = String.Format("{0}", Balans_trackBar.Value);
        }

        private void podkluchenieSMS_checkBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox podkluchenieSMS_checkBox = (CheckBox)sender;
            if (podkluchenieSMS_checkBox.Checked == true)
            {
                podkluchenieSMS_checkBox.Text = String.Format("Да");
            }
            else
            {
                podkluchenieSMS_checkBox.Text = String.Format("Нет");
            }
        }

        private void podkluchenieIB_checkBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox podkluchenieIB_checkBox = (CheckBox)sender;
            if (podkluchenieIB_checkBox.Checked == true)
            {
                podkluchenieIB_checkBox.Text = String.Format("Да");
            }
            else
            {
                podkluchenieIB_checkBox.Text = String.Format("Нет");
            }
        }
        private void Gotovo1_button_Click(object sender, EventArgs e)
        {
            try
            {
                int n = dataGridView1.Rows.Add();
                dataGridView1.Rows[n].Cells[0].Value = bank.Number; 
                dataGridView1.Rows[n].Cells[1].Value = bank.Vklad; 
                dataGridView1.Rows[n].Cells[2].Value = label9.Text;
                dataGridView1.Rows[n].Cells[3].Value = Data_otkritiya_dateTimePicker.Value;
                dataGridView1.Rows[n].Cells[4].Value = podkluchenieSMS_checkBox.Checked; 
                dataGridView1.Rows[n].Cells[5].Value = podkluchenieIB_checkBox.Checked;
                dataGridView1.Rows[n].Cells[6].Value = bank.vladelets.Name; 
                dataGridView1.Rows[n].Cells[7].Value = bank.vladelets.d; 
                dataGridView1.Rows[n].Cells[8].Value = bank.vladelets.Seria + bank.vladelets.Nomer; 

                Nomer_scheta_textBox.Clear();
                Random rand = new Random();
                int x = rand.Next(10000, 99999);
                Nomer_scheta_textBox.Text = x.ToString();

                DataSet ds = new DataSet(); 
                DataTable dt = new DataTable(); 
                dt.TableName = "BANK"; 
                dt.Columns.Add("NOMER"); 
                dt.Columns.Add("BALANS");
                dt.Columns.Add("VKLAD");

                dt.Columns.Add("D_OPEN");
                dt.Columns.Add("SMS");
                dt.Columns.Add("IB");
                dt.Columns.Add("FIO");
                dt.Columns.Add("D_BDAY");
                dt.Columns.Add("PASSPORT");
                ds.Tables.Add(dt); 

                foreach (DataGridViewRow r in dataGridView1.Rows) 
                {
                    DataRow row = ds.Tables["BANK"].NewRow();
                    row["NOMER"] = r.Cells[0].Value; 
                    row["BALANS"] = r.Cells[1].Value; 
                    row["VKLAD"] = r.Cells[2].Value; 

                    row["D_OPEN"] = r.Cells[3].Value;
                    row["SMS"] = r.Cells[4].Value;
                    row["IB"] = r.Cells[5].Value;
                    row["FIO"] = r.Cells[6].Value;
                    row["D_BDAY"] = r.Cells[7].Value;
                    row["PASSPORT"] = r.Cells[8].Value;

                    ds.Tables["BANK"].Rows.Add(row); 
                }
                ds.WriteXml("Data.xml");
            }
            catch(NullReferenceException)
            {

                MessageBox.Show("Заполните все поля.", "Ошибка.");
            }
            catch
            {
                MessageBox.Show("Невозможно сохранить XML файл.", "Ошибка.");
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e) //о программе
        {
            MessageBox.Show("Версия: 1.3\nРазработчик: маш ок", "О программе");
        }

        private void button2_Click(object sender, EventArgs e) //кнопка СОХРАНИТЬ в XML
        {
            try
            {
                DataSet ds = new DataSet(); 
                DataTable dt = new DataTable(); 
                dt.TableName = "BANK"; 
                dt.Columns.Add("NOMER"); 
                dt.Columns.Add("BALANS");
                dt.Columns.Add("VKLAD");

                dt.Columns.Add("D_OPEN");
                dt.Columns.Add("SMS");
                dt.Columns.Add("IB");
                dt.Columns.Add("FIO");
                dt.Columns.Add("D_BDAY");
                dt.Columns.Add("PASSPORT");
                ds.Tables.Add(dt); 

                foreach (DataGridViewRow r in dataGridView1.Rows) 
                {
                    DataRow row = ds.Tables["BANK"].NewRow(); 
                    row["NOMER"] = r.Cells[0].Value;  
                    row["BALANS"] = r.Cells[1].Value; 
                    row["VKLAD"] = r.Cells[2].Value; 

                    row["D_OPEN"] = r.Cells[3].Value;
                    row["SMS"] = r.Cells[4].Value;
                    row["IB"] = r.Cells[5].Value;
                    row["FIO"] = r.Cells[6].Value;
                    row["D_BDAY"] = r.Cells[7].Value;
                    row["PASSPORT"] = r.Cells[8].Value;

                    ds.Tables["BANK"].Rows.Add(row); 
                }
                ds.WriteXml("saved.xml");

                MessageBox.Show("XML файл успешно сохранен.", "Выполнено.");
            }
            catch
            {
                MessageBox.Show("Невозможно сохранить XML файл.", "Ошибка.");
            }
        }

        private void button3_Click(object sender, EventArgs e) // очистить таблицу
        {
            if (dataGridView1.Rows.Count > 0)
            {
                dataGridView1.Rows.Clear();
            }
            else
            {
                MessageBox.Show("Таблица пустая.", "Ошибка.");
            }
        }


        private void button1_Click_1(object sender, EventArgs e) // ПОИСК
        {
            Form f = new Search();
            f.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.dataGridView1.Sort(this.dataGridView1.Columns["Column4"], ListSortDirection.Ascending);
        }
    }
}
