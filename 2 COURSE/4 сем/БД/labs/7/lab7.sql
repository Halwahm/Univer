--1.	Определите общий размер области SGA.
SELECT SUM(VALUE) FROM V$SGA;

--2.	Определите текущие размеры основных пулов SGA.
SELECT * FROM V$SGA;

--3.	Определите размеры гранулы для каждого пула.
select component,
    current_size,
    max_size,
    last_oper_mode,
    last_oper_time,
    granule_size,
    current_size/granule_size as Ratio
    from v$sga_dynamic_components
where current_size > 0;

--4.	Определите объем доступной свободной памяти в SGA.
select current_size from v$sga_dynamic_free_memory;

--5.	Определите максимальный и целевой размер области SGA.
select 
sum(max_size),
sum(current_size)
from v$sga_dynamic_components;

--6.	Определите размеры пулов КЕЕP, DEFAULT и RECYCLE буферного кэша.
select 
component,
min_size,
current_size
from v$sga_dynamic_components;

--7.	Создайте таблицу, которая будет помещаться в пул КЕЕP. Продемонстрируйте сегмент таблицы.
create tablespace HAN_QDATA_L5
  datafile 'C:\БД\lab5\HAN_QDATA_L5.dbf'
  size 10 m
  autoextend on next 5 m
  maxsize 30 m
  extent management local
  online;

create table XXX (k int) storage(buffer_pool keep);

select segment_name, segment_type, tablespace_name, buffer_pool from user_segments
where segment_name  = 'XXX';

--8.	Создайте таблицу, которая будет кэшироваться в пуле DEFAULT. Продемонстрируйте сегмент таблицы. 
create table YYY (k int) storage(buffer_pool default);

select segment_name, segment_type, tablespace_name, buffer_pool from user_segments
where segment_name  = 'YYY';

--9.	Найдите размер буфера журналов повтора.
SELECT VALUE AS "REDO LOG BUFFER"
FROM V$PARAMETER
WHERE NAME = 'log_buffer';

--10.	Найдите размер свободной памяти в большом пуле.
select *
FROM V$sgastat
WHERE pool = 'large pool' and  name = 'free memory';

--11.	Определите режимы текущих соединений с инстансом (dedicated, shared).
select username, sid, serial#, server, paddr, status from v$session where username is not null;

--12.	Получите полный список работающих в настоящее время фоновых процессов.
select name, description from v$bgprocess where paddr!=hextoraw('00') order by name;

--13.	Получите список работающих в настоящее время серверных процессов.
SELECT spid, pname, username, program
FROM v$process
WHERE background = 0;

--14.	Определите, сколько процессов DBWn работает в настоящий момент.
SELECT COUNT(*) AS "Number of DBWn processes"
FROM v$process
WHERE pname LIKE 'DBW%';

--15.	Определите сервисы (точки подключения экземпляра).
SELECT DISTINCT name
FROM v$active_services;

--16.	Получите известные вам параметры диспетчеров.
SELECT name, value
FROM v$parameter
WHERE name LIKE '%dispatch%';
