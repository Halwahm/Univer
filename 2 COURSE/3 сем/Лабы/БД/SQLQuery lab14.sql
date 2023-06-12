use Halaleenko_laba4;
	
-- 1-4. �������� ��� insert, delete, update + �����

create table TR_AUDIT
(
ID int primary key identity, -- �����
STMT varchar(20) check (STMT in ('INS', 'DEL', 'UPD')), -- DML-��������
TRNAME varchar(50), -- ��� ��������
CC varchar(300) -- �����������
)

go
create trigger TR_TEACHER_INS on TEACHER after INSERT as
declare @ID varchar(10), @NAME varchar(50), @GENDER char(1), @PULPIT varchar(15), @RESULT varchar(300)
set @ID = RTRIM((select TEACHER from INSERTED))
set @NAME = (select TEACHER_NAME from INSERTED)
set @GENDER = (select GENDER from INSERTED)
set @PULPIT = RTRIM((select PULPIT from INSERTED))

if (@GENDER not in ('�', '�'))
	raiserror('��� ������ �������', 10,1)

set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
insert into TR_AUDIT values ('INS', 'TR_TEACHER_INS', @RESULT)
go


create trigger TR_TEACHER_DEL on TEACHER after DELETE as
declare @ID varchar(10), @NAME varchar(50), @GENDER char(1), @PULPIT varchar(15), @RESULT varchar(300)
set @ID = RTRIM((select TEACHER from DELETED))
set @NAME = (select TEACHER_NAME from DELETED)
set @GENDER = (select GENDER from DELETED)
set @PULPIT = RTRIM((select PULPIT from DELETED))
set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
insert into TR_AUDIT values ('DEL', 'TR_TEACHER_DEL', @RESULT)
go


create trigger TR_TEACHER_UPD on TEACHER after UPDATE as
declare @ID varchar(10), @NAME varchar(50), @GENDER char(1), @PULPIT varchar(15), @RESULT varchar(300)
set @ID = RTRIM((select TEACHER from DELETED))
set @NAME = (select TEACHER_NAME from DELETED)
set @GENDER = (select GENDER from DELETED)
set @PULPIT = RTRIM((select PULPIT from DELETED))
set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT + ' -- '
set @ID = RTRIM((select TEACHER from INSERTED))
set @NAME = (select TEACHER_NAME from INSERTED)
set @GENDER = (select GENDER from INSERTED)
set @PULPIT = RTRIM((select PULPIT from INSERTED))
set @RESULT = @RESULT + @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
insert into TR_AUDIT values ('UPD', 'TR_TEACHER_UPD', @RESULT)
go


create trigger TR_TEACHER on TEACHER after INSERT, DELETE, UPDATE as
declare @ID varchar(10), @NAME varchar(50), @GENDER char(1), @PULPIT varchar(15), @OPERATION char(3), @RESULT varchar(300)
if ((select count(*) from DELETED) > 0)
begin
	set @ID = RTRIM((select TEACHER from DELETED))
	set @NAME = (select TEACHER_NAME from DELETED)
	set @GENDER = (select GENDER from DELETED)
	set @PULPIT = RTRIM((select PULPIT from DELETED))
	set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
	set @OPERATION = 'DEL'
end
if ((select count(*) from INSERTED) > 0)
begin
	set @ID = RTRIM((select TEACHER from INSERTED))
	set @NAME = (select TEACHER_NAME from INSERTED)
	set @GENDER = (select GENDER from INSERTED)
	set @PULPIT = RTRIM((select PULPIT from INSERTED))
	if ((select count(*) from DELETED) > 0)
	begin
		set @RESULT = @RESULT +  '-- ' +  @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
		set @OPERATION = 'UPD'
	end
	else 
	begin
		set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
		set @OPERATION = 'INS'
	end
end
insert into TR_AUDIT values (@OPERATION, 'TR_TEACHER', @RESULT)
go
return;
go


insert into TEACHER values ('���', '������ ������ �������', '�', '����')
update TEACHER set TEACHER = '�����' where TEACHER = '���' 
delete from TEACHER where TEACHER = '���'

select * from TR_AUDIT

delete from TR_AUDIT
go

----------------------------------------------------------------------------------------
drop trigger TR_TEACHER_INS
drop trigger TR_TEACHER_DEL
drop trigger TR_TEACHER_UPD
drop table TR_AUDIT
go

-- 5. ��������, ��� ����������� ����������� ����������� �� ��������
insert into TEACHER --������� �����������, ����� insert
values ('���', '������ ������ �������', '�', '����')
insert into TEACHER
values ('���', '������ ������ �������', '�', '����')
delete from TEACHER where TEACHER = '���'
select * from TR_AUDIT
go


