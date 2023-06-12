USE Halaleenko_laba4;
SET NOCOUNT ON;
GO
--------------------------------1---------------------------------------
DECLARE Discipline CURSOR
				for SELECT SUBJECT.SUBJECT 
					FROM SUBJECT 
					WHERE SUBJECT.PULPIT IN('ИСиТ')
GO
DECLARE @discip char(20), @d char(300) =' ';
OPEN Discipline;
FETCH Discipline into @discip;
print 'Дисциплины с кафедры ИСиТ';
while @@fetch_status = 0
	begin
		set @d = rtrim(@discip) + ',' + @d;
		FETCH Discipline into @discip;
	end;
print @d;
CLOSE Discipline;
DEALLOCATE Discipline
--------------------------------2---------------------------------------
DECLARE Student CURSOR LOCAL
				for SELECT STUDENT.NAME, PROGRESS.NOTE
					FROM PROGRESS INNER JOIN STUDENT
					ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
					WHERE PROGRESS.SUBJECT IN('КГ')
PRINT '<---Отметки студентов за экзамен по КГ--->' 
DECLARE @stud char(50), @n int;
	OPEN Student;
	FETCH Student into @stud, @n;
	print '1.'+ @stud + cast(@n as varchar(3));
	go
	--КУРСОР УДАЛЯЕТСЯ
DECLARE @stud char(50), @n int;
	FETCH Student into @stud, @n;
	print '2.'+ @stud + cast(@n as varchar(3));
	go
--------------------------------------------------
DECLARE Student CURSOR GLOBAL
				for SELECT STUDENT.NAME, PROGRESS.NOTE
					FROM PROGRESS Inner Join STUDENT
					ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
					WHERE PROGRESS.SUBJECT IN('КГ')
 DECLARE @stud char(50), @n int;
	OPEN Student;
	FETCH Student into @stud, @n;
	print '1.'+ @stud + cast(@n as varchar(3));
	go

DECLARE @stud char(50), @n int;
	FETCH Student into @stud, @n;
	print '2.'+ @stud + cast(@n as varchar(3));
	go
	CLOSE Student;
	DEALLOCATE Student;
	go
--------------------------------3---------------------------------------
DECLARE @sid char(25), @sdate char(25), @spr char(3)
DECLARE StudPr CURSOR LOCAL STATIC
				for SELECT PROGRESS.IDSTUDENT, PROGRESS.PDATE, PROGRESS.NOTE
					FROM PROGRESS
					WHERE PROGRESS.SUBJECT IN('КГ')
	OPEN StudPr;
	print 'Количество строк: ' + cast(@@CURSOR_ROWS as varchar(5));
	UPDATE PROGRESS set NOTE = 6 where IDSTUDENT = 1003
	DELETE PROGRESS where IDSTUDENT = 1003
	INSERT PROGRESS (SUBJECT,  PDATE, NOTE)
			values('КГ',  cast('2013-12-01' as date), 7);
	FETCH StudPr into @sid, @sdate, @spr;
	while @@FETCH_STATUS = 0
	begin
		print @sid + '' + @sdate + '' + @spr;
		fetch StudPr into @sid, @sdate, @spr;
	end;
	CLOSE StudPr;
	DEALLOCATE StudPr
go
---------------------------------------------------------------
DECLARE @sid char(25), @sdate char(25), @spr char(3)
DECLARE StudPr CURSOR LOCAL DYNAMIC
				for SELECT PROGRESS.IDSTUDENT, PROGRESS.PDATE, PROGRESS.NOTE
					FROM PROGRESS
					WHERE PROGRESS.SUBJECT IN('КГ')
	OPEN StudPr;
	print 'Количество строк: ' + cast(@@CURSOR_ROWS as varchar(5));
	UPDATE PROGRESS set NOTE = 5 where IDSTUDENT = 1018
	DELETE PROGRESS where IDSTUDENT = 1016
	INSERT PROGRESS (SUBJECT, IDSTUDENT, PDATE, NOTE)
			values('КГ', '1007', cast('2013-12-01' as date), 5);
	FETCH StudPr into @sid, @sdate, @spr;
	while @@FETCH_STATUS = 0
	begin
		print @sid + '' + @sdate + '' + @spr;
		fetch StudPr into @sid, @sdate, @spr;
	end;
	CLOSE StudPr;
	DEALLOCATE StudPr
