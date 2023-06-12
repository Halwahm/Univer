--set serveroutput on 
---------------------------------------------------------------Implicit cursors---------
--1. select into
declare
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec 
            from faculty
            where faculty = 'TOV';
  dbms_output.put_line(faculty_rec.faculty ||' '||faculty_rec.faculty_name);
end;


--2.
declare
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec 
            from faculty
            where faculty = 'IT';
  dbms_output.put_line(faculty_rec.faculty ||' '||faculty_rec.faculty_name);
exception
  when others
    then dbms_output.put_line('Error msg: ' || sqlerrm || 'Error code: ' || sqlcode);
end;


--3. too_many_rows
declare
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec 
            from faculty;
  dbms_output.put_line(faculty_rec.faculty ||' '||faculty_rec.faculty_name);
exception
  when too_many_rows
    then dbms_output.put_line('Result consists of many rows (ORA ' ||sqlerrm|| ')');
end;


--4. no_data_found
declare
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec 
            from faculty
            where faculty = 'IT';
  dbms_output.put_line(faculty_rec.faculty ||' '||faculty_rec.faculty_name);
exception
  when no_data_found
    then dbms_output.put_line('No data found (ORA ' ||sqlerrm|| ')');
end;


--5. update with commit/rollback
--select * from auditorium;
declare
    is_found boolean;
    is_open boolean;
    is_notfound boolean;
    rowcount pls_integer;
begin
    update auditorium 
        set auditorium = '318-1',
            auditorium_name = '318-1', 
            auditorium_capacity = 90, 
            auditorium_type = 'LK'
        where auditorium = '132-4';
rollback;
    is_found := sql%found;
    is_open := sql%isopen;
    is_notfound := sql%notfound;
    rowcount := sql%rowcount;
    if is_found 
        then dbms_output.put_line('is_found = true');
        else dbms_output.put_line('is_found = false');
    end if;
    if is_open 
        then dbms_output.put_line('is_open = true');
        else dbms_output.put_line('is_open = false');
    end if;
    if is_notfound 
        then dbms_output.put_line('is_notfound = true');
        else dbms_output.put_line('is_notfound = false');
    end if;
    dbms_output.put_line('rowcount = ' || rowcount);
    --rollback;
    --commit
    exception
        when others
            then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

-- update with error--1: ORA-00001: unique constraint (SYS.SYS_C009874) violated
declare
    is_found boolean;
    is_open boolean;
    is_notfound boolean;
    rowcount pls_integer;
begin
    update auditorium 
        set auditorium = '408-2',
            auditorium_name = '408-2', 
            auditorium_capacity = 90, 
            auditorium_type = 'LK'
        where auditorium = '132-4';
    --rollback;
    is_found := sql%found;
    is_open := sql%isopen;
    is_notfound := sql%notfound;
    rowcount := sql%rowcount;
    if is_found 
        then dbms_output.put_line('is_found = true');
        else dbms_output.put_line('is_found = false');
    end if;
    if is_open 
        then dbms_output.put_line('is_open = true');
        else dbms_output.put_line('is_open = false');
    end if;
    if is_notfound 
        then dbms_output.put_line('is_notfound = true');
        else dbms_output.put_line('is_notfound = false');
    end if;
    dbms_output.put_line('rowcount = ' || rowcount);
    rollback;
    --commit
    exception
        when others
            then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

-- insert commit/rollback
declare
    is_found boolean;
    is_open boolean;
    is_notfound boolean;
    rowcount pls_integer;
begin
insert into auditorium(auditorium, auditorium_name, auditorium_capacity, auditorium_type)
  values ('302-1', '302-1', 90, 'LK');
    is_found := sql%found;
    is_open := sql%isopen;
    is_notfound := sql%notfound;
    rowcount := sql%rowcount;
    if is_found 
        then dbms_output.put_line('is_found = true');
        else dbms_output.put_line('is_found = false');
    end if;
    if is_open 
        then dbms_output.put_line('is_open = true');
        else dbms_output.put_line('is_open = false');
    end if;
    if is_notfound 
        then dbms_output.put_line('is_notfound = true');
        else dbms_output.put_line('is_notfound = false');
    end if;
    dbms_output.put_line('rowcount = ' || rowcount);
    rollback;
    --commit
    exception
        when others
            then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

-- insert with error--1: ORA-00001: unique constraint (SYS.SYS_C009874) violated
declare
    is_found boolean;
    is_open boolean;
    is_notfound boolean;
    rowcount pls_integer;