-- 6-7. ������� ���������� ���������
create trigger TR_TEACHER_DEL_B on TEACHER after DELETE as
declare @ID varchar(10), @NAME varchar(50), @GENDER char(1), @PULPIT varchar(15), @RESULT varchar(300)
set @ID = RTRIM((select TEACHER from DELETED))
set @NAME = (select TEACHER_NAME from DELETED)
set @GENDER = (select GENDER from DELETED)
set @PULPIT = RTRIM((select PULPIT from DELETED))
set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
insert into TR_AUDIT values ('DEL', 'TR_TEACHER_DEL_B', @RESULT)
go


create trigger TR_TEACHER_DEL_C on TEACHER after DELETE as
declare @ID varchar(10), @NAME varchar(50), @GENDER char(1), @PULPIT varchar(15), @RESULT varchar(300)
set @ID = RTRIM((select TEACHER from DELETED))
set @NAME = (select TEACHER_NAME from DELETED)
set @GENDER = (select GENDER from DELETED)
set @PULPIT = RTRIM((select PULPIT from DELETED))
set @RESULT = @ID + ' ' + @NAME + ' ' + @GENDER + ' ' + @PULPIT
insert into TR_AUDIT values ('DEL', 'TR_TEACHER_DEL_C', @RESULT)
go


select t.name, e.type_desc 
from sys.triggers  t join  sys.trigger_events e  
on t.object_id = e.object_id  
where OBJECT_NAME(t.parent_id) = 'TEACHER' and e.type_desc = 'DELETE';  

exec sp_settriggerorder @triggername = 'TR_TEACHER_DEL', @order = 'LAST', @stmttype = 'DELETE'
exec sp_settriggerorder @triggername = 'TR_TEACHER_DEL_C', @order = 'FIRST', @stmttype = 'DELETE'


insert into TEACHER values ('���', '������ ��� �������', '�', '����')
delete from TEACHER where TEACHER = '���'
select * from TR_AUDIT
go  



-- 8. instead of ������� - ��������� �������
create trigger TR_FACULTY_DELETE on FACULTY instead of DELETE
as
raiserror('�������� ���������', 10,1)
go
select * from FACULTY
delete from FACULTY where FACULTY = '����'
go



--9. db �������
create trigger TR_UNIVERSITY on database for CREATE_TABLE, DROP_TABLE, ALTER_TABLE as
declare @t1 varchar(50), @t2 varchar(50), @t3 varchar(50) 
set @t1 = EVENTDATA().value('(/EVENT_INSTANCE/EventType)[1]','varchar(50)')
set @t2 = EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]','varchar(50)')
set @t3 = EVENTDATA().value('(/EVENT_INSTANCE/ObjectType)[1]','varchar(50)')

print '��� �������: ' + @t1;
print '��� �������: ' + @t2;
print '��� �������: ' + @t3;

raiserror('�������� �������� � �������� ������ ���������', 10, 1)
return

create table NewTable
(
id int primary key,
val varchar(300)
)
select * from NewTable
drop table NewTable
go


-- 11. ������!
--create database test;
use test
create table TR_AUDIT
(
ID int primary key identity, 
STMT varchar(20) check (STMT in ('INS', 'DEL', 'UPD')),
TRNAME varchar(50),
CC varchar(300)
)
create table WEATHER
(
CITY varchar(30),
STARTDATE DATETIME,
ENDDATE DATETIME,
TEMP NUMERIC
)
go
create trigger TR_WEATHER ON WEATHER FOR INSERT, UPDATE as
declare @CITY varchar(30), @STARTDATE DATETIME, @ENDDATE DATETIME, @TEMP NUMERIC, @ERROR varchar(300)

set @CITY = (select CITY from inserted)
set @STARTDATE = (select STARTDATE from inserted)
set @ENDDATE = (select ENDDATE from inserted)
set @TEMP = (select TEMP from inserted)

if exists (select * from WEATHER 
where (STARTDATE >= @STARTDATE AND STARTDATE <= @ENDDATE) OR (ENDDATE >= @STARTDATE AND ENDDATE <= @ENDDATE) 
except select * from INSERTED)
begin
	SET @ERROR = '�� ������� �������� ' + @CITY + ' ' + cast(@STARTDATE as varchar(20)) + ' ' + 
	cast(@ENDDATE as varchar(20)) + ' ' + cast(@TEMP as varchar(10)) + ' - ������ �� ��������� ���������� ������� ��� ����������' 
	raiserror(@ERROR, 10, 1)
end
return
go

select * from WEATHER

delete from WEATHER

insert into WEATHER values
('�����', '20210101 12:00', '20210101 23:59', 13)
insert into WEATHER values
('�����', '20210101 00:00', '20210101 11:59', 7)
insert into WEATHER values
('�����', '20210101 00:00', '20210101 02:00', 7)
go




 drop trigger TR_FACULTY_DELETE
 drop trigger TR_TEACHER
 drop trigger TR_TEACHER_DEL
 drop trigger TR_TEACHER_DEL_B
 drop trigger TR_TEACHER_DEL_C
 drop trigger TR_TEACHER_INS
 drop trigger TR_TEACHER_UPD
 drop trigger TR_UNIVERSITY
 drop trigger TR_WEATHER
 go