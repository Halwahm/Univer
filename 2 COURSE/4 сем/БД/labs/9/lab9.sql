--already can create table, view, procedure
--select * from dba_sys_privs where grantee = 'C##RL_HANCORE';

--CREATE ROLE C##RL_HANCORE;

--grant create session,
--      create table,
--      create view,
--      create procedure,
--     drop any table,
--      drop any view,
--      drop any procedure 
--to C##RL_HANCORE;
--commit;

--create user C##HAN identified by 12345
--account unlock;

--grant RL_HANCORE to C##HAN
--GRANT CONNECT TO C##HAN;
--GRANT CREATE SESSION TO C##HAN;
--GRANT RESOURCE TO C##HAN;
--ALTER USER C##HAN DEFAULT TABLESPACE TS_HAN;

--1
grant 
  create sequence, 
  create cluster
to C##HAN;


grant create TABLESPACE to C##HAN;
grant alter TABLESPACE to C##HAN;
grant create synonym to C##HAN;
grant create public synonym to C##HAN;

grant create materialized view to C##HAN;
grant create view to C##HAN;
grant query rewrite to C##HAN;







--2
CREATE GLOBAL TEMPORARY TABLE sales_info (customer_name VARCHAR2 (30), transaction_no NUMBER, transaction_date DATE);
insert into sales_info VALUES ('cust1', 2, TO_DATE('01-04-2023', 'DD-MM-YYYY'));
select * from sales_info;

-------------CREATE SEQUENCE------------

--3

create sequence S1
  increment by 10
  start with 1000
  nomaxvalue
  nominvalue
  nocycle
  nocache   
  noorder;  
  
  select s1.currval, s1.nextval from dual;
  
  drop sequence s1;
  
  --4
  
  create sequence S2
    increment by 10
    start with 10
    maxvalue 100
    nominvalue
    nocycle;
    
select s2.currval, s2.nextval from dual;
select s2.nextval from dual;

drop sequence s2;

--5
create sequence S3
  increment by -10
  start with 10
  maxvalue 20  --START WITH cannot be more than MAXVALUE
  minvalue -100
  nocycle
  order;
  
select S3.nextval from dual;

drop sequence S3;

--6
create sequence S4
  increment by 1
  start with 1
  maxvalue 10
  cycle
  cache 5
  noorder;
  
select S4.nextval from dual;

drop sequence S4;

--7
--select sequence_name, sequence_owner from sys.dba_sequences where sequence_owner = 'C##HAN';
select * from user_sequences;
---------tables--------------

--8
--CREATE TABLESPACE TS_HAN
--    DATAFILE 'C:\ад\9\TS_han_pdb.dbf'
--    SIZE 7 m
--    AUTOEXTEND ON NEXT 5M
--    MAXSIZE 20M
--    EXTENT MANAGEMENT LOCAL;


create table T1 
  (
   N1 NUMBER(20), 
   N2 NUMBER(20), 
   N3 NUMBER(20), 
   N4 NUMBER(20)
  ) storage(buffer_pool KEEP)
    tablespace TS_HAN;    
    
--alter user C##HAN
--  default tablespace TS_HAN quota 5m on TS_HAN;
    
insert into T1 values (s1.nextval, s2.nextval, s3.nextval, s4.nextval);

select * from T1;

-----------clusters------------
--9-12
create cluster ABC        --hash-type
  (
    X NUMBER (10),
    V VARCHAR2 (12)
  ) hashkeys 200    
    tablespace TS_HAN;
  
  
--alter user C##HAN
--  default tablespace TS_HAN quota 5m on TS_HAN;
  
create table A
  (
    XA NUMBER (10),
    VA VARCHAR2 (12),
    AA int
  ) cluster ABC (XA, VA);
  
create table B
  (
    XB NUMBER (10),
    VB VARCHAR2 (12),
    BB int
  ) cluster ABC (XB, VB);

create table C
  (
    XC NUMBER (10),
    VC VARCHAR2 (12),
    CC int
  ) cluster ABC (XC, VC);
  
--find created tables and clusters in dictionaries Oracle
--dba_clusters
--dba_tables

--13
--select cluster_name, owner, tablespace_name, cluster_type, cache from dba_clusters;

--select * from dba_tables where table_name = 'A' OR table_name = 'B' OR table_name = 'C';

select * from user_clusters;
select * from user_tables;

---------------synonym------------------------------
--14-15
create synonym SYN_C for C;

select * from SYN_C;

drop synonym SYN_C;

-------------public synonym-------------------------
create public synonym PUBL_SYN_B for B;

select * from PUBL_SYN_B;

drop synonym PUBL_SYN_B;

select * from user_synonyms;
--------------------------------------------------------------------------------
--16
create table AA 
  (
    X number (10),
    V varchar2 (12),
    constraint X_PK primary key (X)
  );

--drop table AA;
--drop table BB;
  
insert into AA (X, V) values (1, 'one');
insert into AA (X, V) values (2, 'two');
insert into AA (X, V) values (3, 'three');
insert into AA (X, V) values (4, 'four');
insert into AA (X, V) values (5, 'five');

select * from AA;

create table BB
  (
    XX NUMBER (10),
    VV VARCHAR2 (12),
    constraint XX_PK foreign key (XX) references AA(X)
  );
  
insert into BB (XX, VV) values (1, 'odin');
insert into BB (XX, VV) values (2, 'dva');
insert into BB (XX, VV) values (3, 'tri');
insert into BB (XX, VV) values (4, 'chetyre');
insert into BB (XX, VV) values (5, 'pyat');

select * from BB

create view V1
as
  select AA.X, AA.V, BB.VV
    from AA inner join BB on AA.X = BB.XX;
    
select * from V1;
--drop view V1;

--17
create materialized view MV
  build immediate         --create view in moment of operator's processing
  refresh complete        --fast / copmlete / force(default)
  as select AA.X, AA.V, BB.VV
  from AA
  inner join BB on AA.X = BB.XX;
  
alter materialized view MV
    refresh complete on demand
    next sysdate + numtodsinterval (2, 'MINUTE');
  
select * from MV;

--drop materialized view MV;

--18
--as sys dba
GRANT CREATE DATABASE LINK TO C##HAN;

CREATE DATABASE LINK DB13 
   CONNECT TO C##HAN
   IDENTIFIED BY PASSWORD
   USING 'han_pba';


--19. select, insert, update, delete, function, procedure with objects of remote server

--create SYSTEM table
create table test_dblink
(
  num int primary key,s
  str nvarchar2(15)
);

select * from test_dblink;
--drop table test_dblink
