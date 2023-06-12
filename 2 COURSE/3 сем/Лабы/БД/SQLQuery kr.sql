use EX

--посчитать кол-во товаров, заказанных сотрудниками каждого офиса и отсортировать по убыванию суммарного значени€ всех заказов
Select SALESREPS.NAME, Sum(ORDERS.QTY) [количество]
from SALESREPS inner join ORDERS on SALESREPS.EMPL_NUM = ORDERS.REP
group by SALESREPS.NAME 
order by Sum(ORDERS.QTY) desc

-------------------------

select OFFICES.CITY [√ород], OFFICES.OFFICE [номер офиса] 
from OFFICES 
inner join SALESREPS on OFFICES.OFFICE = SALESREPS.REP_OFFICE
inner join ORDERS on SALESREPS.EMPL_NUM = ORDERS.REP
where ORDER_DATE between '01.01.2007' and '01.01.2008'