begin
insert into auditorium(auditorium, auditorium_name, auditorium_capacity, auditorium_type)
  values ('301-1', '301-1', 90, 'LK');
    is_found := sql%found;
    is_open := sql%isopen;
    is_notfound := sql%notfound;
    rowcount := sql%rowcount;
    if is_found 
        then dbms_output.put_line('is_found = true');
        else dbms_output.put_line('is_found = false');
    end if;
    if is_open 
        then dbms_output.put_line('is_open = true');
        else dbms_output.put_line('is_open = false');
    end if;
    if is_notfound 
        then dbms_output.put_line('is_notfound = true');
        else dbms_output.put_line('is_notfound = false');
    end if;
    dbms_output.put_line('rowcount = ' || rowcount);
    rollback;
    --commit
    exception
        when others
            then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

-- delete with commit/rollback
declare
    is_found boolean;
    is_open boolean;
    is_notfound boolean;
    rowcount pls_integer;
begin
delete auditorium where auditorium = '314-4';
    is_found := sql%found;
    is_open := sql%isopen;
    is_notfound := sql%notfound;
    rowcount := sql%rowcount;
    if is_found 
        then dbms_output.put_line('is_found = true');
        else dbms_output.put_line('is_found = false');
    end if;
    if is_open 
        then dbms_output.put_line('is_open = true');
        else dbms_output.put_line('is_open = false');
    end if;
    if is_notfound 
        then dbms_output.put_line('is_notfound = true');
        else dbms_output.put_line('is_notfound = false');
    end if;
    dbms_output.put_line('rowcount = ' || rowcount);
    rollback;
    --commit
    exception
        when others
            then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

-- delete with exception
declare
    is_found boolean;
    is_open boolean;
    is_notfound boolean;
    rowcount pls_integer;
begin
delete auditorium where auditorium = '301-4';
    is_found := sql%found;
    is_open := sql%isopen;
    is_notfound := sql%notfound;
    rowcount := sql%rowcount;
    if is_found 
        then dbms_output.put_line('is_found = true');
        else dbms_output.put_line('is_found = false');
    end if;
    if is_open 
        then dbms_output.put_line('is_open = true');
        else dbms_output.put_line('is_open = false');
    end if;
    if is_notfound 
        then dbms_output.put_line('is_notfound = true');
        else dbms_output.put_line('is_notfound = false');
    end if;
    dbms_output.put_line('rowcount = ' || rowcount);
    rollback;
    --commit
    exception
        when others
            then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

------------------------------------------------------------Explicit cursors-----
--6. get list of teachers with explicit cursor and %type variables
declare
    cursor teacher_cur is select teacher, teacher_name, pulpit from teacher;
    c_teacher teacher.teacher%type;
    c_teacher_name teacher.teacher_name%type;
    c_pulput teacher.pulpit%type;
begin
    dbms_output.put_line('TEACHER    TEACHER_NAME                                       PULPIT ');
    dbms_output.put_line('---------- -----------------------------------------------------------');
    open teacher_cur;
    loop
    fetch teacher_cur into c_teacher, c_teacher_name, c_pulput;
    exit when teacher_cur%notfound;
    dbms_output.put_line(rpad(c_teacher, 10) || ' ' || rpad(c_teacher_name, 50) || ' ' || rpad(c_pulput, 20));
  end loop;
  close teacher_cur;
  
  exception
      when others
      then dbms_output.put_line('error-' || sqlcode || ': ' || sqlerrm);
end;

--7.
declare
    cursor subject_cur is select * from subject;
    c_subject subject%rowtype;
begin
    dbms_output.put_line('SUBJECT    SUBJECT_NAME                                      PULPIT');
    dbms_output.put_line('---------- -------------------------------------------       -------');
    open subject_cur;
    fetch subject_cur into c_subject;
    while subject_cur%found
    loop
        dbms_output.put_line(rpad(c_subject.subject, 10) || ' ' || rpad(c_subject.subject_name, 50) || ' ' || rpad(c_subject.pulpit, 10));
        fetch subject_cur into c_subject;
    end loop;
    close subject_cur;
end;


--8.
declare
    cursor audience_selection (min_bound auditorium.auditorium_capacity%type, max_bound auditorium.auditorium_capacity%type)
        is select * 
            from auditorium
            where auditorium_capacity between min_bound and max_bound;
    c_auditorium auditorium%rowtype;
