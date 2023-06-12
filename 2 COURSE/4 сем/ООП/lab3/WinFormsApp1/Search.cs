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
    public partial class Search : Form
    {
        public Search()
        {
            InitializeComponent();
            if (dataGridView2.Rows.Count > 0)
            {
                dataGridView2.Rows.Clear();
            }
            else
            {
                MessageBox.Show("Таблица пустая.", "Ошибка.");
            }

            if (File.Exists("Data.xml")) 
            {
                DataSet ds = new DataSet(); 
                ds.ReadXml("Data.xml");

                foreach (DataRow item in ds.Tables["BANK"].Rows)
                {
                    int n = dataGridView2.Rows.Add(); 
                    dataGridView2.Rows[n].Cells[0].Value = item["NOMER"]; 
                    dataGridView2.Rows[n].Cells[1].Value = item["BALANS"]; 
                    dataGridView2.Rows[n].Cells[2].Value = item["VKLAD"]; 
                                
                    dataGridView2.Rows[n].Cells[3].Value = item["D_OPEN"]; 
                    dataGridView2.Rows[n].Cells[4].Value = item["SMS"]; 
                    dataGridView2.Rows[n].Cells[5].Value = item["IB"]; 
                    dataGridView2.Rows[n].Cells[6].Value = item["FIO"]; 
                    dataGridView2.Rows[n].Cells[7].Value = item["D_BDAY"]; 
                    dataGridView2.Rows[n].Cells[8].Value = item["PASSPORT"]; 
                }
            }
            else
            {
                MessageBox.Show("XML файл не найден.", "Ошибка.");
            }


            for (int i = 0; i < dataGridView2.RowCount - 1; i++)
            {
                if (dataGridView2.Rows[i].Cells[0].Value.ToString() == "")
                {
                    dataGridView2.Rows.RemoveAt(i);
                    i--;
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e) 
        {

        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e) // закрытие
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dataGridView2.RowCount; i++)
            {
                dataGridView2.Rows[i].Selected = false;
                for (int j = 0; j < dataGridView2.ColumnCount; j++)
                    if (dataGridView2.Rows[i].Cells[j].Value != null)
                        if (dataGridView2.Rows[i].Cells[j].Value.ToString().Contains(textBox1.Text))
                        {
                            dataGridView2.Rows[i].Selected = true;
                            break;
                        }
            }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
        }

        private void Search_Load(object sender, EventArgs e)
        {

        }
    }
}
