--set serveroutput on

--1. simple anonymous block without operators
begin    
  null;
end;      

--2. anonymous block print "Hello world"
begin
  dbms_output.put_line('Hello world');
end;

--3. просмотр всех спец символов
select keyword from v_$reserved_words
    where length = 1 order by keyword;


--4. Скрипт для просмотра всех ключевых слов PL/SQL
select keyword from v_$reserved_words;


--5. Анонимный блок
declare
  a number(3) := 5;
  b number(3) := 2;
  --number(n,s)   n=[0,38], s=[-84,127]
  c1 number(4, 2);
  c2 number(4, -1);
  d binary_float := 11110.10;
  e binary_double := 11110.10;
  f number := 3e10;
  isTrue boolean := true;
  
  begin
    -- inizialization int numbers
    dbms_output.put_line('a = ' ||a);
    dbms_output.put_line('b = ' ||b);
    
    --operations with two int numbers and %
    dbms_output.put_line('a + b = ' ||(a + b));
    dbms_output.put_line('a - b = ' ||(a - b));
    dbms_output.put_line('a * b = ' ||(a * b));
    dbms_output.put_line('a / b = ' ||(a / b));
    dbms_output.put_line('a % b = ' ||(a mod b));
           
    c1 := 11.51;
    dbms_output.put_line('c1 = '||c1);
    c2 := 11.51;
    dbms_output.put_line('c2 = '||c2);
    
    --BINARY_FLOAT
    dbms_output.put_line('d (float) = ' ||d);
    
    --BINARY_DOUBLE
    dbms_output.put_line('e (double) = ' ||e);
    
    --e4 (*10^4)
    dbms_output.put_line('f (*10^4) = ' ||f);
    
    --Boolean
    if isTrue
        then dbms_output.put_line('isTrue = true');
        else dbms_output.put_line('isTrue = false');
    end if;
    exception
      when others
      then
        dbms_output.put_line('error: ' || sqlerrm);
        dbms_output.put_line('code: ' || sqlcode);
end;

--6. PL/SQL содержащий объявление констант (VARCHAR2, CHAR, NUMBER)
declare
  stringConst constant varchar2(10) := 'Hello';
  charConst constant char(10) := 'world';
  numConst constant number(5) := 5;
  begin
  dbms_output.put_line('stringConst = ' || stringConst);
  dbms_output.put_line('Length(stringConst) = ' || length(stringConst));
  
  dbms_output.put_line('charConst = ' || charConst);
  dbms_output.put_line('Length(charConst) = ' || length(charConst));
  
  dbms_output.put_line('numConst = ' || numConst);
  dbms_output.put_line('Length(numConst) = ' || length(numConst));
  dbms_output.put_line('numConst * 100 = ' || numConst * 100);
end;


--7-8. переменные с опциями %TYPE и %ROWTYPE
--%TYPE for def-n var (base other var or field in table)
--%ROWTYPE for def-n strucrure (base table or cursor)

declare 
  subject sys.subject.subject%type;
  pulpit sys.pulpit.pulpit%type;
  faculty_rec sys.faculty%rowtype;
  begin
  subject := 'INF';
  pulpit := 'ISiT';
  faculty_rec.faculty := 'IT';
    faculty_rec.faculty_name := 'Fakul`tet informacionnyh tekhnologij';
    dbms_output.put_line(subject);
    dbms_output.put_line(pulpit);
    dbms_output.put_line(rtrim(faculty_rec.faculty) || ': ' || faculty_rec.faculty_name);
    exception
        when others
        then dbms_output.put_line('error = ' || sqlerrm);
end;

--9. Разработайте АБ, демонстрирующий все возможные конструкции оператора IF .
declare
    x int := 17;
begin
    if 50 > x
        then dbms_output.put_line('50 > ' || x);
    end if;
    if 50 = x
      then dbms_output.put_line('50 = '||x);
    end if;
    if 100 > x
        then dbms_output.put_line('100 > ' || x);
    end if;
    if 100 = x
      then dbms_output.put_line('50 = '||x);
    end if;
end;
--------------------------------------------------------
declare
    x int := 17;
begin
    if 50 > x
        then dbms_output.put_line('50 > ' || x);
    elsif 50 = x
        then dbms_output.put_line('50 = '||x);
    elsif 100 > x
        then dbms_output.put_line('100 > ' || x);
    elsif 100 = x
        then dbms_output.put_line('100 = ' || x);
    else dbms_output.put_line('100 <> ' || x);
    end if;
end;


--10. CASE
declare 
  x pls_integer := 17;
begin
  case x
    when 1 then dbms_output.put_line('1');
    when 2 then dbms_output.put_line('2');
    when 3 then dbms_output.put_line('3');
   else dbms_output.put_line('else');
  end case;
  
  case 
    when 8 > x then dbms_output.put_line('8 > '||x);
    when 8 = x then dbms_output.put_line('8 = '||x);
    when 12 = x then dbms_output.put_line('12 = '||x);
    when x between 13 and 20 then dbms_output.put_line('13 <= '||x||' <=20');
    else dbms_output.put_line('else');
    end  case;
end;

--11-12. LOOP + WHILE
declare 
  x pls_integer := 0;
begin
  loop
  x:= x + 1;
  dbms_output.put_line(x);
  exit when x > 5;
  end loop;
  dbms_output.put_line('-------------------------------');

  while(x > 0)
  loop
    x := x - 1;
    dbms_output.put_line(x);
  end loop;
  dbms_output.put_line('-------------------------------');
end;

--13. FOR
begin
for k in 1..5
loop
dbms_output.put_line(k);
end loop;
end;

  
  

