--1.	���������� ����� ������ ������� SGA.
SELECT SUM(VALUE) FROM V$SGA;

--2.	���������� ������� ������� �������� ����� SGA.
SELECT * FROM V$SGA;

--3.	���������� ������� ������� ��� ������� ����.
select component,
    current_size,
    max_size,
    last_oper_mode,
    last_oper_time,
    granule_size,
    current_size/granule_size as Ratio
    from v$sga_dynamic_components
where current_size > 0;

--4.	���������� ����� ��������� ��������� ������ � SGA.
select current_size from v$sga_dynamic_free_memory;

--5.	���������� ������������ � ������� ������ ������� SGA.
select 
sum(max_size),
sum(current_size)
from v$sga_dynamic_components;

--6.	���������� ������� ����� ���P, DEFAULT � RECYCLE ��������� ����.
select 
component,
min_size,
current_size
from v$sga_dynamic_components;

--7.	�������� �������, ������� ����� ���������� � ��� ���P. ����������������� ������� �������.
create tablespace HAN_QDATA_L5
  datafile 'C:\��\lab5\HAN_QDATA_L5.dbf'
  size 10 m
  autoextend on next 5 m
  maxsize 30 m
  extent management local
  online;

create table XXX (k int) storage(buffer_pool keep);

select segment_name, segment_type, tablespace_name, buffer_pool from user_segments
where segment_name  = 'XXX';

--8.	�������� �������, ������� ����� ������������ � ���� DEFAULT. ����������������� ������� �������. 
create table YYY (k int) storage(buffer_pool default);

select segment_name, segment_type, tablespace_name, buffer_pool from user_segments
where segment_name  = 'YYY';

--9.	������� ������ ������ �������� �������.
SELECT VALUE AS "REDO LOG BUFFER"
FROM V$PARAMETER
WHERE NAME = 'log_buffer';

--10.	������� ������ ��������� ������ � ������� ����.
select *
FROM V$sgastat
WHERE pool = 'large pool' and  name = 'free memory';

--11.	���������� ������ ������� ���������� � ��������� (dedicated, shared).
select username, sid, serial#, server, paddr, status from v$session where username is not null;

--12.	�������� ������ ������ ���������� � ��������� ����� ������� ���������.
select name, description from v$bgprocess where paddr!=hextoraw('00') order by name;

--13.	�������� ������ ���������� � ��������� ����� ��������� ���������.
SELECT spid, pname, username, program
FROM v$process
WHERE background = 0;

--14.	����������, ������� ��������� DBWn �������� � ��������� ������.
SELECT COUNT(*) AS "Number of DBWn processes"
FROM v$process
WHERE pname LIKE 'DBW%';

--15.	���������� ������� (����� ����������� ����������).
SELECT DISTINCT name
FROM v$active_services;

--16.	�������� ��������� ��� ��������� �����������.
SELECT name, value
FROM v$parameter
WHERE name LIKE '%dispatch%';
