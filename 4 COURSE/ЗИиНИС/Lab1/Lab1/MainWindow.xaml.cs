using System.Windows;

namespace Lab1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Result.Text = simpleNumbers.getSimpleNumbers(NumberA.Text, NumberB.Text);
           
        }

        private void GetNod(object sender, RoutedEventArgs e)
        {
            Result.Text = nodCreator.getNod(NumberA.Text, NumberB.Text, NumberC.Text);
        }
        
    }
}
