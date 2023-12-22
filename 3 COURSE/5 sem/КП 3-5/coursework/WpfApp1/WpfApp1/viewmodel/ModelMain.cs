using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Collections;
using Microsoft.Win32;
using WpfApp1.Annotations;
using System.Collections.Generic;
using System.Xml.Linq;
using System.Data.Entity;
using System.Windows.Controls;

namespace WpfApp1.viewmodel
{
    public partial class ModelMain : INotifyPropertyChanged
    {
        private ObservableCollection<Products> _productsList = loginWindow.SushiDb.Products.Local;
        private ObservableCollection<Category> _categoryList = loginWindow.SushiDb.Category.Local;
        private Category _selectedCategory = new Category();
        private Products _products;
        private Commands _delProduct;
        private Commands _addProduct;
        private Commands _changeImage;
        private Commands _delCategory;
        private Commands _addCategory;
        private Commands _plus_minus;
        private Commands _showCommentText;
        private Visibility _visibilityFrame = Visibility.Hidden;
        private Commands _addCommentText;
        private Commands _deleteComment;
        public string NewCommentText { get; set; }
        private double _adminpanel;
        private Commands _sortByName;
        private Commands _sortByPrice;
        private Commands _searchProduct;
        public string SearchLine { get; set; } = string.Empty;

        public ModelMain()
        {
            using (var context = new courseEntities())
            {
                var products = context.Products.ToList();
                ProductCommentsList = new ObservableCollection<ProductComments>(
                    products.Select(p => new ProductComments(p)));
            }
        }

        public Commands SearchProduct
        {
            get
            {
                return _searchProduct ??
                    (_searchProduct = new Commands(obj =>
                    {
                        ProductsList = new ObservableCollection<Products>(
                            loginWindow.SushiDb.Products.Local.Where(o => o.ProductName.ToLower().
                            Contains(SearchLine.ToLower())));
                    }));
            }
        }

        public Commands SortByName
        {
            get
            {
                return _sortByName ??
                    (_sortByName = new Commands(obj =>
                    {
                        ProductsList =
                            new ObservableCollection<Products>(ProductsList.OrderBy(products => products.ProductName));
                    }));
            }
        }
        public Commands SortByPrice
        {
            get
            {
                return _sortByPrice ??
                    (_sortByPrice = new Commands(obj =>
                    {
                        ProductsList =
                            new ObservableCollection<Products>(ProductsList.OrderBy(products => products.Price));
                    }));
            }
        }

        public double AdminPanel
        {
            get => _adminpanel;
            set
            {
                _adminpanel = value;
                OnPropertyChanged("AdminPanel");
            }
        }

        public Visibility VisibilityFrame
        {
            get => _visibilityFrame;
            set
            {
                _visibilityFrame = value;
                OnPropertyChanged("VisibilityFrame");
            }
        }

        public Category SelectedCategory
        {
            get => _selectedCategory;
            set
            {
                if (value != null)
                {
                    _selectedCategory = value;
                    SelectingProductsToCategory();
                }
            }
        }


        public Commands ShowCommentText
        {
            get
            {
                return _showCommentText ??
                    (_showCommentText = new Commands(obj =>
                    {
                        if (VisibilityFrame == Visibility.Hidden)
                        {
                            VisibilityFrame = Visibility.Visible;
                        }
                        else
                            VisibilityFrame = Visibility.Hidden;
                    }));
            }
        }

        public Commands AddCommentText
        {
            get
            {
                return _addCommentText ??
                    (_addCommentText = new Commands(obj =>
                    {
                        Comments newComment = new Comments
                        {
                            CommentText = NewCommentText,
                            ProductID = SelectedProduct.ProductID,
                            ClientID = loginWindow.UserID
                        };
                        var selectedProductComments = ProductCommentsList.FirstOrDefault(pc => 
                            pc.Product.ProductID == SelectedProduct.ProductID);
                        if (selectedProductComments == null)
                        {
                            selectedProductComments = new ProductComments
                            {
                                Product = SelectedProduct,
                                CommentsList = new ObservableCollection<Comments>()
                            };
                            ProductCommentsList.Add(selectedProductComments);
                        }
                        selectedProductComments.CommentsList.Add(newComment);
                        loginWindow.SushiDb.Comments.Add(newComment);
                        OnPropertyChanged("SelectedProductCommentsList");
                        NewCommentText = string.Empty;
                        OnPropertyChanged("NewCommentText");
                    },
                    o => NewCommentText != null && NewCommentText != ""));
            }
        }

        public ObservableCollection<Comments> SelectedProductCommentsList
        {
            get
            {
                var selectedProduct = ProductCommentsList.FirstOrDefault(pc =>
                pc.Product.ProductID == SelectedProduct.ProductID);

                return selectedProduct?.CommentsList;
            }
        }