go

--------------------------------4---------------------------------------

DECLARE @s char(10), @p char(10);
DECLARE Dis CURSOR LOCAL DYNAMIC SCROLL
				FOR  SELECT ROW_NUMBER()OVER (ORDER BY SUBJECT), PULPIT 
				FROM SUBJECT

	OPEN Dis;
	FETCH Dis INTO @s, @p;
	WHILE @@FETCH_STATUS = 0
	begin
		PRINT @s+' '+@p
		FETCH Dis INTO @s, @p
	end
	
	PRINT '<---last--->'
	FETCH LAST FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---first--->'
	FETCH FIRST FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---absolute 10--->'
	FETCH ABSOLUTE 10 FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---relative 5--->'
	FETCH RELATIVE 5 FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---relative -5--->'
	FETCH RELATIVE -5 FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---absolute -10--->'
	FETCH ABSOLUTE -10 FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---next--->'
	FETCH NEXT FROM Dis into @s, @p
	PRINT @s+' '+@p

	PRINT '<---prior--->'
	FETCH PRIOR FROM Dis into @s, @p
	PRINT @s+' '+@p
	CLOSE Dis
	go

--------------------------------5---------------------------------------
SELECT STUDENT.IDSTUDENT, STUDENT.NAME, PROGRESS.NOTE								--до изменения отметки на 1
		FROM STUDENT
		Inner Join PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
		WHERE STUDENT.IDSTUDENT IN ('1001')


DECLARE @n int, @name nvarchar(30), @mark int
DECLARE Stud CURSOR LOCAL DYNAMIC
	for SELECT STUDENT.IDSTUDENT, STUDENT.NAME, PROGRESS.NOTE
		FROM STUDENT
		Inner Join PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
		WHERE STUDENT.IDSTUDENT IN ('1001') FOR UPDATE

OPEN Stud;
FETCH Stud into @n, @name, @mark;
PRINT cast(@n as nvarchar(10)) + ' ' + @name + ' ' + cast(@mark as nvarchar(2))
UPDATE PROGRESS SET NOTE = NOTE + 1 WHERE CURRENT OF Stud
CLOSE Stud;

SELECT STUDENT.IDSTUDENT, STUDENT.NAME, PROGRESS.NOTE 								--после изменения отметки на 1
		FROM STUDENT
		Inner Join PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
		WHERE STUDENT.IDSTUDENT IN ('1001')
--------------------------------6---------------------------------------
GO
SELECT  STUDENT.NAME, PROGRESS.NOTE 
	FROM STUDENT 
	Inner Join PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
	WHERE PROGRESS.NOTE > 4
	ORDER BY PROGRESS.NOTE

	insert into PROGRESS
	values ('оаип', '1024', '2014-12-09', 3);

	delete from PROGRESS where PROGRESS.IDSTUDENT in ('1024');

DECLARE @name nvarchar(30), @mark int
DECLARE Badmark CURSOR LOCAL DYNAMIC
	for SELECT  STUDENT.NAME, PROGRESS.NOTE 
		FROM STUDENT 
		Inner Join PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
		WHERE PROGRESS.NOTE < 4

OPEN Badmark;
FETCH Badmark into @name, @mark
PRINT @name + ' ' + cast(@mark as nvarchar(2))
DELETE PROGRESS WHERE CURRENT OF Badmark
CLOSE Badmark

SELECT  STUDENT.NAME, PROGRESS.NOTE 
	FROM STUDENT 
	Inner Join PROGRESS ON PROGRESS.IDSTUDENT = STUDENT.IDSTUDENT
	WHERE PROGRESS.NOTE < 4