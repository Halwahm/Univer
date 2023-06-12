using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Reflection.Emit;
using System.Text;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Data_rozhdeniya_monthCalendar.DateChanged += Data_rozhdeniya_monthCalendar_DateChanged;
            Familia_textBox.Text = "";
            Imya_textBox.Text = "";
            Otchestvo_textBox.Text = "";
            Gorod_comboBox.Text = "";
            seria_pasport_comboBox.Text = "";
            nomer_pasport_textBox.Text = "";
        }

        Vladelets vladelets = new Vladelets();

        private void Gotovo2_button_Click(object sender, EventArgs e)
        {
            this.Close();
            Bank.bank.vladelets = vladelets;
        }

        private void Familia_textBox_TextChanged(object sender, EventArgs e)
        {
            vladelets.Name = "ФИО: " + Familia_textBox.Text + " " + Imya_textBox.Text + " " + Otchestvo_textBox.Text + "\n";
        }

        private void Imya_textBox_TextChanged(object sender, EventArgs e)
        {
            vladelets.Name = "ФИО: " + Familia_textBox.Text + " " + Imya_textBox.Text + " " + Otchestvo_textBox.Text + "\n";
        }

        private void Otchestvo_textBox_TextChanged(object sender, EventArgs e)
        {
            vladelets.Name = Familia_textBox.Text + " " + Imya_textBox.Text + " " + Otchestvo_textBox.Text + "\n";
        }

        private void Gorod_comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            vladelets.Gorod = Gorod_comboBox.Items[Gorod_comboBox.SelectedIndex].ToString();
        }

        private void seria_pasport_comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            vladelets.Seria = seria_pasport_comboBox.Items[seria_pasport_comboBox.SelectedIndex].ToString();
        }

        private void nomer_pasport_textBox_TextChanged(object sender, EventArgs e)
        {
            vladelets.Nomer = nomer_pasport_textBox.Text + "\n";
        }

        private void Data_rozhdeniya_monthCalendar_DateChanged(object sender, DateRangeEventArgs e)
        {
            label9.Text = String.Format(e.Start.ToLongDateString());
            vladelets.d = label9.Text + "\n";
        }

        private void label9_Click(object sender, EventArgs e) { }
    }
}
