using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;


namespace Lab5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        static string key1;
        static string key2;
        static string key3;

        private void encryptBtnClick(object sender, EventArgs e)
        {
            key1 = key1Box.Text;
            key2 = key2Box.Text;
            key3 = key3Box.Text;
            if (key1.Length != 8 || key2.Length != 8 || key3.Length != 8)
                MessageBox.Show("Длина ключа должна быть равна 8 символам");
            else
            {
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    string source = openFileDialog1.FileName;
                    saveFileDialog1.Filter = "txt files | *.txt";
                    if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        string destination = saveFileDialog1.FileName;
                        EncryptFile(source, destination, key1);
                        EncryptFile(destination, destination, key2);
                        EncryptFile(destination, destination, key3);
                    }
                }
            }
        }

        private void EncryptFile(string source, string destination, string key)
        {
            FileStream fsInput = new FileStream(source, FileMode.Open, FileAccess.Read);
            DESCryptoServiceProvider DES = new DESCryptoServiceProvider();
            DES.Key = ASCIIEncoding.ASCII.GetBytes(key);
            DES.IV = ASCIIEncoding.ASCII.GetBytes(key);
            ICryptoTransform desencrypt = DES.CreateEncryptor();
            byte[] bytearrayinput = new byte[fsInput.Length - 0];
            fsInput.Read(bytearrayinput, 0, bytearrayinput.Length);
            fsInput.Close();
            FileStream fsEncrypted = new FileStream(destination, FileMode.Create, FileAccess.Write);
            CryptoStream cryptoStream = new CryptoStream(fsEncrypted, desencrypt, CryptoStreamMode.Write);
            cryptoStream.Write(bytearrayinput, 0, bytearrayinput.Length);
            cryptoStream.Close();
            fsEncrypted.Close();
        }

        private void DecryptFile(string source, string destination, string key)
        {
            FileStream fsInput = new FileStream(source, FileMode.Open, FileAccess.Read);
            DESCryptoServiceProvider DES = new DESCryptoServiceProvider();
            DES.Key = ASCIIEncoding.ASCII.GetBytes(key);
            DES.IV = ASCIIEncoding.ASCII.GetBytes(key);
            ICryptoTransform desencrypt = DES.CreateDecryptor();
            byte[] bytearrayinput = new byte[fsInput.Length - 0];
            fsInput.Read(bytearrayinput, 0, bytearrayinput.Length);
            fsInput.Close();
            FileStream fsEncrypted = new FileStream(destination, FileMode.Create, FileAccess.Write);
            CryptoStream cryptoStream = new CryptoStream(fsEncrypted, desencrypt, CryptoStreamMode.Write);
            cryptoStream.Write(bytearrayinput, 0, bytearrayinput.Length);
            cryptoStream.Close();
            fsEncrypted.Close();
        }

        private void decryptBtnClick(object sender, EventArgs e)
        {
            key1 = key1Box.Text;
            key2 = key2Box.Text;
            key3 = key3Box.Text;
            if (key1.Length != 8 || key2.Length != 8 || key3.Length != 8)
                MessageBox.Show("Длина ключа должна быть равна 8 символам");
            else
            {
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    string source = openFileDialog1.FileName;
                    saveFileDialog1.Filter = "txt files | *.txt";
                    if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        string destination = saveFileDialog1.FileName;
                        DecryptFile(source, destination, key3);
                        DecryptFile(destination, destination, key2);
                        DecryptFile(destination, destination, key1);
                    }
                }
            }
        }
    }
}
