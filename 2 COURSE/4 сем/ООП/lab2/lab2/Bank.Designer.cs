
namespace WinFormsApp1
{
    partial class Bank
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.richTextBox = new System.Windows.Forms.RichTextBox();
            this.Gotovo1_button = new System.Windows.Forms.Button();
            this.podkluchenieIB_checkBox = new System.Windows.Forms.CheckBox();
            this.Balans_trackBar = new System.Windows.Forms.TrackBar();
            this.Tip_vklada_comboBox = new System.Windows.Forms.ComboBox();
            this.Data_otkritiya_dateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.podkluchenieSMS_checkBox = new System.Windows.Forms.CheckBox();
            this.Vladelets_button = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.Nomer_scheta_textBox = new System.Windows.Forms.TextBox();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Balans_trackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Controls.Add(this.label10);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.richTextBox);
            this.panel1.Controls.Add(this.Gotovo1_button);
            this.panel1.Controls.Add(this.podkluchenieIB_checkBox);
            this.panel1.Controls.Add(this.Balans_trackBar);
            this.panel1.Controls.Add(this.Tip_vklada_comboBox);
            this.panel1.Controls.Add(this.Data_otkritiya_dateTimePicker);
            this.panel1.Controls.Add(this.podkluchenieSMS_checkBox);
            this.panel1.Controls.Add(this.Vladelets_button);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.Nomer_scheta_textBox);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(790, 584);
            this.panel1.TabIndex = 0;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(119, 179);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(17, 20);
            this.label10.TabIndex = 19;
            this.label10.Text = "$";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(82, 179);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 20);
            this.label9.TabIndex = 18;
            this.label9.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Times New Roman", 22.2F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label8.Location = new System.Drawing.Point(155, 12);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(102, 43);
            this.label8.TabIndex = 17;
            this.label8.Text = "Банк";
            // 
            // richTextBox
            // 
            this.richTextBox.Location = new System.Drawing.Point(421, 12);
            this.richTextBox.Name = "richTextBox";
            this.richTextBox.Size = new System.Drawing.Size(357, 560);
            this.richTextBox.TabIndex = 16;
            this.richTextBox.Text = "";
            // 
            // Gotovo1_button
            // 
            this.Gotovo1_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.Gotovo1_button.Location = new System.Drawing.Point(13, 471);
            this.Gotovo1_button.Name = "Gotovo1_button";
            this.Gotovo1_button.Size = new System.Drawing.Size(379, 77);
            this.Gotovo1_button.TabIndex = 15;
            this.Gotovo1_button.Text = "Готово";
            this.Gotovo1_button.UseVisualStyleBackColor = false;
            this.Gotovo1_button.Click += new System.EventHandler(this.Gotovo1_button_Click);
            // 
            // podkluchenieIB_checkBox
            // 
            this.podkluchenieIB_checkBox.AutoSize = true;
            this.podkluchenieIB_checkBox.Location = new System.Drawing.Point(290, 421);
            this.podkluchenieIB_checkBox.Name = "podkluchenieIB_checkBox";
            this.podkluchenieIB_checkBox.Size = new System.Drawing.Size(56, 24);
            this.podkluchenieIB_checkBox.TabIndex = 14;
            this.podkluchenieIB_checkBox.Text = "Нет";
            this.podkluchenieIB_checkBox.UseVisualStyleBackColor = true;
            this.podkluchenieIB_checkBox.CheckedChanged += new System.EventHandler(this.podkluchenieIB_checkBox_CheckedChanged);
            // 
            // Balans_trackBar
            // 
            this.Balans_trackBar.BackColor = System.Drawing.Color.White;
            this.Balans_trackBar.Cursor = System.Windows.Forms.Cursors.Default;
            this.Balans_trackBar.Location = new System.Drawing.Point(142, 179);
            this.Balans_trackBar.Maximum = 1000;
            this.Balans_trackBar.Name = "Balans_trackBar";
            this.Balans_trackBar.Size = new System.Drawing.Size(249, 56);
            this.Balans_trackBar.TabIndex = 13;
            this.Balans_trackBar.Scroll += new System.EventHandler(this.Balans_trackBar_Scroll);
            // 
            // Tip_vklada_comboBox
            // 
            this.Tip_vklada_comboBox.FormattingEnabled = true;
            this.Tip_vklada_comboBox.Items.AddRange(new object[] {
            "Срочный вклад",
            "Условный вклад",
            "Вклад до востребования"});
            this.Tip_vklada_comboBox.Location = new System.Drawing.Point(142, 135);
            this.Tip_vklada_comboBox.Name = "Tip_vklada_comboBox";
            this.Tip_vklada_comboBox.Size = new System.Drawing.Size(249, 28);
            this.Tip_vklada_comboBox.TabIndex = 12;
            this.Tip_vklada_comboBox.SelectedIndexChanged += new System.EventHandler(this.Tip_vklada_comboBox_SelectedIndexChanged);
            // 
            // Data_otkritiya_dateTimePicker
            // 
            this.Data_otkritiya_dateTimePicker.CalendarTitleBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.Data_otkritiya_dateTimePicker.CalendarTrailingForeColor = System.Drawing.Color.Green;
            this.Data_otkritiya_dateTimePicker.Location = new System.Drawing.Point(142, 252);
            this.Data_otkritiya_dateTimePicker.Name = "Data_otkritiya_dateTimePicker";
            this.Data_otkritiya_dateTimePicker.Size = new System.Drawing.Size(250, 27);
            this.Data_otkritiya_dateTimePicker.TabIndex = 11;
            // 
            // podkluchenieSMS_checkBox
            // 
            this.podkluchenieSMS_checkBox.AutoSize = true;
            this.podkluchenieSMS_checkBox.Location = new System.Drawing.Point(290, 367);
            this.podkluchenieSMS_checkBox.Name = "podkluchenieSMS_checkBox";
            this.podkluchenieSMS_checkBox.Size = new System.Drawing.Size(56, 24);
            this.podkluchenieSMS_checkBox.TabIndex = 10;
            this.podkluchenieSMS_checkBox.Text = "Нет";
            this.podkluchenieSMS_checkBox.UseVisualStyleBackColor = true;
            this.podkluchenieSMS_checkBox.CheckedChanged += new System.EventHandler(this.podkluchenieSMS_checkBox_CheckedChanged);
            // 
            // Vladelets_button
            // 
            this.Vladelets_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.Vladelets_button.Location = new System.Drawing.Point(142, 303);
            this.Vladelets_button.Name = "Vladelets_button";
            this.Vladelets_button.Size = new System.Drawing.Size(249, 38);
            this.Vladelets_button.TabIndex = 8;
            this.Vladelets_button.Text = "Данные владельца";
            this.Vladelets_button.UseVisualStyleBackColor = false;
            this.Vladelets_button.Click += new System.EventHandler(this.button1_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 421);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(245, 20);
            this.label7.TabIndex = 7;
            this.label7.Text = "Подключение интернет-банкинга";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 367);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(230, 20);
            this.label6.TabIndex = 6;
            this.label6.Text = "Подключение смс-оповещения";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 312);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(75, 20);
            this.label5.TabIndex = 5;
            this.label5.Text = "Владелец";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 252);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(110, 20);
            this.label4.TabIndex = 4;
            this.label4.Text = "Дата открытия";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 179);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(72, 20);
            this.label3.TabIndex = 3;
            this.label3.Text = "Баланс =";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 135);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(86, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "Тип вклада";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 81);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Номер счёта";
            // 
            // Nomer_scheta_textBox
            // 
            this.Nomer_scheta_textBox.Location = new System.Drawing.Point(142, 81);
            this.Nomer_scheta_textBox.Name = "Nomer_scheta_textBox";
            this.Nomer_scheta_textBox.Size = new System.Drawing.Size(249, 27);
            this.Nomer_scheta_textBox.TabIndex = 0;
            this.Nomer_scheta_textBox.TextChanged += new System.EventHandler(this.Nomer_scheta_textBox_TextChanged);
            // 
            // Bank
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(790, 584);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Bank";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Bank_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Balans_trackBar)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Nomer_scheta_textBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button Vladelets_button;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DateTimePicker Data_otkritiya_dateTimePicker;
        private System.Windows.Forms.CheckBox podkluchenieSMS_checkBox;
        private System.Windows.Forms.RichTextBox richTextBox;
        private System.Windows.Forms.Button Gotovo1_button;
        private System.Windows.Forms.CheckBox podkluchenieIB_checkBox;
        private System.Windows.Forms.TrackBar Balans_trackBar;
        private System.Windows.Forms.ComboBox Tip_vklada_comboBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
    }
}

