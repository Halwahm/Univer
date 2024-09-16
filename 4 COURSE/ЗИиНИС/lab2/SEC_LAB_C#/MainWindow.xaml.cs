using Microsoft.Win32;
using SEC_LAB_C_.AffineCH;
using SEC_LAB_C_.ExcelClass;
using SEC_LAB_C_.SaveToFile;
using SEC_LAB_C_.VizinerCH;
using System;
using System.Diagnostics;
using System.IO;
using System.Windows;


namespace SEC_LAB_C
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        string file_origin;

        string path1 = "D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\SavedFile\\Encrypted.txt";
        string path2 = "D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\SavedFile\\Decrypted.txt";

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                string file_path = openFileDialog.FileName;
                file_origin = file_path;
                try
                {
                    string text = File.ReadAllText(file_path);
                    textbox_orginal_txt.Text = text;
                    string fileContent = File.ReadAllText(file_path);
                    int characterCount = fileContent.Length;
                    num_of_symb.Content = characterCount;
                }
                catch (Exception ex)
                {
                    // Обработка ошибки чтения файла
                }
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

            string normal_txt = textbox_orginal_txt.Text;

            int key_a = Convert.ToInt32(input_key_a.Text);
            int key_b = Convert.ToInt32(input_key_b.Text);

            if (russia_rb.IsChecked == true) { 

                //Зашифрование сообщения
                Stopwatch sw = new Stopwatch();
                sw.Start();
                var encrypted_txt = affine_cheaper_ru.AFFINE_ENCRYPTED(normal_txt, key_a, key_b);
                sw.Stop();
                time_encr.Content = sw.ElapsedMilliseconds + " мс";
                //

                //Расшифрование сообщения
                Stopwatch sw2 = new Stopwatch();
                sw2.Start();
                var decrypted_txt = affine_cheaper_ru.AFFINE_DECRYPTED(encrypted_txt, key_a, key_b);
                sw2.Stop();
                time_decr.Content = sw2.ElapsedMilliseconds + " мс";
                //
            
                textbox_encrypted_txt.Text = encrypted_txt;
                textbox_decrypted_txt.Text = decrypted_txt;

                save_to_file.save(textbox_encrypted_txt.Text, path1);
                save_to_file.save(textbox_decrypted_txt.Text, path2);
                
                excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Encrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path1, "Зашифрованное сообщение");
                excel_pr.ExcelPrint1( $"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Decrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path2, "Расшифрованное сообщение");

            }
            
            if (english_rb.IsChecked == true) { //Если английский язык

                //Зашифрование сообщения
                Stopwatch sw = new Stopwatch();
                sw.Start();
                var encrypted_txt = affine_cheaper_eu.AFFINE_ENCRYPTED(normal_txt, key_a, key_b);
                sw.Stop();
                time_encr.Content = sw.ElapsedMilliseconds + " мс";
                //

                //Расшифрование сообщения
                Stopwatch sw2 = new Stopwatch();
                sw2.Start();
                var decrypted_txt = affine_cheaper_eu.AFFINE_DECRYPTED(encrypted_txt, key_a, key_b);
                sw2.Stop();
                time_decr.Content = sw2.ElapsedMilliseconds + " мс";
                //
            
                textbox_encrypted_txt.Text = encrypted_txt;
                textbox_decrypted_txt.Text = decrypted_txt;

                save_to_file.save(textbox_encrypted_txt.Text, path1);
                save_to_file.save(textbox_decrypted_txt.Text, path2);

                excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Encrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path1, "Зашифрованное сообщение");
                excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Decrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path2, "Расшифрованное сообщение");
            }          
            
            if (deut_rb.IsChecked == true) { //Если немецкий язык

                //Зашифрование сообщения
                Stopwatch sw = new Stopwatch();
                sw.Start();
                var encrypted_txt = affine_cheaper_de.AFFINE_ENCRYPTED(normal_txt, key_a, key_b);
                sw.Stop();
                time_encr.Content = sw.ElapsedMilliseconds + " мс";
                //

                //Расшифрование сообщения
                Stopwatch sw2 = new Stopwatch();
                sw2.Start();
                var decrypted_txt = affine_cheaper_de.AFFINE_DECRYPTED(encrypted_txt, key_a, key_b);
                sw2.Stop();
                time_decr.Content = sw2.ElapsedMilliseconds + " мс";
                //
            
                textbox_encrypted_txt.Text = encrypted_txt;
                textbox_decrypted_txt.Text = decrypted_txt;

                save_to_file.save(textbox_encrypted_txt.Text, path1);
                save_to_file.save(textbox_decrypted_txt.Text, path2);

                excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Encrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path1, "Зашифрованное сообщение");
                excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Decrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path2, "Расшифрованное сообщение");
            }


        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                string file_path = openFileDialog.FileName;
                file_origin = file_path;
                try
                {
                    string text = File.ReadAllText(file_path);
                    textbox_orginal_txt_viz.Text = text;
                    string fileContent = File.ReadAllText(file_path);
                    int characterCount = fileContent.Length;
                    num_of_symb_viz.Content = characterCount;
                }
                catch (Exception ex)
                {
                    // Обработка ошибки чтения файла
                }
            }
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            string key_a = input_key_secondname.Text;

            Stopwatch sw4 = new Stopwatch();
            sw4.Start();
            var encrypted_txt = viziner_encr.Encrypt(textbox_orginal_txt_viz.Text, key_a);
            sw4.Stop();
            time_encr_viz.Content = sw4.ElapsedMilliseconds + "мс";
            textbox_encrypted_txt_viz.Text = encrypted_txt;

            Stopwatch sw3 = new Stopwatch();
            sw3.Start();
            var decrypted_txt = viziner_encr.Decrypt(textbox_encrypted_txt_viz.Text, key_a);
            sw3.Stop();
            time_decr_viz.Content = sw3.ElapsedMilliseconds + "мс";
            textbox_decrypted_txt_viz.Text = decrypted_txt;


            save_to_file.save(textbox_encrypted_txt_viz.Text, path1);
            save_to_file.save(textbox_decrypted_txt_viz.Text, path2);

            excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Encrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path1, "Зашифрованное сообщение");
            excel_pr.ExcelPrint1($"D:\\My Files\\Univer\\4 COURSE\\ЗИиНИС\\lab2\\EXCEL\\Decrypted_vers{DateTime.Now.ToString("hh.mm.ss")}.xlsx", path2, "Расшифрованное сообщение");

        }
    }
}
