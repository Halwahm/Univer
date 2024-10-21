using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        private static readonly Encoding encoding = Encoding.Default;
        BigInteger p;
        BigInteger q;
        BigInteger ee;
        BigInteger n;
        BigInteger x = -1;
        public Form1()
        {
            InitializeComponent();
            p = new BigInteger(new byte[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 });
            q = new BigInteger(new byte[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            ee = new BigInteger(new byte[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2 });
            n = p * q;
        }

        private void GenerateClick(object sender, EventArgs e)
        {
            if(x == -1)
            {
                Random rnd = new Random();
                x = rnd.Next(0,int.MaxValue);
            }
            BigInteger newX = BigInteger.ModPow(x, ee, n);
            x = newX;
            string newx = newX.ToBinaryString();
            SequenceBox.Text += newx[newx.Length - 1];
        }

        private void ResetClick(object sender, EventArgs e)
        {
            x = -1;
            SequenceBox.Clear();
        }

        private void EncryptClick(object sender, EventArgs e)
        {
            byte[] key = ASCIIEncoding.ASCII.GetBytes(761118554211.ToString());

            RC4 encoder = new RC4(key);
            string testString = RC4Box.Text;
            byte[] testBytes = ASCIIEncoding.ASCII.GetBytes(testString);
            byte[] result = encoder.Encode(testBytes, testBytes.Length);

            string res = BitConverter.ToString(result);
            RC4 decoder = new RC4(key);
            byte[] decryptedBytes = decoder.Decode(result, result.Length);
            string decryptedString = ASCIIEncoding.ASCII.GetString(decryptedBytes);

            RC4Box.Clear();
            RC4Box.Text += encoding.GetString(result);
        }

        private void DecryptClick(object sender, EventArgs e)
        {
            byte[] key = ASCIIEncoding.ASCII.GetBytes(761118554211.ToString());
            byte[] result = encoding.GetBytes(RC4Box.Text);
            RC4 decoder = new RC4(key);
            byte[] decryptedBytes = decoder.Decode(result, result.Length);
            string decryptedString = ASCIIEncoding.ASCII.GetString(decryptedBytes);
            RC4Box.Clear();
            RC4Box.Text += decryptedString;
        }
    }
}
