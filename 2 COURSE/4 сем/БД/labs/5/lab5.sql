--1. Получите список всех табличных пространств.
select * from dba_tablespaces;

--2
create tablespace HAN_QDATA_L5
  datafile 'C:\БД\lab5\HAN_QDATA_L5.dbf'
  size 10 m
  autoextend on next 5 m
  maxsize 30 m
  extent management local
  offline;

alter tablespace HAN_QDATA_L5 online;

alter user SYS
  default tablespace HAN_QDATA_L5 quota 2m on HAN_QDATA_L5;
    
create table HAN_T1(num int primary key, text varchar(150)) tablespace HAN_QDATA_L5;

insert into HAN_T1 values (1, 'one');
insert into HAN_T1 values (2, 'two');
insert into HAN_T1 values (3, 'three');

select * from HAN_T1;
  
--3. Список сегментов HAN_QDATA
select * from user_segments where tablespace_name = 'HAN_QDATA_L5';

--6
drop table HAN_T1;

--7
select * from user_segments where tablespace_name = 'HAN_QDATA_L5';
select * from USER_RECYCLEBIN;

--8. Восстановите (FLASHBACK) удаленную таблицу. 
flashback table HAN_T1 to before drop;

--9. Заполнение на 10000 сторок
declare i int:= 4;
begin loop i:=i+1;
  insert into HAN_T1 values (i,'number');
  exit when (i = 10000);
end loop;
end;

select * from HAN_T1;

--10
--how many extents
select * from user_segments where tablespace_name = 'HAN_QDATA_L5';
select * from user_extents where segment_name = 'HAN_T1';

--11. Список всех сегментов в БД
select * from user_extents;

--12
select rowid from HAN_T1;

--13
select ora_rowscn from HAN_T1;

--16.
drop tablespace HAN_QDATA_L5 including contents and datafiles;


select distinct segment_type from dba_segments;
