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
--   alter user C##HAN identified by qwe; 

GRANT C##RL_HAN TO C##HAN;
GRANT ALL PRIVILEGES TO C##HAN;
---------------------------------------------------
CREATE DATABASE LINK COFFE
CONNECT TO GUS IDENTIFIED BY "12345"
USING 'COFFEE';
drop database link COFFE;
---------------------------------------
---------------------------------------
---------------------------------------

create table RIS(id int primary key,str varchar(20), numb NUMBER GENERATED ALWAYS AS IDENTITY);
--drop table RIS@COFFE;
select * from RIS@COFFE;
select * from RIS;
--delete RIS@COFFE;
--delete RIS;
commit;
rollback;---����� �����
--������� 1
begin
    insert into RIS(id,str) values(1,'222');
    insert into RIS@COFFE(id,str) values(2,'222');
commit;
end;

select * from RIS@COFFE;
select * from RIS;

begin
    insert into RIS(id,str) values(4,'222');
    update RIS@COFFE set str='23454' where str ='222';
commit;
end;

begin
    update RIS set str='23454' where str ='222';
    insert into RIS@COFFE(id,str) values(19,'222');
commit;
end;

--������� 2 (��������� ����������� ����������� �� ������� ���������� �������)
insert into RIS@COFFE(id,str) values(2,'222', 45);
commit;

--������� 3

select * from RIS@COFFE;
--2
begin
delete RIS@COFFE where ID=2;
end;

--3
begin



commit;
end;


begin



lock table RIS@COFFE in share mode;
SLEEP(30000);
commit;
end;

--������� RIS � ��������� ���� ������ ����������� � ������ ������ �������, ����� ����������� ����� �� 30000 ����������� (30 ������), � ����� ���������� �����������. 
--���� ������ ���������� �������� �������� ������ � ������� RIS �� ����� ���� �����, ��� ����� ������������� � ����� ������� ������������ �������.










--��������� ��������
create or replace procedure SLEEP(P_MILLI_SECONDS IN NUMBER)
AS LANGUAGE JAVA NAME 'java.lang.Thread.sleep(long)';