        public Commands DeleteComment
        {
            get
            {
                return _deleteComment ??
                    (_deleteComment = new Commands(obj =>
                    {
                        if (obj is Comments commentToRemove)
                        {
                            var selectedProduct = ProductCommentsList.FirstOrDefault(pc =>
                            pc.Product.ProductID == SelectedProduct.ProductID);
                            if (selectedProduct != null && selectedProduct.CommentsList.Contains(commentToRemove))
                            {
                                selectedProduct.CommentsList.Remove(commentToRemove);
                                loginWindow.SushiDb.Comments.Remove(commentToRemove);
                                loginWindow.SushiDb.SaveChanges();
                            }
                        }
                    }));
            }
        }

        public Commands AddCategory
        {
            get
            {
                return _addCategory ??
                    (_addCategory = new Commands(obj =>
                    {
                        Category _Category = new Category();
                        _Category.CategoryName = SelectedCategory.CategoryName;
                        CategoryList.Add(_Category);
                        loginWindow.SushiDb.Category.Add(_Category);
                        loginWindow.SushiDb.SaveChanges();
                    }
                    , o => SelectedCategory.CategoryName != null && SelectedCategory.CategoryName != ""));
            }
        }

        public Commands DeleteCategory
        {
            get
            {
                return _delCategory ??
                    (_delCategory = new Commands(obj =>
                    {
                        var delCategory = CategoryList.FirstOrDefault(u => u.CategoryName == SelectedCategory.CategoryName);

                        if (delCategory != null)
                        {
                            var productsInCategory = loginWindow.SushiDb.Products.Any(p => p.CategoryID == delCategory.CategoryID);

                            if (productsInCategory)
                                MessageBox.Show("Невозможно удалить категорию, так как она содержит товары.");
                            else
                                CategoryList.Remove(delCategory);
                        }
                    },
                    o => CategoryList.Count() != 0 && SelectedCategory?.CategoryName != null 
                    && SelectedCategory.CategoryName != ""));
            }
        }

        public Products SelectedProduct
        {
            get => _products;
            set
            {
                if (value != null )
                {
                    _products = value;
                    OnPropertyChanged("SelectedProduct");
                }
            }
        }

        public ObservableCollection<Products> ProductsList
        {
            get => _productsList;
            set
            {
                _productsList = value;
                OnPropertyChanged("ProductsList");
            }
        }

        private ObservableCollection<ProductComments> _productCommentsList = new ObservableCollection<ProductComments>();
        public ObservableCollection<ProductComments> ProductCommentsList
        {
            get => _productCommentsList;
            set
            {
                _productCommentsList = value;
                OnPropertyChanged("ProductCommentsList");
            }
        }


        public ObservableCollection<Category> CategoryList
        {
            get => _categoryList;
            set
            {
                _categoryList = value;
                OnPropertyChanged("CategoryList");
            }
        }

        public Commands plus_minus
        {
            get
            {
                return _plus_minus ??
                    (_plus_minus = new Commands(obj => {

                        switch (obj as string)
                        {
                            case "+":
                                SelectedProduct.product_quantity++;
                                break;
                            case "-":
                                if (SelectedProduct.product_quantity > 0)
                                    SelectedProduct.product_quantity--;
                                break;
                        }
                    }));
            }
        }

        public Commands DeleteProduct
        {
            get
            {
                return _delProduct ??
                    (_delProduct = new Commands(obj =>
                    {
                        if (SelectedProduct != null)
                        {
                            ProductsList.Remove(SelectedProduct); 

                            loginWindow.SushiDb.Products.Remove(SelectedProduct);
                            loginWindow.SushiDb.SaveChanges();
                        }
                    },
                    o => SelectedProduct != null));

            }
        }

        public Commands AddProduct
        {
            get
            {
                return _addProduct ??
                    (_addProduct = new Commands(obj =>
                    {
                        Products _product = new Products();
                        _product.ProductName = string.Empty;
                        _product.Price = 0;
                        ProductsList.Add(_product);
                        loginWindow.SushiDb.Products.Add(_product);
                        loginWindow.SushiDb.SaveChanges();
                    }
                    ));
            }
        }


        public Commands ChangeImage
        {
            get
            {
                return _changeImage ??
                (_changeImage = new Commands(obj =>
                {
                    byte[] binArray = OpenImageDialog();
                    if (binArray == null) return;
                    if ((binArray.Length / 1024) > 1024)
                    {
                        MessageBox.Show("Файл больше мегабайта");
                        return;
                    }

                    if (SelectedProduct != null)
                    {
                        SelectedProduct.ProductImage = binArray;
                        OnPropertyChanged("SelectedProduct");
                    }
                }));
            }
        }

        private byte[] OpenImageDialog()
        {
            var openFileDialog = new OpenFileDialog { Filter = @"Image files (*.jpg,*.png)|*.jpg;*.png" };
            byte[] binArray = null;
            if (openFileDialog.ShowDialog() == true)
            {
                binArray = System.IO.File.ReadAllBytes(openFileDialog.FileName);
            }
            else
            {
                return null;
            }
            return binArray;
        }

        private void SelectingProductsToCategory() => ProductsList = new ObservableCollection<Products>
            (loginWindow.SushiDb.Products.Local.Where(o => o.CategoryID == SelectedCategory.CategoryID));

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
