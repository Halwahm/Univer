-- 9. � ��������� ���� MyStart ������, ��������� ������� � ������ XXX_t
create table TOV_T(
    x number(3) primary key,
    s varchar2(50)
);
-- 10. ������� � ����� Tables, ��������� ������� XXX_t.
-- 11. ��������� ������ ����������� INSERT, ������������ 3 ������ � 
-- ������� XXX_t. ��������� ��������� INSERT. ��������� �������� COMMIT
insert into TOV_T (x, s) values (1, 'first');
insert into TOV_T (x, s) values (2, 'second');
insert into TOV_T (x, s) values (3, 'third');
select * from TOV_T
commit;
-- 12. ��������� ������ ���������� UPDAT�, ���������� 2 ������ � 
-- ������� XXX_t. ��������� �������� UPDAT�. ��������� �������� COMMIT
update TOV_T set x=x+10 where x in (1, 2);
commit;
-- 13. ��������� ������ ����������� SELECT (������� �� �������, 
-- ���������� ���������� �������);
select sum(x) from TOV_T;
select * from TOV_T where x < 10;
-- 14. ��������� ������ ���������� DELELE, ��������� 1 ������ � �������
-- XXX_t. ��������� �������� DELETE. ��������� �������� COMMIT;
delete from TOV_T where x = 3;
-- 15. �������� ������� XXX_t1, ��������� ���������� �������� ����� � 
-- �������� XXX_t. �������� ������ � ������� XXX_t1.
create table TOV_T1 (
    y number(3) primary key,
    x number(3) references TOV_T(x)
);
insert into TOV_T1 values (10, 11);
insert into TOV_T1 values (20, 12);
select * from TOV_T1;
-- 16. ��������� ������ ����������� SELECT �� ����� ������ (����� � ������ 
-- ����������, ���������� ����������);
select t.x, t.s, t1.y from TOV_T t left join TOV_T1 t1 on t.x = t1.x;
select t.x, t.s, t1.y from TOV_T t right join TOV_T1 t1 on t.x = t1.x;
select t.x, t.s, t1.y from TOV_T t inner join TOV_T1 t1 on t.x = t1.x;
-- 18. ��������� ������ ���������� DROP, ��������� ������� XXX_t, XXX_t1
drop table TOV_T1;
drop table TOV_T;