--set serveroutput on 
--1. add in teacher table columns birthday and salary 

alter table TEACHER
add BIRTHDAY date;

alter table TEACHER
add SALARY number(7,2);

select * from teacher;

declare
  cursor teacher_curs is select * from teacher for update;
  teacher_row teacher%rowtype;
  rand_date date;
  rand_sal number;
begin
    for teacher_row in teacher_curs
    loop
          SELECT TO_DATE( TRUNC(DBMS_RANDOM.VALUE(TO_CHAR(DATE '1990-01-01','J'), 
          TO_CHAR(DATE '2000-01-01','J'))),'J') into rand_date FROM DUAL;
          SELECT DBMS_RANDOM.VALUE (1000,2500) into rand_sal FROM DUAL;
           update teacher
           set birthday = rand_date, salary = TRUNC(rand_sal, 2)
           where current of teacher_curs;
    end loop;
    
    exception
    when others
    then  dbms_output.put_line(sqlerrm);
end;

select * from teacher;

--2. get list of teachers in format 
declare
    cursor list_of_teach is select teacher_name from teacher where to_char(birthday, 'd') = '1';
    v_array apex_application_global.vc_arr2;
    v_string varchar2(50);
begin
    for r_teach in list_of_teach
    loop
        v_array := apex_util.string_to_table(r_teach.teacher_name, ' ');
        if v_array.count = 3 
            then v_string := v_array(1)||' '||substr(v_array(2), 1, 1)||'.'||substr(v_array(3), 1, 1)||'.';
        end if;
        dbms_output.put_line(v_string);
    end loop;
end;
  
  
--3. (view) list of teachers whowas born in next month
create view teacher_next_month as
  select * from teacher where to_char(birthday, 'mm') = to_char(add_months(sysdate, 1), 'mm');

select * from teacher_next_month;

drop view teacher_next_month;

--4. count of teachers, borned each month
create view teachers_count_by_month as
    select (extract (month from birthday)) as birth_month, count(*) as count
    from teacher
    group by (extract (month from birthday))    --get month from birthday date
    order by birth_month;

select * from teachers_count_by_month;

drop view teachers_count_by_month;

--5. create cursor and print list of teachers with universary in next year
declare
    cursor teacher_university is select teacher_name, birthday from teacher;
begin
    for teacher in teacher_university
    loop
        if mod(to_number(extract(year from teacher.birthday)) - to_number(extract(year from (add_months(sysdate, 12)))), 5) = 0 
            then dbms_output.put_line(teacher.teacher_name||' --- '||teacher.birthday|| '; '|| 'Ему исполняется: '||TRUNC((MONTHS_BETWEEN(SYSDATE, teacher.birthday)/12)+1));
        end if;
    end loop;
end;

--6. 
declare
    cursor c_pulp is select pulpit, faculty from pulpit;
    cursor c_fac is select faculty from faculty;
    avgsal number(6);
begin
    dbms_output.put_line('pulpits:');
    for r_pulp in c_pulp
    loop
        select floor(avg(salary)) into avgsal 
          from teacher 
          where pulpit = r_pulp.pulpit;
          
        dbms_output.put_line(rpad(r_pulp.pulpit, 20) || ' ' || avgsal);
    end loop;
    
    dbms_output.put_line('faculties:');
    for r_fac in c_fac
    loop
        select floor(avg(salary)) into avgsal 
          from teacher 
          where pulpit in (select pulpit from pulpit where faculty = r_fac.faculty);
          
        dbms_output.put_line(rpad(r_fac.faculty, 20) || ' ' || avgsal);
    end loop;
    
    select floor(avg(salary)) into avgsal from teacher;
    dbms_output.put_line(rpad('all', 20) || avgsal);
end;

--7. Деление чисел zero_devide
DECLARE
  dividend NUMBER := 10;
  divisor NUMBER := 0;
  result NUMBER;
BEGIN
  IF divisor = 0 THEN
    RAISE_APPLICATION_ERROR(-20001, 'Ошибка: деление на 0!');
  ELSE
    result := dividend / divisor;
    DBMS_OUTPUT.PUT_LINE('Результат деления: ' || result);
  END IF;
EXCEPTION
  WHEN ZERO_DIVIDE THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: деление на 0!');
END;
----------------------------
DECLARE
  dividend NUMBER := 10;
  divisor NUMBER := 11;
  result NUMBER;
BEGIN
  IF divisor = 0 THEN
    RAISE_APPLICATION_ERROR(-20001, 'Ошибка: деление на 0!');
  ELSE
    result := dividend / divisor;
    DBMS_OUTPUT.PUT_LINE('Результат деления: ' || result);
  END IF;
EXCEPTION
  WHEN ZERO_DIVIDE THEN
    DBMS_OUTPUT.PUT_LINE('Ошибка: деление на 0!');
END;


select * from teacher;

--8. NO_DATA_FOUND
--alter table TEACHER add teacher_code int;
--UPDATE teacher SET teacher_code = TRUNC(DBMS_RANDOM.VALUE(1000, 9999));
DECLARE
  v_teacher_name teacher.teacher_name%TYPE;
  v_teacher_code teacher.teacher_code%TYPE := 5569;
  --v_teacher_code teacher.teacher_code%TYPE := 5568;
BEGIN
  SELECT teacher_name INTO v_teacher_name FROM teacher WHERE teacher_code = v_teacher_code;
  DBMS_OUTPUT.PUT_LINE('Найден преподаватель: ' || v_teacher_name);
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Преподаватель не найден!');
END;

--9. Исключения

DECLARE
  ex1 EXCEPTION;
  ex2 EXCEPTION;
  ex3 EXCEPTION;
  pragma exception_init(ex1, -20001);
  pragma exception_init(ex2, -20001);
  pragma exception_init(ex3, -20001);
BEGIN
  DBMS_OUTPUT.PUT_LINE('Main Block');
  BEGIN
    DBMS_OUTPUT.PUT_LINE('Nested Block');
    RAISE ex2;
  EXCEPTION
    WHEN ex2 THEN
      DBMS_OUTPUT.PUT_LINE('Exception ex2 caught in the nested block');
  END;

  BEGIN
    DBMS_OUTPUT.PUT_LINE('Nested Block 2');
    RAISE ex3;
  EXCEPTION
    WHEN ex3 THEN
      DBMS_OUTPUT.PUT_LINE('Exception ex3 caught in the nested block 2');
  END;

EXCEPTION
  WHEN ex1 THEN
    DBMS_OUTPUT.PUT_LINE('Exception ex1 caught in the main block');
END;

--10. NO_DATA_FOUND
--create table no_dat(no int primary key);

DECLARE
  l_max_val NUMBER;
BEGIN
  SELECT MAX(no) INTO l_max_val FROM no_dat;
  
  IF l_max_val IS NULL THEN
    RAISE NO_DATA_FOUND;
  END IF;
  
  DBMS_OUTPUT.PUT_LINE('Максимальное значение: ' || l_max_val);
END;







--extract
--current_date
--current_timestamp
--sysdate
--localtimestamp
--sys_extract_utc(timestamp '2000-03-28 11:30:00.00 -08:00')
--next_day('01-12-10', '???????')
--last_day
--extract(year from date '2003-08-22')