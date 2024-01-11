use Halaleenko_laba4; 

--1. функция подсчета студентов по факультету
go
create function CountStudents(@faculty varchar(20) = null) returns int 
as
begin
	declare @count int = 0
	set @count = (select count(*) 
				from Student inner join Groups on Student.IDGROUP = Groups.IDGROUP
				where Groups.FACULTY = @faculty)
	return @count
end
go

print dbo.CountStudents('ХТИТ')
go

alter function CountStudents(@faculty varchar(20) = null, @profession varchar(20) = null) returns int
as
begin
	declare @count int = 0
	set @count = (select count(*) 
				from Student inner join Groups on Student.IDGROUP = Groups.IDGROUP
				where Groups.FACULTY = @faculty AND Groups.PROFESSION = @profession)
	return @count
end
go

print dbo.CountStudents('ХТИТ','1-36 07 01')
go

drop function CountStudents;
go


--2. скалярная функция + отчет
go
create function PulpitSubjects(@pulpit varchar(20)) returns varchar(300) 
as
begin
	declare @subjects varchar(300) = 'Дисциплины: ',
			@subject varchar(50)
	declare SubjectsCursor cursor local for
		select SUBJECT 
		from SUBJECT 
		where SUBJECT.PULPIT = @pulpit

	open SubjectsCursor
		fetch SubjectsCursor into @subject
		set @subjects = @subjects + RTRIM(@subject)
		if (@@FETCH_STATUS !=0)
			Set @subjects = 'Дисциплины: нет'
		while @@FETCH_STATUS = 0
		begin
			fetch SubjectsCursor into @subject
			set @subjects = @subjects + ', ' + RTRIM(@subject)
		end
	close SubjectsCursor

	return @subjects
end
go

select PULPIT, dbo.PulpitSubjects(PULPIT) from PULPIT
go

drop function PulpitSubjects;
go

--3. табличная функция
go
create function FacultyPulpit (@faculty varchar(30) = null, @pulpit varchar(30) = null) 
returns @result table 
				(
					faculty char(10),
					pulpit char(20)
				)
as 
begin
	if(@faculty is null)
	begin
		if (@pulpit is null)
		begin
			-- оба null
			insert into @result
			select FACULTY.FACULTY, PULPIT.PULPIT
			from FACULTY left outer join PULPIT on FACULTY.FACULTY = PULPIT.FACULTY
			return
		end
		else
		begin
			-- faculty null
			insert into @result
			select FACULTY.FACULTY, PULPIT.PULPIT
			from FACULTY left outer join PULPIT on FACULTY.FACULTY = PULPIT.FACULTY
			where PULPIT.PULPIT = @pulpit
			return
		end
	end
	else 
	begin
		if (@pulpit is null)
		begin
			-- pulpit null
			insert into @result
			select FACULTY.FACULTY, PULPIT.PULPIT
			from FACULTY left outer join PULPIT on FACULTY.FACULTY = PULPIT.FACULTY
			where FACULTY.FACULTY = @faculty
			return
		end
		else
		begin
			-- оба не null
			insert into @result
			select FACULTY.FACULTY, PULPIT.PULPIT
			from FACULTY left outer join PULPIT on FACULTY.FACULTY = PULPIT.FACULTY
			where FACULTY.FACULTY = @faculty AND PULPIT.PULPIT = @pulpit
			return
		end
	end
return
end
go

select * from FacultyPulpit(null, null)
select * from FacultyPulpit('ХТИТ', null)
select * from FacultyPulpit(null, 'ЛВ')
select * from FacultyPulpit('ЛХФ', 'ЛВ')

drop function FacultyPulpit
go

--4. код кафедры => количество преподователей

create function TeacherCount(@pulpit char(20)) returns int
as
begin
	declare @teacherCount int = 0

	if (@pulpit is null)
		set @teacherCount = 
		(select count(*) 
		from TEACHER)
	else
		set @teacherCount = 
		(select count(*) 
		from TEACHER where PULPIT = @pulpit)

	return @teacherCount
end
go

select dbo.TeacherCount(null)
select dbo.TeacherCount('ИСиТ')

select PULPIT, dbo.TeacherCount(PULPIT)
from PULPIT

drop function TeacherCount;
go


--5. xmybase
use Халалеенко_продажи
set nocount on
go

create function CountDop(@count int = null) returns int 
as
begin
	declare @id int
	set @id = (select count(*) 
				from доп_информация 
				where количество_ячеек = @count)
	return @id
end
go


print dbo.CountDop('5')

drop function CountDop
go




-- 6. многооператорная функция 
go
create function StudentCount(@faculty varchar(50)) returns int
as
begin
	 declare @studentCount int  = 0
	 set @studentCount = 
		(select count(*)
		from STUDENT inner join GROUPS on STUDENT.IDGROUP = GROUPS.IDGROUP
					 inner join FACULTY on GROUPS.FACULTY = FACULTY.FACULTY
		where FACULTY.FACULTY = @faculty)
	return @studentCount
end
go

create function PulpitCount(@faculty varchar(50)) returns int
as
begin
	 declare @pulpitCount int = 0
	 set @pulpitCount = 
		(select count(*)
		from PULPIT
		where PULPIT.FACULTY = @faculty)
	return @pulpitCount
end
go

create function ProfessionCount(@faculty varchar(50)) returns int
as
begin
	 declare @professionCount int = 0
	 set @professionCount = 
		(select count(*)
		from PROFESSION
		where PROFESSION.FACULTY = @faculty)
	return @professionCount
end
go

create function GroupCount(@faculty varchar(50)) returns int
as
begin
	 declare @groupCount int = 0
	 set @groupCount = 
		(select count(*)
		from GROUPS
		where GROUPS.FACULTY = @faculty)
	return @groupCount
