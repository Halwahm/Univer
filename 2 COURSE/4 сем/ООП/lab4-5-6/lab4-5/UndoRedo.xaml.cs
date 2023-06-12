using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace lab4_5
{
    /// <summary>
    /// Логика взаимодействия для UndoRedo.xaml
    /// </summary>
    public partial class UndoRedo : UserControl
    {
        public UndoRedo()
        {
            InitializeComponent();
        }

        private void Redo_Click(object sender, RoutedEventArgs e)
        {
            Control.Redo();
        }

        private void Undo_Click(object sender, RoutedEventArgs e)
        {
            Control.Undo();
        }
    }
}
