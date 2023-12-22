using System.Windows.Controls;
using WpfApp1.viewmodel;

namespace WpfApp1
{
    public partial class Comments : Page
    {
        public Comments()
        {
            InitializeComponent();
            DataContext = loginWindow._ModelMain;
        }
    }
}
