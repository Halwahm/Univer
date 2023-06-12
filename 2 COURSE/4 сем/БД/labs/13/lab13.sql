--1. local procedure 
----- List of teachers from pulpit
--drop procedure GET_TEACHERS;
create or replace procedure get_teachers(pcode teacher.pulpit%type) is
begin
  for rec in (select * from teacher where pulpit = pcode) 
  loop
    dbms_output.put_line(rec.teacher_name);
  end loop;
exception
    when others then dbms_output.put_line(sqlerrm);
end;

begin
  get_teachers('ISiT');
end;


--2. number of teachers from X pulpit
--drop function get_num_teachers
create or replace function get_num_teachers (pcode teacher.pulpit%type)
return number is res int;
begin
  select count(*) into res from teacher where pulpit = pcode;
  return res;
exception
    when others then dbms_output.put_line(sqlerrm);
end;

select get_num_teachers ('ISiT') from dual;

--3. 
--proc: get listof teachers from X faculty 
--drop procedure get_teachers
create or replace procedure get_teachers(fcode faculty.faculty%type) is
begin
  for rec in (select teacher_name from teacher t
                                  join pulpit p 
                                  on t.pulpit = p.pulpit
                                  where p.faculty = fcode) 
  loop
    dbms_output.put_line(rec.teacher_name);
  end loop;
exception
    when others then dbms_output.put_line(sqlerrm);
end;

begin
  get_teachers('TOV');
end;

--get list of subjects from pulpit
--drop procedure get_subjects;
create or replace procedure get_subjects(fcode faculty.faculty%type) is
begin
  for rec in (select subject_name from subject) 
  loop
    dbms_output.put_line(rec.subject_name);
  end loop;
exception
    when others then dbms_output.put_line(sqlerrm);
end;

begin
  get_subjects('ISiT');
end;

--4. number of teaches from faculty
--drop function get_num_teachers;
create or replace function get_num_teachers(fcode faculty.faculty%type)
return number is res int;
begin
  select count(*) into res from teacher t
                           join pulpit p on t.pulpit = p.pulpit
                           where p.faculty = fcode;
  return res;
exception
    when others then dbms_output.put_line(sqlerrm);
end;

select get_num_teachers('TOV') from dual;

--func: number of subjects from pulpit
--drop function get_num_subjects;
create or replace function get_num_subjects(pcode subject.pulpit%type)
return number is res int;
begin
  select count(*) into res from subject where pulpit = pcode;
  return res;
exception
    when others then dbms_output.put_line(sqlerrm);
end;

select get_num_subjects('ISiT') from dual;

--5. 
create or replace package teachers is
  procedure get_teachers(fcode faculty.faculty%type);
  procedure get_subjects(pcode subject.pulpit%type);
  function get_num_teachers(fcode faculty.faculty%type) return number;
  function get_num_subjects(pcode subject.pulpit%type) return number;
end teachers;

create or replace package body teachers is
  procedure get_teachers(fcode faculty.faculty%type) is
    begin
      for rec in (select t.teacher_name from teacher t join pulpit p on t.pulpit = p.pulpit 
      where p.faculty = fcode) loop
        dbms_output.put_line(rec.teacher_name);
      end loop;
    exception
        when others then dbms_output.put_line(sqlerrm);
    end;

  procedure get_subjects(pcode subject.pulpit%type) is
    begin
      for rec in (select subject from subject where pulpit = pcode) loop
        dbms_output.put_line(rec.subject);
      end loop;
    exception
        when others then dbms_output.put_line(sqlerrm);
    end;
    
  function  get_num_teachers(fcode faculty.faculty%type)
  return number is res int;
    begin
      select count(*) into res 
        from teacher t
        join pulpit p on t.pulpit = p.pulpit
        where p.faculty = fcode;
      return res;
    exception
        when others then dbms_output.put_line(sqlerrm);
    end;

  function get_num_subjects(pcode subject.pulpit%type)
  return number is res int;
    begin
      select count(*) into res from subject where pulpit = pcode;
      return res;
    exception
        when others then dbms_output.put_line(sqlerrm);
    end;
end teachers;

--drop package teachers;

--6. 
begin 
  teachers.get_subjects('ISiT');
end;





 

