set nocount on;
use Halaleenko_laba4 

--1. результирующий набор
go
create procedure PSUBJECT as
begin
	declare @count int = (select count(*) from SUBJECT)
	select SUBJECT, SUBJECT_NAME, PULPIT from SUBJECT
	return @count
end
go

declare @count int
exec @count = PSUBJECT
print 'кол-во строк: ' +cast(@count as varchar(100))

--drop procedure PSUBJECT

--2. через object explorer
GO --@p - код кафедры, @c - кол-во строк

ALTER procedure [dbo].[PSUBJECT] @p varchar(20) = null,  @c int output as
begin
	declare @count int = (select count(*) from SUBJECT)
	set @c  = (select count(*) from SUBJECT where PULPIT = @p)
	select SUBJECT, SUBJECT_NAME, PULPIT from SUBJECT where PULPIT = @p
	return @count
end
GO

declare @crez int, @count int
exec @count = PSUBJECT @p = 'ИСиТ', @c = @crez output
print @count
print @crez


--3. без выходного параметра
go
ALTER procedure [dbo].[PSUBJECT] @p varchar(20) = null as
begin
	declare @count int = (select count(*) from SUBJECT)
	select SUBJECT, SUBJECT_NAME, PULPIT from SUBJECT where PULPIT = @p
	return @count
end
GO

create table #SUBJECT
(
	SUBJECT char(10) primary key,
	SUBJECT_NAME varchar(100),
	PULPIT char(20)
)

insert #SUBJECT exec PSUBJECT @p = 'ИСиТ'
select * from #SUBJECT

drop table #SUBJECT
go


--4. try catch
create procedure PAUDITORIUM_INSERT @a char(20), @n varchar(50), @c int = 0, @t char(10) 
as --auditorium, auditorium name, auditorium capacity, auditorium type
begin 
	begin try
		insert into AUDITORIUM values
		(@a, @t, @c, @n)
		return 1
	end try
	begin catch
		print cast (error_number() as varchar(6)) + ' ' + cast (error_severity() as varchar(6)) + ' ' + error_message() 
		return -1
	end catch

end

--delete from AUDITORIUM where AUDITORIUM = ('206-1')

go
declare @rez int
exec @rez = PAUDITORIUM_INSERT @a = '202-1', @t = 'ЛК', @c = 15, @n = '202-1' 
print @rez
if @rez = 1
	select * from AUDITORIUM



--5. вывод дисциплин и raiserror
create procedure PPULPIT_SUBJECTS @p char(20) as
begin
	if (@p not in (select PULPIT from PULPIT))
		begin
			raiserror('Ошибка в параметрах', 11, 1)
			return 0
		end
	declare @pulpitName nvarchar(50) = @p
	declare @i int = 0
	declare @subjectName nvarchar(15), @subjectline nvarchar(150) = '', @subjectPulpit nvarchar(50)
	declare subjects cursor local dynamic for
		SELECT SUBJECT.SUBJECT, SUBJECT.PULPIT from SUBJECT
	
		open subjects

			fetch from subjects into @subjectName, @subjectPulpit
			if (@subjectPulpit = @pulpitName)
				set @subjectline = trim(@subjectName) + ', ' + @subjectline
					
			while @@FETCH_STATUS = 0
				begin
					fetch from subjects into @subjectName, @subjectPulpit
					if (@subjectPulpit = @pulpitName)
					begin
						set @subjectline = trim(@subjectName) + ', ' + @subjectline
						set @i = @i + 1
					end
				end

		close subjects
		if len(@subjectline) > 0
			set @subjectline = left(@subjectline, len(@subjectline)-1)
		else
			set @subjectline = 'нет'
		print char(9) + char(9) + 'Дисциплины: ' + @subjectline
	
	return @i
end
go

declare @count int
exec @count = PPULPIT_SUBJECTS @p = 'ИСиТ'

print @count

drop procedure PPULPIT_SUBJECTS
go


