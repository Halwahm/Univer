--1. �������� ������ ���� ������������ PDB � ������ ���������� ORA12W. ���������� �� ������� ���������.
select name, open_mode, con_id from v$pdbs; 
select pdb_name, pdb_id, status from SYS.dba_pdbs;

--3. ��������� ������ � ORA12W, ����������� �������� �������� �����������.
select * from v$instance;

--4. ������������ � XXX_PDB c ������� SQL Developer �������� ���������������� ������� (��������� ������������, ����, 
--������� ������������, ������������ � ������ U1_XXX_PDB).

--ALTER SESSION SET "_ORACLE_SCRIPT"=true

CREATE TABLESPACE TS_HAN
    DATAFILE 'C:\��\3\TS_han_pdb.dbf'
    SIZE 7 m
    AUTOEXTEND ON NEXT 5M
    MAXSIZE 20M
    EXTENT MANAGEMENT LOCAL;
    
CREATE TEMPORARY TABLESPACE  TS_HAN_TEMP
    TEMPFILE 'C:\��\3\TS_HAN_temp_pdb.dbf'
    SIZE 5 m
    AUTOEXTEND ON NEXT 3M
    MAXSIZE 30M
    EXTENT MANAGEMENT LOCAL;
    
--drop tablespace TS_HAN_TEMP;
    
CREATE ROLE RL_HANCORE;

--drop role RL_HANCORE

grant create session,
      create table,
      create view,
      create procedure,
      drop any table,
      drop any view,
      drop any procedure 
to RL_HANCORE;
commit;

--grant create session to RL_HANCORE;
select * from dba_sys_privs where grantee = 'RL_HANCORE';

CREATE PROFILE PF_HANCORE LIMIT
    PASSWORD_LIFE_TIME 180
    SESSIONS_PER_USER 3
    FAILED_LOGIN_ATTEMPTS 7
    PASSWORD_LOCK_TIME 1
    PASSWORD_REUSE_TIME 10
    PASSWORD_GRACE_TIME DEFAULT
    CONNECT_TIME 180
    IDLE_TIME 30;

--select * from v$pdbs;


create user U1_HAN_PDB identified by 12345
default tablespace TS_HAN quota unlimited on TS_HAN
temporary tablespace TS_HAN_TEMP
account unlock;


grant create session, create table to U1_HAN_PDB
--grant create table to U1_HAN_PDB


--5. ������������ � ������������ U1_XXX_PDB, � ������� SQL Developer, �������� ������� XXX_table, �������� � ��� ������, ��������� SELECT-������ � �������.

create table HAN_table ( x int , y varchar(5))

insert into HAN_table values (1, 'frst');
insert into HAN_table values (3, 'thrd');

select * from HAN_table

--drop table HAN_table

--6.
select * from DBA_TABLESPACES; 
select * from DBA_ROLES;
select * from DBA_PROFILES;  
select * from ALL_USERS;

select * from DBA_DATA_FILES;   
select * from DBA_TEMP_FILES;  
select GRANTEE, PRIVILEGE from DBA_SYS_PRIVS; 

--7. 
create user C##HAN identified by 12345
account unlock;
grant create session, create table to C##HANPDB;


CREATE TABLESPACE TS_CCC
    DATAFILE 'C:\��\3\TS_CCC_pdb.dbf'
    SIZE 7 m
    AUTOEXTEND ON NEXT 5M
    MAXSIZE 20M
    EXTENT MANAGEMENT LOCAL;
    
CREATE TEMPORARY TABLESPACE  TS_CCC_TEMP
    TEMPFILE 'C:\��\3\TS_CCC_temp_pdb.dbf'
    SIZE 5 m
    AUTOEXTEND ON NEXT 3M
    MAXSIZE 30M
    EXTENT MANAGEMENT LOCAL;
    

create user C##HAN identified by 12345
default tablespace TS_CCC_PDB quota unlimited on TS_CCC_PDB
temporary tablespace TS_CCC_TEMP_PDB
account unlock

grant create session, create table to C##HANPDB;

grant RL_HANCORE to C##HANPDB

select status from v#session;
-- from HAN_pdb
grant create session, create table to C##HANPDB;

--10. ������������ ������������� C##XXX, �������� ������� � �������� � ��� ������.
create table CHANTAB ( x int , y varchar(5))
--drop table CHANTAB;
insert into CHANTAB values (1, 'frst');
insert into CHANTAB values (2, 'scnd');

select * from CHANTAB

--11. ����������� ��� �������, ��������� ������������� C##XXX � U1_XXX_PD.
select * from dba_data_files;
select * from user_objects;


alter pluggable database HAN_pdb close immediate;
--drop pluggable database HAN_pdb;


drop user C##HANPDB cascade;