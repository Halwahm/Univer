namespace lab4.WinForm
{
    partial class Form1
    {
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

        private void InitializeComponent()
        {
            this.s1Value = new System.Windows.Forms.TextBox();
            this.k1Value = new System.Windows.Forms.TextBox();
            this.f1Value = new System.Windows.Forms.TextBox();
            this.s2Value = new System.Windows.Forms.TextBox();
            this.k2Value = new System.Windows.Forms.TextBox();
            this.f2Value = new System.Windows.Forms.TextBox();
            this.runBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // s1Value
            // 
            this.s1Value.Location = new System.Drawing.Point(140, 50);
            this.s1Value.Name = "s1Value";
            this.s1Value.Size = new System.Drawing.Size(150, 22);
            this.s1Value.TabIndex = 0;
            // 
            // k1Value
            // 
            this.k1Value.Location = new System.Drawing.Point(140, 90);
            this.k1Value.Name = "k1Value";
            this.k1Value.Size = new System.Drawing.Size(150, 22);
            this.k1Value.TabIndex = 1;
            // 
            // f1Value
            // 
            this.f1Value.Location = new System.Drawing.Point(140, 130);
            this.f1Value.Name = "f1Value";
            this.f1Value.Size = new System.Drawing.Size(150, 22);
            this.f1Value.TabIndex = 2;
            // 
            // s2Value
            // 
            this.s2Value.Location = new System.Drawing.Point(440, 50);
            this.s2Value.Name = "s2Value";
            this.s2Value.Size = new System.Drawing.Size(150, 22);
            this.s2Value.TabIndex = 3;
            // 
            // k2Value
            // 
            this.k2Value.Location = new System.Drawing.Point(440, 90);
            this.k2Value.Name = "k2Value";
            this.k2Value.Size = new System.Drawing.Size(150, 22);
            this.k2Value.TabIndex = 4;
            // 
            // f2Value
            // 
            this.f2Value.Location = new System.Drawing.Point(440, 130);
            this.f2Value.Name = "f2Value";
            this.f2Value.Size = new System.Drawing.Size(150, 22);
            this.f2Value.TabIndex = 5;
            // 
            // runBtn
            // 
            this.runBtn.Location = new System.Drawing.Point(300, 200);
            this.runBtn.Name = "runBtn";
            this.runBtn.Size = new System.Drawing.Size(100, 30);
            this.runBtn.TabIndex = 6;
            this.runBtn.Text = "Run Sum";
            this.runBtn.UseVisualStyleBackColor = true;
            this.runBtn.Click += new System.EventHandler(this.runBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(40, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(88, 16);
            this.label1.TabIndex = 7;
            this.label1.Text = "s (Object 1):";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(40, 93);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 16);
            this.label2.TabIndex = 8;
            this.label2.Text = "k (Object 1):";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(40, 133);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 16);
            this.label3.TabIndex = 9;
            this.label3.Text = "f (Object 1):";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(340, 53);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(88, 16);
            this.label4.TabIndex = 10;
            this.label4.Text = "s (Object 2):";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(340, 93);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(89, 16);
            this.label5.TabIndex = 11;
            this.label5.Text = "k (Object 2):";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(340, 133);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 16);
            this.label6.TabIndex = 12;
            this.label6.Text = "f (Object 2):";
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(640, 300);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.runBtn);
            this.Controls.Add(this.f2Value);
            this.Controls.Add(this.k2Value);
            this.Controls.Add(this.s2Value);
            this.Controls.Add(this.f1Value);
            this.Controls.Add(this.k1Value);
            this.Controls.Add(this.s1Value);
            this.Name = "Form1";
            this.Text = "Sum Method Demo";
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.TextBox s1Value;
        private System.Windows.Forms.TextBox k1Value;
        private System.Windows.Forms.TextBox f1Value;
        private System.Windows.Forms.TextBox s2Value;
        private System.Windows.Forms.TextBox k2Value;
        private System.Windows.Forms.TextBox f2Value;
        private System.Windows.Forms.Button runBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}