-- 6. две строки добавить
go
create procedure PAUDITORIUM_INSERT_TYPE @a_ char(20), @n_ varchar(50), @c_ int = 0, @t_ char(10), @tn_ varchar(50) as
begin
declare @err nvarchar(50) = 'Ошибка: '
declare @rez int
	set transaction isolation level serializable
	-- предотвращает вставку новых строк другой транзакцией до тех пор, пока первая транзакция не будет подтверждена или отменена.
		begin try
			insert into AUDITORIUM_TYPE values (@t_, @tn_)
			exec @rez = PAUDITORIUM_INSERT @a = @a_, @n = @n_, @c = @c_, @t = @t_
				if (@rez = -1)
					begin
						return -1
					end
		end try
		begin catch
			set @err = @err + error_message()
			raiserror(@err, 11, 1)
			return -1
		end catch
	return 1
end
go
declare @rez int
exec @rez = PAUDITORIUM_INSERT_TYPE @a_ = '208-1', @n_ = '208-1', @c_ = 15, @t_ = 'AUT2', @tn_ = 'AUDITORIUM TYPE 2' 
print @rez
if @rez = 1
	select * from AUDITORIUM
	select * from AUDITORIUM_TYPE


	delete from AUDITORIUM where AUDITORIUM_TYPE like ('AUT2')
	delete from AUDITORIUM_TYPE where AUDITORIUM_TYPE like ('AUT2');
drop procedure PAUDITORIUM_INSERT_TYPE
go



--7. mybase 
use Халалеенко_продажи
set nocount on
go

create procedure PRo @p nchar(20), @c nchar(30) output as
	set @c = (select покупатель from покупатель where адрес = @p)
go

declare @var nchar(30), @cr nchar(20)
exec @var = PRo @p = 'маяк', @c = @cr output
print cast(@cr as varchar(20))

drop procedure PRo
go

--8. отчет
use Halaleenko_laba4
set nocount on

