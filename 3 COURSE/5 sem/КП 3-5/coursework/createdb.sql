create database sushi_db;

use sushi_db;


-- Таблица категорий блюд
create table Category
(
    CategoryID int primary key identity(1,1),
    CategoryName nvarchar(20)
);

-- Таблица клиентов
create table Clients
(
    ClientID int identity(1,1) primary key not null,
    Email nvarchar(40) not null,
    FirstName nvarchar(20) not null,
    LastName nvarchar(20) not null,
    Address nvarchar(50) not null, 
    PhoneNumber nvarchar(15) not null,
    PasswordHash nvarchar(64) not null 
);

-- Таблица продуктов (блюд)
create table Products
(
    ProductID int primary key identity(1,1),
    ProductName nvarchar(50) not null, 
    ProductImage varbinary(max),
    Price money not null, 
    CategoryID int,
    constraint FK_Category_Products foreign key (CategoryID) references Category(CategoryID)
);

-- Таблица заказов
create table Orders
(
    OrderID int primary key,
    ClientID int, 
    TotalPrice money not null,
    Status nvarchar(20),
    Amount money,
    constraint FK_Client_Orders foreign key (ClientID) references Clients(ClientID)
);

-- Таблица комментариев к блюдам
create table Comments
(
    CommentID int primary key identity(1,1),
    ProductID int,
    ClientID int,
    CommentText varchar(100),
    constraint FK_Comments_Products foreign key (ProductID) references Products(ProductID),
    constraint FK_Comments_Clients foreign key (ClientID) references Clients(ClientID)
);


-- Таблица деталей заказа
create table OrderDetails
(
    DetailID int primary key,
    OrderID int,
    ProductID int,
    Address nvarchar(50),
    constraint FK_OrderDetails_Orders foreign key (OrderID) references Orders(OrderID)
);

ALTER TABLE Clients
ADD CONSTRAINT UC_Email UNIQUE (Email);

