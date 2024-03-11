--PROFILE
create profile C##PFHAN limit
  password_life_time 180 
  sessions_per_user 3 
  failed_login_attempts 7 
  password_lock_time 1
  password_reuse_time 10 
  password_grace_time default 
  connect_time 180 
  idle_time 30; 

  select * from dba_profiles where profile='C##PFHAN';
--ROLE
 create role C##RL_HAN;
 select * from dba_roles where role like '%HAN%';
  GRANT CREATE SESSION TO C##RL_HAN;
  GRANT CREATE VIEW, DROP ANY VIEW TO C##RL_HAN;
  GRANT CREATE PROCEDURE, DROP ANY PROCEDURE TO C##RL_HAN;
  GRANT CREATE TABLE, DROP ANY TABLE TO C##RL_HAN;

select * from dba_sys_privs where grantee like '%C##RL_HAN';

--USER
  create user C##HAN identified by 12345
    profile C##PFHAN
    account unlock;
 GRANT CREATE DATABASE LINK TO C##HAN;

    select * from all_users where username like '%HAN%';

GRANT C##RL_HAN TO C##HAN;
GRANT ALL PRIVILEGES TO C##HAN;
---------------------------------------------------
CREATE DATABASE LINK TEA
CONNECT TO C##SAI IDENTIFIED BY "12345"
USING '192.168.229.155/FREE';


drop database link TEA;
---------------------------------------
---------------------------------------
---------------------------------------

create table RIS(
    id int primary key,
    str varchar(20), 
    numb NUMBER GENERATED ALWAYS AS IDENTITY
);
--drop table RIS;
select * from RIS@TEA;
select * from RIS;
--delete RIS@TEA;
--delete RIS;
commit;
rollback;

begin
    insert into RIS(id,str) values(2,'ars');
    insert into RIS@TEA(id,str) values(2,'tanya');
commit;
end;

select * from RIS@TEA;
select * from RIS;

begin
    insert into RIS(id,str) values(3,'nastya');
    update RIS@TEA set str='tanya123' where str ='tanya';
commit;
end;

begin
    update RIS set str='nastya321' where str ='nastya';
    insert into RIS@TEA(id,str) values(6,'kasper');
commit;
end;

select * from RIS@TEA;
select * from RIS;

begin
    insert into RIS@TEA(id,str) values(21,'rexd');
commit;
end;

select * from RIS@TEA;
select * from RIS;

begin
    delete from RIS where id = 2;
end;

commit;