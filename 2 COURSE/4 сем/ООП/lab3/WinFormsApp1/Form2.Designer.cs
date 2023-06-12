
namespace WinFormsApp1
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Familia_textBox = new System.Windows.Forms.TextBox();
            this.Imya_textBox = new System.Windows.Forms.TextBox();
            this.Otchestvo_textBox = new System.Windows.Forms.TextBox();
            this.Data_rozhdeniya_monthCalendar = new System.Windows.Forms.MonthCalendar();
            this.Gorod_comboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.seria_pasport_comboBox = new System.Windows.Forms.ComboBox();
            this.nomer_pasport_textBox = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.Gotovo2_button = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Familia_textBox
            // 
            this.Familia_textBox.Location = new System.Drawing.Point(90, 32);
            this.Familia_textBox.Name = "Familia_textBox";
            this.Familia_textBox.Size = new System.Drawing.Size(291, 27);
            this.Familia_textBox.TabIndex = 0;
            this.Familia_textBox.TextChanged += new System.EventHandler(this.Familia_textBox_TextChanged);
            // 
            // Imya_textBox
            // 
            this.Imya_textBox.Location = new System.Drawing.Point(90, 65);
            this.Imya_textBox.Name = "Imya_textBox";
            this.Imya_textBox.Size = new System.Drawing.Size(291, 27);
            this.Imya_textBox.TabIndex = 1;
            this.Imya_textBox.TextChanged += new System.EventHandler(this.Imya_textBox_TextChanged);
            // 
            // Otchestvo_textBox
            // 
            this.Otchestvo_textBox.Location = new System.Drawing.Point(90, 98);
            this.Otchestvo_textBox.Name = "Otchestvo_textBox";
            this.Otchestvo_textBox.Size = new System.Drawing.Size(291, 27);
            this.Otchestvo_textBox.TabIndex = 2;
            this.Otchestvo_textBox.TextChanged += new System.EventHandler(this.Otchestvo_textBox_TextChanged);
            // 
            // Data_rozhdeniya_monthCalendar
            // 
            this.Data_rozhdeniya_monthCalendar.Location = new System.Drawing.Point(410, 38);
            this.Data_rozhdeniya_monthCalendar.Name = "Data_rozhdeniya_monthCalendar";
            this.Data_rozhdeniya_monthCalendar.TabIndex = 3;
            this.Data_rozhdeniya_monthCalendar.TitleBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.Data_rozhdeniya_monthCalendar.TrailingForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.Data_rozhdeniya_monthCalendar.DateChanged += new System.Windows.Forms.DateRangeEventHandler(this.Data_rozhdeniya_monthCalendar_DateChanged);
            // 
            // Gorod_comboBox
            // 
            this.Gorod_comboBox.FormattingEnabled = true;
            this.Gorod_comboBox.Items.AddRange(new object[] {
            "Брестская область",
            "Витебская область",
            "Гомельская область",
            "Гродненьская область",
            "Минская область",
            "Могилевская область",
            "г. Минск"});
            this.Gorod_comboBox.Location = new System.Drawing.Point(177, 160);
            this.Gorod_comboBox.Name = "Gorod_comboBox";
            this.Gorod_comboBox.Size = new System.Drawing.Size(204, 28);
            this.Gorod_comboBox.TabIndex = 4;
            this.Gorod_comboBox.SelectedIndexChanged += new System.EventHandler(this.Gorod_comboBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 163);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(159, 20);
            this.label1.TabIndex = 5;
            this.label1.Text = "Область проживания";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Имя";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "Фамилия";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 98);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 20);
            this.label4.TabIndex = 8;
            this.label4.Text = "Отчество";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(449, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(116, 20);
            this.label5.TabIndex = 9;
            this.label5.Text = "Дата рождения";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(34, 216);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(121, 20);
            this.label6.TabIndex = 10;
            this.label6.Text = "Серия паспорта";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(209, 215);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(126, 20);
            this.label7.TabIndex = 11;
            this.label7.Text = "Номер паспорта";
            // 
            // seria_pasport_comboBox
            // 
            this.seria_pasport_comboBox.FormattingEnabled = true;
            this.seria_pasport_comboBox.Items.AddRange(new object[] {
            "AB",
            "BM",
            "HB",
            "KH",
            "MP",
            "MC",
            "KB",
            "PP"});
            this.seria_pasport_comboBox.Location = new System.Drawing.Point(70, 240);
            this.seria_pasport_comboBox.Name = "seria_pasport_comboBox";
            this.seria_pasport_comboBox.Size = new System.Drawing.Size(50, 28);
            this.seria_pasport_comboBox.TabIndex = 12;
            this.seria_pasport_comboBox.SelectedIndexChanged += new System.EventHandler(this.seria_pasport_comboBox_SelectedIndexChanged);
            // 
            // nomer_pasport_textBox
            // 
            this.nomer_pasport_textBox.Location = new System.Drawing.Point(199, 240);
            this.nomer_pasport_textBox.MaxLength = 7;
            this.nomer_pasport_textBox.Name = "nomer_pasport_textBox";
            this.nomer_pasport_textBox.Size = new System.Drawing.Size(147, 27);
            this.nomer_pasport_textBox.TabIndex = 13;
            this.nomer_pasport_textBox.TextChanged += new System.EventHandler(this.nomer_pasport_textBox_TextChanged);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.Gotovo2_button);
            this.panel1.Controls.Add(this.Imya_textBox);
            this.panel1.Controls.Add(this.nomer_pasport_textBox);
            this.panel1.Controls.Add(this.Familia_textBox);
            this.panel1.Controls.Add(this.seria_pasport_comboBox);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.Gorod_comboBox);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.Data_rozhdeniya_monthCalendar);
            this.panel1.Controls.Add(this.Otchestvo_textBox);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(620, 367);
            this.panel1.TabIndex = 14;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(449, 248);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(92, 20);
            this.label9.TabIndex = 16;
            this.label9.Text = "не выбрана";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(410, 248);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(48, 20);
            this.label8.TabIndex = 15;
            this.label8.Text = "Дата: ";
            // 
            // Gotovo2_button
            // 
            this.Gotovo2_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.Gotovo2_button.Location = new System.Drawing.Point(11, 305);
            this.Gotovo2_button.Name = "Gotovo2_button";
            this.Gotovo2_button.Size = new System.Drawing.Size(590, 50);
            this.Gotovo2_button.TabIndex = 14;
            this.Gotovo2_button.Text = "Готово";
            this.Gotovo2_button.UseVisualStyleBackColor = false;
            this.Gotovo2_button.Click += new System.EventHandler(this.Gotovo2_button_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(620, 367);
            this.Controls.Add(this.panel1);
            this.MaximizeBox = false;
            this.Name = "Form2";
            this.Text = "Form2";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox Familia_textBox;
        private System.Windows.Forms.TextBox Imya_textBox;
        private System.Windows.Forms.TextBox Otchestvo_textBox;
        private System.Windows.Forms.MonthCalendar Data_rozhdeniya_monthCalendar;
        private System.Windows.Forms.ComboBox Gorod_comboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox seria_pasport_comboBox;
        private System.Windows.Forms.TextBox nomer_pasport_textBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button Gotovo2_button;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
    }
}