begin
    dbms_output.put_line('<-----AUDITORIUMS CAPACITY LESS THAN 20----->');
    dbms_output.put_line('AUDITORIUM           AUDITORIUM_TYPE AUDITORIUM_CAPACITY AUDITORIUM_NAME');
    dbms_output.put_line('-------------------- --------------- ------------------- ---------------');
    open audience_selection(0, 20);
    loop                                                                        --exit when audience_selection%notfound;
        fetch audience_selection into c_auditorium;
        exit when audience_selection%notfound;
        dbms_output.put_line(rpad(c_auditorium.auditorium, 21) || rpad(c_auditorium.auditorium_type, 16) || rpad(c_auditorium.auditorium_capacity, 20) || rpad(c_auditorium.auditorium_name, 15));
    end loop;
    close audience_selection;
    
    dbms_output.put_line('');
    dbms_output.put_line('');
    
    dbms_output.put_line('<-----AUDITORIUMS CAPACITY BETWEEN 20 AND 30----->');
    dbms_output.put_line('AUDITORIUM           AUDITORIUM_TYPE AUDITORIUM_CAPACITY AUDITORIUM_NAME');
    dbms_output.put_line('-------------------- --------------- ------------------- ---------------');
    open audience_selection(20, 30);
    fetch audience_selection into c_auditorium;
    while audience_selection%notfound                                         --use WHILE audience_selection%notfound 
    loop
        dbms_output.put_line(rpad(c_auditorium.auditorium, 21) || rpad(c_auditorium.auditorium_type, 16) || rpad(c_auditorium.auditorium_capacity, 20) || rpad(c_auditorium.auditorium_name, 15));
        fetch audience_selection into c_auditorium;
    end loop;
    close audience_selection;
    
    dbms_output.put_line('');
    dbms_output.put_line('');
    
    dbms_output.put_line('<-----AUDITORIUMS CAPACITY BETWEEN 30 AND 60----->');
    dbms_output.put_line('AUDITORIUM           AUDITORIUM_TYPE AUDITORIUM_CAPACITY AUDITORIUM_NAME');
    dbms_output.put_line('-------------------- --------------- ------------------- ---------------');
    for c_auditorium in audience_selection(30, 60)                          --use FOR c_auditorium in audience_selection(30, 60)  
    loop
        dbms_output.put_line(rpad(c_auditorium.auditorium, 21) || rpad(c_auditorium.auditorium_type, 16) || rpad(c_auditorium.auditorium_capacity, 20) || rpad(c_auditorium.auditorium_name, 15));
    end loop;
    
    dbms_output.put_line('');
    dbms_output.put_line('');
    
    dbms_output.put_line('<-----AUDITORIUMS CAPACITY BETWEEN 60 AND 80----->');
    dbms_output.put_line('AUDITORIUM           AUDITORIUM_TYPE AUDITORIUM_CAPACITY AUDITORIUM_NAME');
    dbms_output.put_line('-------------------- --------------- ------------------- ---------------');
    for c_auditorium in audience_selection(60, 80)
    loop                                                                          ---------use FOR
        dbms_output.put_line(rpad(c_auditorium.auditorium, 21) || rpad(c_auditorium.auditorium_type, 16) || rpad(c_auditorium.auditorium_capacity, 20) || rpad(c_auditorium.auditorium_name, 15));
    end loop;
    
    dbms_output.put_line('');
    dbms_output.put_line('');
    
    dbms_output.put_line('<-----AUDITORIUMS CAPACITY MORE THAN 80----->');
    dbms_output.put_line('AUDITORIUM           AUDITORIUM_TYPE AUDITORIUM_CAPACITY AUDITORIUM_NAME');
    dbms_output.put_line('-------------------- --------------- ------------------- ---------------');
    for c_auditorium in audience_selection(80, 100)                               -------use FOR
    loop
        dbms_output.put_line(rpad(c_auditorium.auditorium, 21) || rpad(c_auditorium.auditorium_type, 16) || rpad(c_auditorium.auditorium_capacity, 20) || rpad(c_auditorium.auditorium_name, 15));
    end loop;
end;

--9. refcursor
declare
    type t_faculty is ref cursor;
    cur_faculty t_faculty;
    d_faculty faculty.faculty%type;
begin
    open cur_faculty for select faculty from faculty;
    loop
        fetch cur_faculty into d_faculty;
        exit when cur_faculty%notfound;
        dbms_output.put_line(d_faculty);
    end loop;
    close cur_faculty;
end;


--10. reduction of all the capacity of all auditoriums, with a capacity of 40-80 by 10%
declare
    cursor c_auditorum (min_bound auditorium.auditorium_capacity%type, max_bound auditorium.auditorium_capacity%type)
        is select auditorium_capacity 
            from auditorium
            where auditorium_capacity between min_bound and max_bound
            for update;
begin
    for aum_capacity in c_auditorum(40, 80)
    loop
        update auditorium set auditorium_capacity = auditorium_capacity * 0.9 where current of c_auditorum;
    end loop;
    rollback;
end;

