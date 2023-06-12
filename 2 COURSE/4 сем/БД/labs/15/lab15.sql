--1. create table T_RANGE with range partition
CREATE TABLE T_RANGE    
(
    num number
)
PARTITION BY RANGE (num)
(
  PARTITION num_less_100 VALUES LESS THAN (100)
  STORAGE (INITIAL 64K),
  PARTITION num_max_value VALUES LESS THAN (MAXVALUE)
  STORAGE (INITIAL 159K)
) ENABLE ROW MOVEMENT;

drop table T_RANGE;

--2. create table T_INTERVAL with interval partition
CREATE TABLE T_INTERVAL 
(
  DateKey date
)
PARTITION BY RANGE (DateKey)
(
  PARTITION before_2018 VALUES LESS THAN (TO_DATE('01-01-2022','dd-mm-yyyy'))
);

drop table T_INTERVAL;

--3. create table T_HASH with hash partition
CREATE TABLE T_HASH
(
  TextKey varchar2(50)
)
PARTITION BY HASH (TextKey)
PARTITIONS 2
STORAGE (INITIAL 64K)
ENABLE ROW MOVEMENT;

drop table T_HASH;

--4. create table T_LIST with list partition
CREATE TABLE T_LIST
(
  CharKey char
)
PARTITION BY LIST (CharKey)
(
  PARTITION chars VALUES ('c', 'h', 'a', 'r')
  STORAGE (INITIAL 64K),
  PARTITION other_chars VALUES (DEFAULT)
  STORAGE (INITIAL 64K)
) ENABLE ROW MOVEMENT;                   

drop table T_LIST;

--5. insert values in tables

insert into T_RANGE values (19);
insert into T_RANGE values (180);

SELECT partition_name FROM user_tab_partitions WHERE table_name = 'T_RANGE';

select * from t_range partition (num_less_100);
select * from t_range partition (num_max_value);

-----------------------------------
--select * from user_objects;         --check objects (33)

insert into T_INTERVAL values (TO_DATE('01-01-2019','dd-mm-yyyy'));
insert into T_INTERVAL values (TO_DATE('18-10-2002','dd-mm-yyyy'));

SELECT partition_name FROM user_tab_partitions WHERE table_name = 'T_INTERVAL';

select * from t_interval partition (before_2018);

-----------------------------------
--select * from user_objects;        

insert into T_HASH values ('text');
insert into T_HASH values ('texttext');

SELECT partition_name FROM user_tab_partitions WHERE table_name = 'T_HASH';

select * from t_hash partition (SYS_P855);
select * from t_hash partition (SYS_P856);

-----------------------------------

insert into T_LIST values ('c');
insert into T_LIST values ('r');
insert into T_LIST values ('p');

select * from t_list partition (chars);
select * from t_list partition (other_chars);

---------------------------------------------------------------------------------

--6. show for all tables replacing between sections with UPDATE
select * from t_range partition (num_less_100);
select * from t_range partition (num_max_value);
update t_range set num = 99 where num = 180;

update t_interval set datekey = '16-04-2016' where datekey = '01-01-2019';

update t_hash set textkey = 'texttext123' where textkey = 'text';

update t_list set charkey = 'k' where charkey = 'c';

--7. ALTER TABLE MERGE

alter table t_range MERGE PARTITIONS num_less_100, num_max_value INTO PARTITION num_max_value;
select * from user_tab_partitions where table_name = 'T_RANGE';

--8. ALTER TABLE SPLIT 

alter table t_range SPLIT PARTITION num_max_value INTO
(
  PARTITION num_less_100 values less than (100),
  PARTITION num_max_value
);

select * from user_tab_partitions where table_name = 'T_RANGE';

--9. ALTER TABLE EXCHANGE 

alter table t_range EXCHANGE PARTITION num_max_value WITH TABLE t_range_ WITHOUT VALIDATION;
select * from t_range partition (num_max_value);

select * from user_tab_partitions where table_name = 'T_RANGE';


--10 
-- список всех секционированных таблиц;
SELECT table_name FROM all_tab_partitions
--	список всех секций какой-либо таблицы;
SELECT partition_name FROM all_tab_partitions WHERE table_name = 'T_RANGE';
--	список всех значений из какой-либо секции по имени секции;
SELECT * FROM T_INTERVAL PARTITION (before_2018);
--	список всех значений из какой-либо секции по ссылке.
SELECT * FROM T_LIST PARTITION FOR(0);
 
---------------------------------------------------------------------------------

 DROP TABLE T_RANGE;
 DROP TABLE T_INTERVAL;
 DROP TABLE T_HASH;
 DROP TABLE T_LIST;
