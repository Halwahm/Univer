create database app1;

use app1;

create table ADDRESS (
	id_address int identity(1,1) primary key,
	country nchar(20),
	city nchar(20),
	street nchar(20),
	house int,
	build int,
	flat int
);


create table PASSPORT (
	id_passport int identity(1,1) primary key,
	serial nchar(20),
	number int,
	photo image
);


create table PERSON (
	id_person int identity(1,1) primary key,
	first_name nchar(10),
	middle_name nchar(10),
	last_name nchar(10),
	age int,
	phone nchar(10),

	id_address int,
	CONSTRAINT FK_Person_ADDRESS 
    FOREIGN KEY (id_address) 
    REFERENCES ADDRESS (id_address),

	id_passport int,
	CONSTRAINT FK_Person_PASSPORT 
    FOREIGN KEY (id_passport) 
    REFERENCES PASSPORT (id_passport)
);
