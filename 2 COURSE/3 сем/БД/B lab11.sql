---------------------------- Task 4 B ----------------------------
set nocount on
begin tran
update Transactions set Info = 'Строка 6' where Counter = 4
insert Transactions values ('Строка 5')
--t1
rollback tran
--t2

---------------------------- Task 5 B ----------------------------

set transaction isolation level read committed
begin tran
update Transactions set Info = 'Строка 6' where Counter = 4
insert Transactions values ('Строка 5')
--t1
commit tran
--t2
select * from Transactions
---------------------------- Task 6 B ----------------------------

set transaction isolation level read committed
begin tran
update Transactions set Info = 'Строка 6' where Counter = 4
--insert Transactions values ('Строка 5')
--t1
commit tran
--t2
rollback
---------------------------- Task 7 B ----------------------------

set transaction isolation level read committed
begin tran
insert Transactions values ('Строка 5')
--t1
rollback tran
--t2