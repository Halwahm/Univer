using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1.viewmodel
{
    public class ProductComments: INotifyPropertyChanged
    {
        public Products Product;

        private ObservableCollection<Comments> _commentsList;
        public ObservableCollection<Comments> CommentsList
        {
            get { return _commentsList; }
            set
            {
                _commentsList = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public ProductComments(Products product)
        {
            Product = product;
            CommentsList = new ObservableCollection<Comments>();
        }
        public ProductComments()
        {
            CommentsList = new ObservableCollection<Comments>();
        }
    }

}