end
go

create function FacultyReport(@studentCount int) 
returns @result table 
		(
		Faculty varchar(50),
		PulpitCount int, 
		GroupCount int, 
		ProfessionCount int
		)
as
begin
	declare FacultyCursor cursor local for
		select FACULTY
		from FACULTY
		where dbo.StudentCount(FACULTY) > @studentCount
	declare @faculty varchar(50)
	open FacultyCursor

		fetch FacultyCursor into @faculty
		while @@FETCH_STATUS = 0
		begin
			insert into @result values
			(@faculty, dbo.PulpitCount(@faculty), dbo.GroupCount(@faculty), dbo.ProfessionCount(@faculty))

			fetch FacultyCursor into @faculty
		end

	close FacultyCursor
	return
end
go


select * from dbo.FacultyReport(24) --кол-во студентов с IDGROUP 9-13
go


-- 7.
create procedure PFACULTY_REPORT2 @faculty char(10) = null, @pulpit char(10) = null as
begin
	declare facultyCursor cursor local for
		select faculty from FACULTY
	declare pulpitCursor cursor local for 
		select pulpit from PULPIT
	declare @result int = 0
	declare @currFaculty varchar(30), @currPulpit varchar(30), @subjectString varchar(300)

	open facultyCursor	

	if(@faculty is null)
	begin
		if (@pulpit is null)
		begin
			-- оба null
			fetch facultyCursor into @currFaculty
			while @@FETCH_STATUS = 0
			begin
				print 'Факультет: ' + @currFaculty
				open pulpitCursor 
				fetch pulpitCursor into @currPulpit
				while @@FETCH_STATUS = 0
				begin
					if (exists (select * from PULPIT where FACULTY = @currFaculty AND PULPIT = @currPulpit)) 
					begin
						print char(9) + 'Кафедра ' + @currPulpit
						print char(9) +  char(9) + 'Количество учителей: ' +cast(dbo.TeacherCount(@currPulpit) as varchar(5))
						print char(9) +  char(9) + cast(dbo.PulpitSubjects(@currPulpit) as varchar(300))
					end
					
					fetch pulpitCursor into @currPulpit
				end
				close pulpitCursor
				fetch facultyCursor into @currFaculty
			end
			set @result = dbo.PulpitCount(@faculty)
		end
		else
		begin
			-- faculty null
			fetch facultyCursor into @currFaculty
			open pulpitCursor
			while @@FETCH_STATUS = 0
			begin		
				fetch pulpitCursor into @currPulpit
				while @@FETCH_STATUS = 0
				begin
					if(@currPulpit = @pulpit)
					begin
						print 'Факультет: ' + @currFaculty
						print char(9) + 'Кафедра ' + @currPulpit
						print char(9) +  char(9) + 'Количество учителей: ' +cast(dbo.TeacherCount(@currPulpit) as varchar(5))
						print char(9) +  char(9) + cast(dbo.PulpitSubjects(@currPulpit) as varchar(300))
						
					end
					fetch pulpitCursor into @currPulpit
				end
				set @result = @result + dbo.PulpitCount(@faculty)
				fetch facultyCursor into @currFaculty
			end
			close pulpitCursor
		end
	end
	else 
	begin
		if (@pulpit is null)
		begin
			-- pulpit null
			fetch facultyCursor into @currFaculty
			open pulpitCursor
			while @@FETCH_STATUS = 0
			begin
				if(@currFaculty = @faculty)
				begin
					print 'Факультет: ' + @currFaculty
					fetch pulpitCursor into @currPulpit
					while @@FETCH_STATUS = 0
					begin
						if (exists (select * from PULPIT where FACULTY = @currFaculty AND PULPIT = @currPulpit)) 
						begin
							print char(9) + 'Кафедра ' + @currPulpit
							print char(9) +  char(9) + 'Количество учителей: ' +cast(dbo.TeacherCount(@currPulpit) as varchar(5))
							print char(9) +  char(9) + cast(dbo.PulpitSubjects(@currPulpit) as varchar(300))
						end
						fetch pulpitCursor into @currPulpit
					end
				end
				fetch facultyCursor into @currFaculty

			end
			set @result = dbo.PulpitCount(@faculty)
			close pulpitCursor
		end
		else
		begin
			-- оба не null
			fetch facultyCursor into @currFaculty
			open pulpitCursor
			while @@FETCH_STATUS = 0
			begin		
					fetch pulpitCursor into @currPulpit
					while @@FETCH_STATUS = 0
					begin
						if(@currPulpit = @pulpit)
						begin
							print 'Факультет: ' + @currFaculty
							print char(9) + 'Кафедра ' + @currPulpit
							print char(9) +  char(9) + 'Количество учителей: ' +cast(dbo.TeacherCount(@currPulpit) as varchar(5))
							print char(9) +  char(9) + cast(dbo.PulpitSubjects(@currPulpit) as varchar(300))
							
						end
						fetch pulpitCursor into @currPulpit
					end
					fetch facultyCursor into @currFaculty
			end
			set @result = dbo.PulpitCount(@faculty)
			close pulpitCursor

		end
	end

	close facultyCursor
	return @result
end


drop procedure PFACULTY_REPORT2
go


declare @rez int
exec @rez = PFACULTY_REPORT2 
print '----------- ' + cast (@rez as nvarchar(10)) 
go
declare @rez int
exec @rez = PFACULTY_REPORT2 @faculty = 'ХТиТ'
print '----------- ' + cast (@rez as nvarchar(10)) 
go
go
declare @rez int
exec @rez = PFACULTY_REPORT2 @pulpit = 'ИСиТ'
print '----------- ' + cast (@rez as nvarchar(10)) 
go