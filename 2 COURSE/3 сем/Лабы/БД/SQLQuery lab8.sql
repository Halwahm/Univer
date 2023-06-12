USE Halaleenko_laba4
--1. �������� ����������, �������� ��������
DECLARE 
	@xchar char = 'a', 
	@xvarchar varchar(4) = 'aaaa',
	@xdatetime date = '2021-02-01',
	@d datetime,
	@xtime time = '09:50',
	@xint int = 1,
	@xsmallint smallint = 1,
	@xtinyint tinyint = 1,
	@xnumeric numeric(12,5) = 12.5

SELECT @d = PDATE FROM PROGRESS;
SELECT @d datetime

SELECT @xchar [xchar], @xvarchar [xvarchar]
SET @xvarchar = '����'
SELECT @xvarchar [xvarchar], @xint [xint]

PRINT 'Time = ' + convert(varchar, @xdatetime)

--2. ������ �� ����������� ���������
DECLARE 
	@capacity numeric(8,3) = (SELECT cast(sum(AUDITORIUM_CAPACITY) as numeric(8,3)) from AUDITORIUM),
	@total int,
	@avgcapacity numeric(8,3),
	@totallessavg int,
	@procent numeric(8,3)
if @capacity < 200
begin
	SET @total = (SELECT cast(count(*) as numeric(8,3)) from AUDITORIUM);
	SET @avgcapacity = (SELECT avg(AUDITORIUM_CAPACITY) from AUDITORIUM);
	SET @totallessavg = (SELECT cast(count(*) as numeric(8,3)) from AUDITORIUM where AUDITORIUM_CAPACITY < @avgcapacity);
	SET @procent = @totallessavg / @total;
	SELECT @capacity '����� �����������',
	@total '����� ���������',
	@avgcapacity '������� �����������',
	@totallessavg '��������� � ������������ ���� �������',
	@procent '������� ����� ���������'
end
else select @capacity '����� ����������� ���������';

--3. ���������� ���������� --����� ������������ �����
PRINT '����� ������������ �����: ' + cast(@@rowcount as varchar) 
PRINT '������ SQL Server: ' + cast(@@version as varchar)
PRINT '��������� ������������� ��������: ' + cast(@@spid as varchar)
PRINT '��� ��������� ������: ' + cast(@@error as varchar)
PRINT '��� �������: ' + cast(@@servername as varchar)
PRINT '������� ����������� ����������: ' + cast(@@trancount as varchar)
PRINT '�������� ���������� ���������� ����� ��������������� ������: ' + cast(@@fetch_status as varchar)
PRINT '������� ����������� ������� ���������: ' + cast(@@nestlevel as varchar)

--4.1 ����������
DECLARE 
@t float = 12.1, 
@x float = 2.5, 
@z float 
if @t > @x SET @z = sin(@t)*sin(@t)
else if @t < @x SET @z = 4*(@t + @x)
else if @t = @x SET @z = 1 - exp(@x-2)
SELECT @z 'z'

go --4.2 ����������� ���
create function dbo.ShortenName (@nameFull nvarchar(50))  
returns nvarchar(50)   
as   
begin
    DECLARE @nameShort nvarchar(50) = '',
			@symbol nchar(1),
			@i int = 1,
			@wordCount int = 0,
			@isFirstLetter int = 0;
	while @i < len(@nameFull)
		begin
			SET @symbol = substring(@nameFull, @i ,1);
			if (@symbol = ' ')
				begin
					SELECT @wordCount = @wordCount + 1, 
					@isFirstLetter = 1, 
					@nameShort = @nameShort + @symbol
				end
			else if (@isFirstLetter = 1)
				begin
					SELECT @isFirstLetter = 0, 
					@nameShort = @nameShort + @symbol
				end
			else if (@wordCount = 0)
				begin
					SELECT @nameShort = @nameShort + @symbol
				end			
			SET @i = @i + 1
		end   
    return @nameShort; 
end
go

DECLARE @fullName nvarchar(50) = '���������� ������ ����������',
		@shortName nvarchar(50);
SET @shortName = dbo.ShortenName(@fullName)
PRINT @shortName

--4.3 �� � ��������� ������
SELECT STUDENT.NAME, STUDENT.BDAY, (datediff(YY, STUDENT.BDAY, sysdatetime())) as '�������'
from STUDENT where month(STUDENT.BDAY) = month(sysdatetime()) + 1 

--4.4 ����� ��� ������
SELECT day(GETDATE()) as '���� ������' from PROGRESS where PROGRESS.SUBJECT like '����'

--5 if else, begin end
DECLARE @aud int = (SELECT count(*) from AUDITORIUM) 
if @aud > 50
begin
	PRINT '� ��� ����� ���������'
end
begin
	PRINT '� ��� ���� ���������'
end

--6 case
SELECT (case
	when NOTE between 0 and 3 then '�� ����'
	when NOTE between 4 and 5 then '����, �� �����'
	when NOTE between 6 and 7 then '���� ������'
	when NOTE between 8 and 10 then '���� ������'
	end) ������, count(*) [����������] from PROGRESS
group by (case
	when NOTE between 0 and 3 then '�� ����'
	when NOTE between 4 and 5 then '����, �� �����'
	when NOTE between 6 and 7 then '���� ������'
	when NOTE between 8 and 10 then '���� ������'
	end)

--7 �������, while
create table #hello (tind int, tfield varchar(100)) 
GO
SET nocount on --�� �������� ��������� � ����� �����
DECLARE @i int = 0
while @i < 1000
begin
	insert #hello(tind, tfield) values (floor(30000*rand()), -- ���������� ���������� ����� �����, ������� <= �������� ��������
	replicate('hello', 10))
	if (@i % 100 = 0) PRINT @i;
	SET @i = @i + 1
end
select * from #hello;

 --8 return
DECLARE @q int = 1
PRINT @q+1
PRINT @q+2
return
PRINT @q+3

--9 try catch
begin try 
	update PROGRESS SET NOTE = 'hello' where NOTE = 4
end try
begin catch
	PRINT ERROR_NUMBER() 
	PRINT ERROR_MESSAGE()
	PRINT ERROR_LINE()
	PRINT ERROR_PROCEDURE()
	PRINT ERROR_SEVERITY()
	PRINT ERROR_STATE()
end catch

declare @number int = 1
while(@number < 21)
	begin
	if ((@number%2) = 0)	select @number [�����]
	set @number = @number + 1;
end