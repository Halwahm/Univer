using Lab09.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Windows;

namespace Lab09
{
    public class MyContext : DbContext
    {
        public DbSet<Author> Authors { get; set; }
        public DbSet<Book> Books { get; set; }
    }

    public partial class MainWindow : Window
    {
        private AuthorRepository _authorRepository = new AuthorRepository();
        private List<Author> authors = new List<Author>();
        private MyContext db = new MyContext();
        public MainWindow()
        {
            InitializeComponent();
            LoadData();
        }

        private async void LoadData()
        {
            authors = db.Authors.ToList();
            authorsListView.ItemsSource = authors;
        }

        private async void Add_Click(object sender, RoutedEventArgs e)
        {
            var author = new Author { Name = "Leo Tolstoy" };
            await _authorRepository.AddAuthor(author);
            authors.Add(author);
            authorsListView.Items.Refresh();
        }

        private async void Update_Click(object sender, RoutedEventArgs e)
        {
            foreach (Author author in authorsListView.SelectedItems)
            {
                // Находим автора с выбранным именем
                var selectedAuthor = await _authorRepository.GetAuthorById(author.AuthorId);
                if (selectedAuthor != null)
                {
                    // Изменяем имя автора
                    selectedAuthor.Name = "Leo N. Tolstoy";
                    await _authorRepository.UpdateAuthor(selectedAuthor);
                }
            }
            // Обновляем список авторов в ListView
            authorsListView.Items.Refresh();
        }


        private async void Delete_Click(object sender, RoutedEventArgs e)
        {
            foreach (Author author in authorsListView.SelectedItems)
            {
                // Находим автора с выбранным именем
                var selectedAuthor = await _authorRepository.GetAuthorById(author.AuthorId);
                if (selectedAuthor != null)
                {
                    // Удаляем автора
                    await _authorRepository.DeleteAuthor(author.AuthorId);
                    // Удаляем автора из списка авторов в приложении
                    authors.Remove(author);
                }
            }
            // Обновляем список авторов в ListView
            authorsListView.Items.Refresh();
        }

        private async void Read_Click(object sender, RoutedEventArgs e)
        {
            authors = (await _authorRepository.GetAuthorsByName("Leo")).ToList();
            authorsListView.ItemsSource = authors;
        }

        private async void Sort_Click(object sender, RoutedEventArgs e)
        {
            authors = (await _authorRepository.GetAuthorsOrderedByName()).ToList();
            authorsListView.ItemsSource = authors;
        }

        private async void Async_Click(object sender, RoutedEventArgs e)
        {
            var author = new Author { Name = "Jane Austen" };
            await _authorRepository.AddAuthor(author);
            authors.Add(author);
            authorsListView.Items.Refresh();
        }

        private void Tran_Click(object sender, RoutedEventArgs e)
        {
            _authorRepository.BeginTransaction();
            try
            {
                _authorRepository.AddAuthor(new Author { Name = "Charles Dickens" });
                _authorRepository.SaveChangesAsync().Wait();


                _authorRepository.CommitTransaction();
                authorsListView.ItemsSource = authors;
            }
            catch (Exception ex)
            {
                _authorRepository.RollbackTransaction();
            }
        }

        private async void SQL_Click(object sender, RoutedEventArgs e)
        {
            _authorRepository.ExecuteSqlCommand("INSERT INTO Authors (Name) VALUES ('William Shakespeare')");
            authors = (await _authorRepository.GetAuthors()).ToList();
            authorsListView.ItemsSource = authors;
        }
    }
}
