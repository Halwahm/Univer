create tablespace TS_HAN
  datafile 'TS_HAN.dbf'
  size 7m
  autoextend on next 5m
  maxsize 20m
  extent management local;
  
create temporary tablespace TS_HAN_TEMP
  tempfile 'HAN_TEMP.dbf'
  size 5m
  autoextend on next 3m
  maxsize 30m
  extent management local;
commit;
  
select tablespace_name from SYS.DBA_TABLESPACES;

alter session set "_ORACLE_SCRIPT"=true;  

create role RLHAN_CORE;

grant create session,
      create table,
      create view,
      create procedure to RLHAN_CORE;

--grant drop table,
--      drop view,
--      drop procedure to RLHAN_CORE;
commit;

select * from dba_roles where ROLE = 'RLHAN_CORE';
select * from dba_roles where ROLE != 'RLHAN_CORE';
select * from dba_sys_privs;
select * from dba_sys_privs where grantee = 'RLHAN_CORE';

create profile PF_HANCORE limit
  password_life_time 180
  sessions_per_user 3
  failed_login_attempts 7 --кол-во попыток входа
  password_lock_time 1 --кол-во дней блокировки после ошибки
  password_reuse_time 10 --через сколько дней можно повторить пароль
  password_grace_time default --кол-во дней предупреждений о смене пароля
  connect_time 180 --время соединения (мин)
  idle_time 30; --кол-во мин простоя
  
select * from dba_profiles where PROFILE = 'PF_HANCORE';
select * from dba_profiles where PROFILE = 'DEFAULT';
select * from dba_profiles;

create user HANCORE identified by Pa$$w0rd
  default tablespace TS_HAN quota unlimited on TS_HAN
  temporary tablespace TS_HAN_TEMP
  profile PF_HANCORE
  account unlock;
  password expire;
  
grant RLHAN_CORE to HANCORE;
commit;

create tablespace HAN_QDATA
  datafile 'HAN_QDATA.dbf'
  size 10m
  autoextend on next 5m
  maxsize 20m
  extent management local
  offline;
 
 create tablespace HA_QDATA
  datafile 'HA_QDATA.dbf'
  size 10m
  autoextend on next 5m
  maxsize 20m
  extent management local
  offline;
  
alter tablespace HAN_QDATA online;

alter user HANCORE quota 2m on HAN_QDATA;

alter user HANCORE default tablespace HAN_QDATA;

create table HAN_T1
  (x number(3), 
  y varchar(10));
  
insert into HAN_T1 values (1, 'one');
insert into HAN_T1 values (2, 'two');
insert into HAN_T1 values (3, 'three');

select * from HAN_t1;

drop table HAN_T1;

  