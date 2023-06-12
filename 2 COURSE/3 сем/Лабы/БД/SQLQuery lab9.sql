use Halaleenko_laba4
exec sp_helpindex 'AUDITORIUM_TYPE' 

--1 план запроса и стоимость 
create table #hello (tind int, tfield varchar(100)) 
go
set nocount on --не выводить сообщения о вводе строк
declare @i int = 0
while @i < 1000
	begin
		insert #hello(tind, tfield) values (floor(30000*rand()), replicate('hello', 10))
		if (@i % 100 = 0) print @i;
		set @i = @i + 1
	end
go

select * from #hello where tind between 1500 and 2500 order by tind
checkpoint --фиксация БД
dbcc dropcleanbuffers
			   --DROP TABLE #hello;
				 --drop index #hello.#hello_cl
create clustered index #hello_cl on #hello(tind asc)
  go
  
--2 некластеризованный 
create table #hello2 (tkey int, cc int identity(1,1), tf varchar(100)) 
go
set nocount on
declare @f int = 0
while @f < 10000
begin
	insert #hello2(tkey, tf) values (floor(30000*rand()), replicate('hello', 10))
	if (@f % 100 = 0) print @f;
	set @f = @f + 1
end

--drop table #hello2

select count(*) [Количество строк] from #hello2
select * from #hello2

create index #hello2_nonclu on #hello2(tkey, cc)

select * from #hello2 where tkey > 1500 and cc < 4500
select * from #hello2 order by tkey, cc


--3 некластеризованный индекс покрытия
create table #hello3 (tkey int, cc int identity(1,1), tf varchar(100)) 
go
set nocount on
declare @k int = 0
while @k < 10000
begin
	insert #hello3(tkey, tf) values (floor(30000*rand()), replicate('hello', 10))
	if (@k % 100 = 0) print @k;
	set @k = @k + 1
end

select count(*) [Количество строк] from #hello3
select * from #hello3

create index #hello3_tkey_x on #hello3(tkey) include (cc)

select * from #hello3 where tkey > 15000
--drop table #hello3

--4 некластеризированный фильтруемый индекс
select tkey from #hello3 where tkey between 5000 and 10000 
select tkey from #hello3 where tkey > 3000 and tkey < 5000
select tkey from #hello3 where tkey = 1000

create index #hello_where on #hello3(tkey) where (tkey >= 3000 and tkey <= 5000)


--5 фрагментация
create index #hello3_tkey on #hello3(tkey) 
	 go
select name [Индекс], avg_fragmentation_in_percent [Фрагментация (%)]
        FROM sys.dm_db_index_physical_stats(DB_ID(N'TEMPDB'), 
        OBJECT_ID(N'#hello3'), NULL, NULL, NULL) ss
        JOIN sys.indexes ii on ss.object_id = ii.object_id and ss.index_id = ii.index_id where name is not null;

insert top(10000000) #hello3(tkey, tf) select tkey, tf from #hello3

alter index #hello3_tkey on #hello3 reorganize 
alter index #hello3_tkey on #hello3 rebuild with (online = off) 


-- 6 fillfactor процент заполнения индексных страниц нижнего уровня
drop index #hello3_tkey on #hello3 
create index #hello3_tkey on #hello3(tkey) with (fillfactor = 65)
   go
insert top(50) percent #hello3(tkey, tf) select tkey, tf from #hello3

select name [Индекс], avg_fragmentation_in_percent [Фрагментация (%)]
        from sys.dm_db_index_physical_stats(db_id(N'TEMPDB'), 
        object_id(N'#hello3'), NULL, NULL, NULL) ss
        join sys.indexes ii on ss.object_id = ii.object_id and ss.index_id = ii.index_id where name is not null;