go
create procedure PFACULTY_REPORT @f char(10) = null, @p char(10) = null as
begin
	declare @faculty nvarchar(10), @pulpitcount int, @i int = 0
	declare @pulpitName nvarchar(50), @teacherCount int, @j int = 0
	declare @subjectName nvarchar(15), @subjectline nvarchar(150) = '', @subjectPulpit nvarchar(50)
	declare facultyCount cursor local dynamic for
		select FACULTY.FACULTY, count(*) from FACULTY inner join PULPIT on FACULTY.FACULTY = PULPIT.FACULTY
		group by FACULTY.FACULTY order by FACULTY.FACULTY asc
	declare pulpits cursor local dynamic for
		select PULPIT.PULPIT, count(*) from PULPIT left outer join TEACHER on PULPIT.PULPIT = TEACHER.PULPIT
		group by FACULTY, PULPIT.PULPIT order by FACULTY asc
	declare @rezcount int = 0

	open facultyCount
	open pulpits


	if (@f is null AND @p is null)
	begin
	
	
		fetch from facultyCount into @faculty, @pulpitcount
		print 'Факультет: ' + @faculty
		while @@FETCH_STATUS = 0
		begin
			set @i = 0
		
			while @i < @pulpitcount
				begin
					set @subjectline = ''
					fetch from pulpits into @pulpitName,@teacherCount
					print char(9) + 'Кафедра: ' + @pulpitName
					print char(9) + char(9) + 'Количество преподавателей: ' + cast(@teacherCount as nvarchar(10))
					exec PPULPIT_SUBJECTS @p = @pulpitName
					set @i = @i + 1
				end 



			fetch from facultyCount into @faculty, @pulpitcount
			if (@@FETCH_STATUS = 0) print 'Факультет: ' + @faculty
			set @rezcount = @rezcount + 1
		end		

		return @rezcount	

	end
	if (@f is not null AND @p is null)
	begin
		if (@f not in (select FACULTY from FACULTY))
		begin
			raiserror('Факультет не найден', 11, 1)
			return -1
		end
		fetch from facultyCount into @faculty, @pulpitcount
		if (@faculty = @f)
		begin
			begin
			set @i = 0
		
			while @i < @pulpitcount
				begin
					set @subjectline = ''
					fetch from pulpits into @pulpitName,@teacherCount
					print char(9) + 'Кафедра: ' + @pulpitName
					print char(9) + char(9) + 'Количество преподавателей: ' + cast(@teacherCount as nvarchar(10))
					exec PPULPIT_SUBJECTS @p = @pulpitName
					set @i = @i + 1
				end

			fetch from facultyCount into @faculty, @pulpitcount
			if (@@FETCH_STATUS = 0) print 'Факультет: ' + @faculty
			return @pulpitCount
			
		end
	end
		while (@@FETCH_STATUS = 0)
		begin
			fetch from facultyCount into @faculty, @pulpitcount
			if (@faculty = @f)
			begin
			begin
			set @i = 0
		
			while @i < @pulpitcount
				begin
					set @subjectline = ''
					fetch from pulpits into @pulpitName,@teacherCount
					print char(9) + 'Кафедра: ' + @pulpitName
					print char(9) + char(9) + 'Количество преподавателей: ' + cast(@teacherCount as nvarchar(10))
					exec PPULPIT_SUBJECTS @p = @pulpitName
					set @i = @i + 1
				end 

			fetch from facultyCount into @faculty, @pulpitcount
			if (@@FETCH_STATUS = 0) print 'Факультет: ' + @faculty
			return @pulpitCount
		end
		end
		end		

	end

	if(@p is not null)
	begin
		if (@p not in (select PULPIT from PULPIT))
		begin
			raiserror('Кафедра не найдена', 11, 1)
			return -1
		end
		fetch from facultyCount into @faculty, @pulpitcount
		if (@p in (select PULPIT from FACULTY inner join PULPIT on PULPIT.FACULTY = FACULTY.FACULTY where FACULTY.FACULTY = @faculty))
		begin
			begin
			set @i = 0
		
			while @i < @pulpitcount
				begin
					set @subjectline = ''
					fetch from pulpits into @pulpitName,@teacherCount
					if (@pulpitName = @p)
					begin
						print char(9) + 'Кафедра: ' + @pulpitName
						print char(9) + char(9) + 'Количество преподавателей: ' + cast(@teacherCount as nvarchar(10))
						exec @rezcount = PPULPIT_SUBJECTS @p = @pulpitName
						return @rezcount
					end
				end


			fetch from facultyCount into @faculty, @pulpitcount
			if (@@FETCH_STATUS = 0) print 'Факультет: ' + @faculty
			return @pulpitCount
			
		end
		end
		while (@@FETCH_STATUS = 0)
		begin
			fetch from facultyCount into @faculty, @pulpitcount
			if (@p in (select PULPIT from FACULTY inner join PULPIT on PULPIT.FACULTY = FACULTY.FACULTY where FACULTY.FACULTY = @faculty))
			begin
				begin
				set @i = 0
		
				while @i < @pulpitcount
					begin
						set @subjectline = ''
						fetch from pulpits into @pulpitName,@teacherCount
						if (@pulpitName = @p)
						begin
							print char(9) + 'Кафедра: ' + @pulpitName
							print char(9) + char(9) + 'Количество преподавателей: ' + cast(@teacherCount as nvarchar(10))
							exec @rezcount = PPULPIT_SUBJECTS @p = @pulpitName
							return @rezcount
						end
				end 


			fetch from facultyCount into @faculty, @pulpitcount
			if (@@FETCH_STATUS = 0) print 'Факультет: ' + @faculty
			return @pulpitCount
			
		end
		end
		end		

	end
	
	close facultyCount
	close pulpits
end
go
declare @rez int
exec @rez = PFACULTY_REPORT 
print '----------- ' + cast (@rez as nvarchar(10)) 
go
declare @rez int
exec @rez = PFACULTY_REPORT @f = 'ХТиТ'
print '----------- ' + cast (@rez as nvarchar(10)) 
go
go
declare @rez int
exec @rez = PFACULTY_REPORT @p = 'ИСиТ'
print '----------- ' + cast (@rez as nvarchar(10)) 
go

-------------
go
drop procedure PSUBJECT
drop procedure PPULPIT_SUBJECTS
drop procedure PAUDITORIUM_INSERT_TYPE
drop procedure PFACULTY_REPORT