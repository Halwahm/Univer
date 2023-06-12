use Halaleenko_laba4

---FACYLTY
insert into FACULTY   (FACULTY,   FACULTY_NAME ) 
            values  ('����',   '���������� ���������� � �������'); 
insert into FACULTY   (FACULTY,   FACULTY_NAME ) 
            values  ('���',     '����������������� ���������'); 
insert into FACULTY   (FACULTY,   FACULTY_NAME ) 
            values  ('���',     '���������-������������� ���������'); 
insert into FACULTY   (FACULTY,   FACULTY_NAME ) 
            values  ('����',    '���������� � ������� ������ ��������������'); 
insert into FACULTY   (FACULTY,   FACULTY_NAME ) 
            values  ('���',     '���������� ������������ �������'); 
insert into FACULTY   (FACULTY,   FACULTY_NAME ) 
            values  ('��',     '��������� �������������� ����������');   

---PROFESSION
 insert into PROFESSION(FACULTY, PROFESSION, PROFESSION_NAME, QUALIFICATION)    values    ('��',  '1-40 01 02',   '�������������� ������� � ����������', '�������-�����������-�������������' ); 
 insert into PROFESSION(FACULTY, PROFESSION, PROFESSION_NAME, QUALIFICATION)    values    ('��',  '1-47 01 01', '������������ ����', '��������-��������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,  PROFESSION_NAME, QUALIFICATION)    values    ('��',  '1-36 06 01',  '��������������� ������������ � ������� ��������� ����������', '�������-��������������' );                      
 insert into PROFESSION(FACULTY, PROFESSION,  PROFESSION_NAME, QUALIFICATION)  values    ('����',  '1-36 01 08',    '��������������� � ������������ ������� �� �������������� ����������', '�������-�������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,  PROFESSION_NAME, QUALIFICATION)      values    ('����',  '1-36 07 01',  '������ � �������� ���������� ����������� � ����������� ������������ ����������', '�������-�������' ); 
 insert into PROFESSION(FACULTY, PROFESSION, PROFESSION_NAME, QUALIFICATION)  values    ('���',  '1-75 01 01',      '������ ���������', '������� ������� ���������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,  PROFESSION_NAME, QUALIFICATION)   values    ('���',  '1-75 02 01',   '������-�������� �������������', '������� ������-��������� �������������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,     PROFESSION_NAME, QUALIFICATION)   values    ('���',  '1-89 02 02',     '������ � ������������������', '���������� � ����� �������' ); 
 insert into PROFESSION(FACULTY, PROFESSION, PROFESSION_NAME, QUALIFICATION)  values    ('���',  '1-25 01 07',  '��������� � ���������� �� �����������', '���������-��������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,  PROFESSION_NAME, QUALIFICATION)      values    ('���',  '1-25 01 08',    '������������� ����, ������ � �����', '���������' );                       
 insert into PROFESSION(FACULTY, PROFESSION,     PROFESSION_NAME, QUALIFICATION)  values    ('����',  '1-36 05 01',   '������ � ������������ ������� ���������', '�������-�������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,   PROFESSION_NAME, QUALIFICATION)   values    ('����',  '1-46 01 01',      '�������������� ����', '�������-��������' ); 
 insert into PROFESSION(FACULTY, PROFESSION,     PROFESSION_NAME, QUALIFICATION)      values    ('���',  '1-48 01 02',  '���������� ���������� ������������ �������, ���������� � �������', '�������-�����-��������' );                 
 insert into PROFESSION(FACULTY, PROFESSION,   PROFESSION_NAME, QUALIFICATION)    values    ('���',  '1-48 01 05',    '���������� ���������� ����������� ���������', '�������-�����-��������' );  
 insert into PROFESSION(FACULTY, PROFESSION,    PROFESSION_NAME, QUALIFICATION)  values    ('���',  '1-54 01 03',   '������-���������� ������ � ������� �������� �������� ���������', '������� �� ������������' );

 ---GROUPS
 insert into GROUPS   (FACULTY,  PROFESSION, YEAR_FIRST ) 
         values ('����','1-36 01 08', 2013),---12 ��                                                   
                ('����','1-36 01 08', 2012), 
                ('����','1-36 07 01', 2011), 
                ('����','1-36 07 01', 2010), 
                ('���','1-48 01 02', 2012), ---16 ��  
                ('���','1-48 01 02', 2011), 
                ('���','1-48 01 05', 2013), 
                ('���','1-54 01 03', 2012), 
                ('���','1-75 01 01', 2013),--20 ��       
                ('���','1-75 02 01', 2012), 
                ('���','1-75 02 01', 2011), 
                ('���','1-89 02 02', 2012), 
                ('���','1-89 02 02', 2011),   
                ('����','1-36 05 01', 2013), 
                ('����','1-36 05 01', 2012), 
                ('����','1-46 01 01', 2012),--27 �� 
                ('���','1-25 01 07', 2013),  
                ('���','1-25 01 07', 2012),      
                ('���','1-25 01 07', 2010), 
                ('���','1-25 01 08', 2013), 
                ('���','1-25 01 08', 2012) ---32 ��  

---STUDENT
insert into STUDENT (IDGROUP,NAME, BDAY) 
    values (2, '����� ������� ��������',         '12.07.1994'), 
           (2, '������� �������� ����������',    '06.03.1994'), 
           (2, '�������� ����� �����������',     '09.11.1994'), 
           (2, '������� ����� ���������',        '04.10.1994'), 
           (2, '��������� ��������� ����������', '08.01.1994'), 
           (3, '������� ������ ���������',       '02.08.1993'), 
           (3, '������� ��� ����������',         '07.12.1993'), 
           (3, '������� ����� �����������',      '02.12.1993'), 
           (4, '������� ������ �����������',     '08.03.1992'), 
           (4, '������� ����� �������������',    '02.06.1992'), 
           (4, '�������� ����� �����������',     '11.12.1992'), 
           (4, '�������� ������� �������������', '11.05.1992'), 
           (4, '����������� ������� ��������',   '09.11.1992'), 
           (4, '�������� ������� ����������',    '01.11.1992'), 
           (5, '�������� ����� ������������',    '08.07.1995'), 
           (5, '������ ������� ����������',      '02.11.1995'), 
           (5, '������ ��������� �����������',   '07.05.1995'), 
           (5, '����� ��������� ���������',      '04.08.1995'), 
           (6, '���������� ����� ����������',    '08.11.1994'), 
           (6, '�������� ������ ��������',       '02.03.1994'), 
           (6, '���������� ����� ����������',    '04.06.1994'), 
           (6, '��������� ���������� ���������', '09.11.1994'), 
           (6, '����� ��������� �������',        '04.07.1994'), 
           (7, '����������� ����� ������������', '03.01.1993'), 
           (7, '������� ���� ��������',          '12.09.1993'), 
           (7, '��������� ������ ��������',      '12.06.1993'), 
           (7, '���������� ��������� ����������','09.02.1993'), 
           (7, '������� ������ ���������',       '04.07.1993'), 
           (8, '������ ������� ���������',       '08.01.1992'), 
           (8, '��������� ����� ����������',     '12.05.1992'), 
           (8, '�������� ����� ����������',      '08.11.1992'), 
           (8, '������� ������� ���������',      '12.03.1992'), 
           (9, '�������� ����� �������������',   '10.08.1995'), 
           (9, '���������� ������ ��������',     '02.05.1995'), 
           (9, '������ ������� �������������',   '08.01.1995'), 
           (9, '��������� ��������� ��������',   '11.09.1995'), 
           (10, '������ ������� ������������',   '08.01.1994'), 
           (10, '������ ������ ����������',      '11.09.1994'), 
           (10, '����� ���� �������������',      '06.04.1994'), 
           (10, '������� ������ ����������',     '12.08.1994'),
		   (11, '��������� ��������� ����������','07.11.1993'), 
           (11, '������ ������� ����������',     '04.06.1993'), 
           (11, '������� ����� ����������',      '10.12.1993'), 
           (11, '������� ������ ����������',     '04.07.1993'), 
           (11, '������� ����� ���������',       '08.01.1993'), 
           (11, '����� ������� ����������',      '02.09.1993'), 
           (12, '���� ������ �����������',       '11.12.1995'), 
           (12, '������� ���� �������������',    '10.06.1995'), 
           (12, '��������� ���� ���������',      '09.08.1995'), 
           (12, '����� ����� ���������',         '04.07.1995'), 
           (12, '��������� ������ ����������',   '08.03.1995'), 
           (12, '����� ����� ��������',          '12.09.1995'), 
           (13, '������ ����� ������������',     '08.10.1994'), 
           (13, '���������� ����� ����������',   '10.02.1994'), 
           (13, '�������� ������� �������������','11.11.1994'), 
           (13, '���������� ����� ����������',   '10.02.1994'), 
           (13, '����������� ����� ��������',    '12.01.1994'), 
           (14, '�������� ������� �������������','11.09.1993'), 
           (14, '������ �������� ����������',    '01.12.1993'), 
           (14, '���� ������� ����������',       '09.06.1993'), 
           (14, '�������� ���������� ����������','05.01.1993'), 
           (14, '����������� ����� ����������',  '01.07.1993'), 
           (15, '������� ��������� ���������',   '07.04.1992'), 
           (15, '������ �������� ���������',     '10.12.1992'), 
           (15, '��������� ����� ����������',    '05.05.1992'), 
           (15, '���������� ����� ������������', '11.01.1992'), 
           (15, '�������� ����� ����������',     '04.06.1992'), 
           (16, '����� ����� ����������',        '08.01.1994'), 
           (16, '��������� ��������� ���������', '07.02.1994'), 
           (16, '������ ������ �����������',     '12.06.1994'), 
           (16, '������� ����� ��������',        '03.07.1994'), 
           (16, '������ ������ ���������',       '04.07.1994'), 
           (17, '������� ��������� ����������',  '08.11.1993'), 
           (17, '������ ����� ����������',       '02.04.1993'), 
           (17, '������ ���� ��������',          '03.06.1993'), 
           (17, '������� ������ ���`������',      '05.11.1993'), 
           (17, '������ ������ �������������',   '03.07.1993'), 
           (18, '��������� ����� ��������',      '08.01.1995'), 
           (18, '���������� ��������� ���������','06.09.1995'), 
           (18, '�������� ��������� ����������', '08.03.1995'), 
           (18, '��������� ����� ��������',      '07.08.1995') 

---PULPIT
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY ) 
  values  ('����', '�������������� ������ � ���������� ','��'  ) 
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
    values  ('��', '�����������','���')           
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
   values  ('��', '��������������','���')            
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
  values  ('�����', '���������� � ����������������','���')                 
insert into PULPIT   (PULPIT,  PULPIT_NAME, FACULTY) 
   values  ('����', '������ ������� � ������������','���')  
insert into PULPIT   (PULPIT,  PULPIT_NAME, FACULTY) 
   values  ('���', '������� � ������������������','���')               
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
   values  ('������','������������ �������������� � ������-��������� �������������','���')           
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
   values  ('��', '���������� ����', '����')                           
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
   values  ('�����','������ ����� � ���������� �������������','����')   
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
   values  ('���','���������� �������������������� �����������', '����')    
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
values  ('�����','���������� � ������� ������� �� ���������','����')     
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
values  ('��', '������������ �����','���')  
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
 values  ('���','���������� ����������� ���������','���')              
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
 values  ('�������','���������� �������������� ������� � ����� ���������� ���������� ','����')  
insert into PULPIT   (PULPIT, PULPIT_NAME, FACULTY) 
    values  ('�����','��������� � ��������� ���������� �����������','����')                                                
insert into PULPIT   (PULPIT,    PULPIT_NAME, FACULTY) 
values  ('����',    '������������� ������ � ����������','���')    
insert into PULPIT   (PULPIT,    PULPIT_NAME, FACULTY) 
  values  ('����',   '����������� � ��������� ������������������','���')    
insert into PULPIT   (PULPIT,    PULPIT_NAME, FACULTY) 
   values  ('������', '����������, �������������� �����, ������� � ������', '���')     

---TEACHER
insert into  TEACHER    (TEACHER,   TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('����',    '������ �������� �������������', '�',  '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('�����',    '�������� ��������� ��������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('�����',    '���������� ������� ����������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('�����',    '�������� ������ ��������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('���',     '����� ��������� ����������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('���',     '��������� ����� ��������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                      values  ('���',     '����� ������� ��������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('���',     '����� ������� �������������',  '�', '����');                      
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('���',     '����� ����� �������������',  '�',   '����');                        
insert into  TEACHER    (TEACHER,  TEACHER_NAME,GENDER, PULPIT ) 
                       values  ('������',   '����������� ��������� ��������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('����',   '������� ��������� ����������', '�', '����'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('����',   '������ ������ ��������', '�', '��'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('����', '������� ������ ����������',  '�',  '������'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('���',     '���������� ������� ��������', '�', '������'); 
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('���',   '������ ������ ���������� ', '�', '��');                       
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('�����',   '��������� �������� ���������', '�', '�����');  
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('������',   '���������� �������� ����������', '�', '��');  
insert into  TEACHER    (TEACHER,  TEACHER_NAME, GENDER, PULPIT ) 
                       values  ('�����',   '�������� ������ ����������', '�', '��');

---SUBJECT
 insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT ) 
                       values ('����',   '������� ���������� ������ ������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT) 
                       values ('��',     '���� ������','����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('���',    '�������������� ����������','����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('����',  '������ �������������� � ����������������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('��',     '������������� ������ � ������������ ��������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('���',    '���������������� ������� ����������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('����',  '������������� ������ ��������� ����������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('���',     '�������������� �������������� ������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('��',      '������������ ��������� ','����');  
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,  PULPIT ) 
                       values ('���',     '������������ �������������� �������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT) 
                       values ('��',   '���������� ����������', '����'); 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,PULPIT ) 
                      values ('��',   '�������������� ����������������','����');   
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT ) 
               values ('����', '���������� ������ ���',  '����');                    
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,PULPIT ) 
               values ('���',  '��������-��������������� ����������������', '����');  
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT ) 
                       values ('��', '������������� ������','����') 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT ) 
                       values ('�������','������ ������-��������� � ������������� �����-����',  '������') 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,PULPIT ) 
                       values ('��', '���������� �������� ','��') 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,PULPIT ) 
                       values ('��',    '�����������', '�����')  
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT ) 
                       values ('��',    '������������ �����', '��')     
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME, PULPIT ) 
                       values ('���',    '������ ��������� ����','��') 
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,PULPIT ) 
                       values ('����',   '���������� � ������������ �������������', '�����')  
insert into SUBJECT   (SUBJECT,   SUBJECT_NAME,PULPIT ) 
                       values ('����',   '���������� ���������� �������� ���������� ','�������')     

---PROGRESS
insert into PROGRESS (SUBJECT, IDSTUDENT, PDATE, NOTE) 
    values  ('����', 1001,  '01.10.2013',8), 
           ('����', 1002,  '01.10.2013',7), 
           ('����', 1003,  '01.10.2013',5), 
           ('����', 1005,  '01.10.2013',4) 
insert into PROGRESS (SUBJECT, IDSTUDENT, PDATE, NOTE) 
    values   ('����', 1014,  '01.12.2013',5), 
           ('����', 1015,  '01.12.2013',9), 
           ('����', 1016,  '01.12.2013',5), 
           ('����', 1017,  '01.12.2013',4) 
insert into PROGRESS (SUBJECT, IDSTUDENT, PDATE, NOTE) 
    values ('��',   1018,  '06.5.2013',4), 
           ('��',   1019,  '06.05.2013',7), 
           ('��',   1020,  '06.05.2013',7), 
           ('��',   1021,  '06.05.2013',9), 
           ('��',   1022,  '06.05.2013',5), 
           ('��',   1023,  '06.05.2013',6)

---AUDITORIUM_TYPE
insert into AUDITORIUM_TYPE   (AUDITORIUM_TYPE,  AUDITORIUM_TYPENAME )        values ('��',            '����������');
insert into AUDITORIUM_TYPE   (AUDITORIUM_TYPE,  AUDITORIUM_TYPENAME )         values ('��-�',          '������������ �����');
insert into AUDITORIUM_TYPE   (AUDITORIUM_TYPE, AUDITORIUM_TYPENAME )         values ('��-�',          '���������� � ���. ����������');
insert into AUDITORIUM_TYPE   (AUDITORIUM_TYPE,  AUDITORIUM_TYPENAME )          values  ('��-X',          '���������� �����������');
insert into AUDITORIUM_TYPE   (AUDITORIUM_TYPE, AUDITORIUM_TYPENAME )        values  ('��-��',   '����. ������������ �����');

---AUDITORIUM
insert into  AUDITORIUM  (AUDITORIUM, AUDITORIUM_NAME,   
 AUDITORIUM_TYPE, AUDITORIUM_CAPACITY)    
values  ('206-1', '206-1','��-�', 15); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY)  
values  ('301-1',   '301-1', '��-�', 15); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY )    
values  ('236-1',   '236-1', '��',   60); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY )   
values  ('313-1',   '313-1', '��-�',   60); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY )   
values  ('324-1',   '324-1', '��-�',   50); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY )    
 values  ('413-1',   '413-1', '��-�', 15); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY )  
values  ('423-1',   '423-1', '��-�', 90); 
insert into  AUDITORIUM   (AUDITORIUM,   AUDITORIUM_NAME,  
AUDITORIUM_TYPE, AUDITORIUM_CAPACITY )      
values  ('408-2',   '408-2', '��',  90); 