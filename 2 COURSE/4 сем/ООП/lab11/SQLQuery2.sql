create database StoreDb;

use StoreDb;

CREATE TABLE Product (
  Id INT IDENTITY(1,1) PRIMARY KEY,
  Name NVARCHAR(MAX) NOT NULL,
  Quantity INT NOT NULL,
  Price DECIMAL(18,2) NOT NULL,
  IsSelected BIT NOT NULL
);
