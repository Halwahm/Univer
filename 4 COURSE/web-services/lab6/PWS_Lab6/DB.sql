create database WSVVS;
use WSVVS;
use master;
drop database WSVVS;

create table student(
    id int identity(1,1) primary key,
    name nvarchar(50)
)

create table note(
    id int identity(1,1) primary key,
    stud_id int references student(id),
    subject nvarchar(20),
    note int
)

insert into student (name) values ('Vlad');
insert into student (name) values ('Ilya');
insert into student (name) values ('Nikita');
insert into student (name) values ('Stacy');
    
insert into note (stud_id, subject, note) values (1, 'DB', 1);
insert into note (stud_id, subject, note) values (1, 'PIS', 2);
insert into note (stud_id, subject, note) values (1, 'KIS', 3);
insert into note (stud_id, subject, note) values (2, 'RIS', 4);
insert into note (stud_id, subject, note) values (2, 'Business', 5);
insert into note (stud_id, subject, note) values (2, 'PMS', 6);
insert into note (stud_id, subject, note) values (3, 'Crypta', 7);

select * from student;
select * from note;
