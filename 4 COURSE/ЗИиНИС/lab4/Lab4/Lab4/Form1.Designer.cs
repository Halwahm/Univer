namespace Lab4
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.textToEncypt = new System.Windows.Forms.RichTextBox();
            this.encryptedText = new System.Windows.Forms.RichTextBox();
            this.rRotList = new System.Windows.Forms.ComboBox();
            this.mRotList = new System.Windows.Forms.ComboBox();
            this.lRotList = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.button16 = new System.Windows.Forms.Button();
            this.button17 = new System.Windows.Forms.Button();
            this.button18 = new System.Windows.Forms.Button();
            this.button19 = new System.Windows.Forms.Button();
            this.button20 = new System.Windows.Forms.Button();
            this.button21 = new System.Windows.Forms.Button();
            this.button22 = new System.Windows.Forms.Button();
            this.button23 = new System.Windows.Forms.Button();
            this.button24 = new System.Windows.Forms.Button();
            this.button25 = new System.Windows.Forms.Button();
            this.button26 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textToEncypt
            // 
            this.textToEncypt.Location = new System.Drawing.Point(592, 140);
            this.textToEncypt.Name = "textToEncypt";
            this.textToEncypt.Size = new System.Drawing.Size(229, 228);
            this.textToEncypt.TabIndex = 0;
            this.textToEncypt.Text = "";
            // 
            // encryptedText
            // 
            this.encryptedText.Location = new System.Drawing.Point(12, 35);
            this.encryptedText.Name = "encryptedText";
            this.encryptedText.Size = new System.Drawing.Size(565, 149);
            this.encryptedText.TabIndex = 1;
            this.encryptedText.Text = "";
            // 
            // rRotList
            // 
            this.rRotList.DropDownWidth = 10;
            this.rRotList.FormattingEnabled = true;
            this.rRotList.Location = new System.Drawing.Point(756, 51);
            this.rRotList.Name = "rRotList";
            this.rRotList.Size = new System.Drawing.Size(45, 24);
            this.rRotList.TabIndex = 3;
            // 
            // mRotList
            // 
            this.mRotList.DropDownWidth = 10;
            this.mRotList.FormattingEnabled = true;
            this.mRotList.Location = new System.Drawing.Point(676, 51);
            this.mRotList.Name = "mRotList";
            this.mRotList.Size = new System.Drawing.Size(48, 24);
            this.mRotList.TabIndex = 4;
            // 
            // lRotList
            // 
            this.lRotList.DropDownWidth = 10;
            this.lRotList.FormattingEnabled = true;
            this.lRotList.Location = new System.Drawing.Point(593, 51);
            this.lRotList.Name = "lRotList";
            this.lRotList.Size = new System.Drawing.Size(44, 24);
            this.lRotList.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(782, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 16);
            this.label1.TabIndex = 6;
            this.label1.Text = "R";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(703, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 16);
            this.label2.TabIndex = 7;
            this.label2.Text = "M";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(621, 27);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(14, 16);
            this.label3.TabIndex = 8;
            this.label3.Text = "L";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(29, 220);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(45, 45);
            this.button1.TabIndex = 9;
            this.button1.Text = "Q";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(437, 221);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(45, 45);
            this.button2.TabIndex = 10;
            this.button2.Text = "O";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(488, 221);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(45, 45);
            this.button3.TabIndex = 11;
            this.button3.Text = "P";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(386, 221);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(45, 45);
            this.button4.TabIndex = 12;
            this.button4.Text = "I";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(335, 221);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(45, 45);
            this.button5.TabIndex = 13;
            this.button5.Text = "U";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(284, 221);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(45, 45);
            this.button6.TabIndex = 14;
            this.button6.Text = "Y";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(233, 221);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(45, 45);
            this.button7.TabIndex = 15;
            this.button7.Text = "T";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(182, 221);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(45, 45);
            this.button8.TabIndex = 16;
            this.button8.Text = "R";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(131, 221);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(45, 45);
            this.button9.TabIndex = 17;
            this.button9.Text = "E";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(80, 221);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(45, 45);
            this.button10.TabIndex = 18;
            this.button10.Text = "W";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(107, 272);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(45, 45);
            this.button11.TabIndex = 27;
            this.button11.Text = "S";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(158, 272);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(45, 45);
            this.button12.TabIndex = 26;
            this.button12.Text = "D";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(209, 272);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(45, 45);
            this.button13.TabIndex = 25;
            this.button13.Text = "F";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(260, 272);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(45, 45);
            this.button14.TabIndex = 24;
            this.button14.Text = "G";
            this.button14.UseVisualStyleBackColor = true;
            this.button14.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button15
            // 
            this.button15.Location = new System.Drawing.Point(311, 272);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(45, 45);
            this.button15.TabIndex = 23;
            this.button15.Text = "H";
            this.button15.UseVisualStyleBackColor = true;
            this.button15.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(362, 272);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(45, 45);
            this.button16.TabIndex = 22;
            this.button16.Text = "J";
            this.button16.UseVisualStyleBackColor = true;
            this.button16.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button17
            // 
            this.button17.Location = new System.Drawing.Point(413, 272);
            this.button17.Name = "button17";
            this.button17.Size = new System.Drawing.Size(45, 45);
            this.button17.TabIndex = 21;
            this.button17.Text = "K";
            this.button17.UseVisualStyleBackColor = true;
            this.button17.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button18
            // 
            this.button18.Location = new System.Drawing.Point(464, 272);
            this.button18.Name = "button18";
            this.button18.Size = new System.Drawing.Size(45, 45);
            this.button18.TabIndex = 20;
            this.button18.Text = "L";
            this.button18.UseVisualStyleBackColor = true;
            this.button18.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button19
            // 
            this.button19.Location = new System.Drawing.Point(56, 272);
            this.button19.Name = "button19";
            this.button19.Size = new System.Drawing.Size(45, 45);
            this.button19.TabIndex = 19;
            this.button19.Text = "A";
            this.button19.UseVisualStyleBackColor = true;
            this.button19.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button20
            // 
            this.button20.Location = new System.Drawing.Point(158, 323);
            this.button20.Name = "button20";
            this.button20.Size = new System.Drawing.Size(45, 45);
            this.button20.TabIndex = 34;
            this.button20.Text = "X";
            this.button20.UseVisualStyleBackColor = true;
            this.button20.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button21
            // 
            this.button21.Location = new System.Drawing.Point(209, 323);
            this.button21.Name = "button21";
            this.button21.Size = new System.Drawing.Size(45, 45);
            this.button21.TabIndex = 33;
            this.button21.Text = "C";
            this.button21.UseVisualStyleBackColor = true;
            this.button21.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button22
            // 
            this.button22.Location = new System.Drawing.Point(260, 323);
            this.button22.Name = "button22";
            this.button22.Size = new System.Drawing.Size(45, 45);
            this.button22.TabIndex = 32;
            this.button22.Text = "V";
            this.button22.UseVisualStyleBackColor = true;
            this.button22.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button23
            // 
            this.button23.Location = new System.Drawing.Point(311, 323);
            this.button23.Name = "button23";
            this.button23.Size = new System.Drawing.Size(45, 45);
            this.button23.TabIndex = 31;
            this.button23.Text = "B";
            this.button23.UseVisualStyleBackColor = true;
            this.button23.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button24
            // 
            this.button24.Location = new System.Drawing.Point(362, 323);
            this.button24.Name = "button24";
            this.button24.Size = new System.Drawing.Size(45, 45);
            this.button24.TabIndex = 30;
            this.button24.Text = "N";
            this.button24.UseVisualStyleBackColor = true;
            this.button24.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button25
            // 
            this.button25.Location = new System.Drawing.Point(413, 323);
            this.button25.Name = "button25";
            this.button25.Size = new System.Drawing.Size(45, 45);
            this.button25.TabIndex = 29;
            this.button25.Text = "M";
            this.button25.UseVisualStyleBackColor = true;
            this.button25.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // button26
            // 
            this.button26.Location = new System.Drawing.Point(107, 323);
            this.button26.Name = "button26";
            this.button26.Size = new System.Drawing.Size(45, 45);
            this.button26.TabIndex = 28;
            this.button26.Text = "Z";
            this.button26.UseVisualStyleBackColor = true;
            this.button26.Click += new System.EventHandler(this.encrytpBtnClick);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(156, 16);
            this.label4.TabIndex = 35;
            this.label4.Text = "Зашифрованный текст";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(592, 117);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(110, 16);
            this.label5.TabIndex = 36;
            this.label5.Text = "Исходный текст";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(833, 394);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.button20);
            this.Controls.Add(this.button21);
            this.Controls.Add(this.button22);
            this.Controls.Add(this.button23);
            this.Controls.Add(this.button24);
            this.Controls.Add(this.button25);
            this.Controls.Add(this.button26);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.button14);
            this.Controls.Add(this.button15);
            this.Controls.Add(this.button16);
            this.Controls.Add(this.button17);
            this.Controls.Add(this.button18);
            this.Controls.Add(this.button19);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lRotList);
            this.Controls.Add(this.mRotList);
            this.Controls.Add(this.rRotList);
            this.Controls.Add(this.encryptedText);
            this.Controls.Add(this.textToEncypt);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox textToEncypt;
        private System.Windows.Forms.RichTextBox encryptedText;
        private System.Windows.Forms.ComboBox rRotList;
        private System.Windows.Forms.ComboBox mRotList;
        private System.Windows.Forms.ComboBox lRotList;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.Button button17;
        private System.Windows.Forms.Button button18;
        private System.Windows.Forms.Button button19;
        private System.Windows.Forms.Button button20;
        private System.Windows.Forms.Button button21;
        private System.Windows.Forms.Button button22;
        private System.Windows.Forms.Button button23;
        private System.Windows.Forms.Button button24;
        private System.Windows.Forms.Button button25;
        private System.Windows.Forms.Button button26;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}

