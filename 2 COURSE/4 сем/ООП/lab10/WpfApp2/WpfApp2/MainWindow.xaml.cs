using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using WpfApp2.classes;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory;

namespace WpfApp2
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private UnitOfWork uow;
        public MainWindow()
        {
            InitializeComponent();
            uow = new UnitOfWork();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Show();
        }

        private void Show()
        {
            using (ApplicationContext db = new ApplicationContext())
            {
                using (var transaction = db.Database.BeginTransaction())
                {
                    try
                    {
                        var query =
                        from person in db.PERSON
                        join address in db.ADDRESS
                        on person.id_address equals address.id_address
                        join passport in db.PASSPORT
                        on person.id_passport equals passport.id_passport
                        select new
                        {
                            person.id_person,
                            person.first_name,
                            person.middle_name,
                            person.last_name,
                            person.age,
                            person.phone,
                            person.id_passport,
                            person.id_address,
                            address.country,
                            address.city,
                            address.street,
                            address.house,
                            address.build,
                            address.flat,
                            passport.serial,
                            passport.number,
                            passport.photo
                        };
                        table.ItemsSource = query.ToList();
                    }
                    catch (Exception ex)
                    {
                        transaction.Rollback();
                    }
                }
            }
        }

        private void insertButton_Click(object sender, RoutedEventArgs e)
        {
            Insert insert = new Insert();
            insert.ShowDialog();
            Show();
        }

        private void deleteButton_Click(object sender, RoutedEventArgs e)
        {
            using (ApplicationContext db = new ApplicationContext())
            {
                using (var transaction = db.Database.BeginTransaction())
                {
                    try
                    {
                        var person = db.PERSON.Where(p => p.id_person ==
                        (int)table.SelectedItem.GetType().GetProperty("id_person").GetValue(table.SelectedItem)).FirstOrDefault();
                        var address = db.ADDRESS.Where(a => a.id_address ==
                        (int)table.SelectedItem.GetType().GetProperty("id_address").GetValue(table.SelectedItem)).FirstOrDefault();
                        var passport = uow.Passports.GetAll().Where(p => p.id_passport ==
                        (int)table.SelectedItem.GetType().GetProperty("id_passport").GetValue(table.SelectedItem)).FirstOrDefault();

                        uow.Persons.Delete(person.id_person);
                        uow.Addresses.Delete(address.id_address);
                        uow.Passports.Delete(passport.id_passport);
                        uow.Save();
                        transaction.Commit();
                    }
                    catch (Exception ex)
                    {
                        transaction.Rollback();
                    }
                }
            }
            Show();
        }

        private void updateButton_Click(object sender, RoutedEventArgs e)
        {
            Update update = new Update(table.SelectedItem);
            update.ShowDialog();
            Show();
        }

        private void viewButton_Click(object sender, RoutedEventArgs e)
        {
            Show();
        }

        private void selectButton_Click(object sender, RoutedEventArgs e)
        {
            using (ApplicationContext db = new ApplicationContext())
            {
                using (var transaction = db.Database.BeginTransaction())
                {
                    try
                    {
                        var listPerson = from p in db.PERSON
                                         join a in db.ADDRESS on p.id_address equals a.id_address
                                         join ps in db.PASSPORT on p.id_passport equals ps.id_passport
                                         where p.age == int.Parse(ageTextBox.Text) &&
                                         a.country == countryTextBox.Text
                                         select new
                                         {
                                             p.id_person,
                                             p.first_name,
                                             p.middle_name,
                                             p.last_name,
                                             p.age,
                                             p.phone,
                                             p.id_passport,
                                             p.id_address,
                                             a.country,
                                             a.city,
                                             a.street,
                                             a.house,
                                             a.build,
                                             a.flat,
                                             ps.serial,
                                             ps.number,
                                             ps.photo
                                         };
                        table.ItemsSource = listPerson.ToList();
                    }
                    catch (Exception ex)
                    {
                        transaction.Rollback();
                    }
                }
            }
        }
    }
}
