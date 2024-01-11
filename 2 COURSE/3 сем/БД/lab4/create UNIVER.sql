use Halaleenko_laba4

/*drop table PROGRESS 
drop table STUDENT 
drop table GROUPS 
drop table SUBJECT 
drop table TEACHER 
drop table  PULPIT 
drop table PROFESSION 
drop table FACULTY 
drop table AUDITORIUM  
drop table AUDITORIUM_TYPE*/

create table AUDITORIUM_TYPE 
(    AUDITORIUM_TYPE  char(10) constraint AUDITORIUM_TYPE_PK  primary key,  
      AUDITORIUM_TYPENAME  varchar(30)       
)

  create table AUDITORIUM  
(   AUDITORIUM   char(20)  constraint AUDITORIUM_PK  primary key,          
    AUDITORIUM_TYPE char(10) constraint  AUDITORIUM_AUDITORIUM_TYPE_FK foreign key          
                      references AUDITORIUM_TYPE(AUDITORIUM_TYPE),  
   AUDITORIUM_CAPACITY  integer constraint  AUDITORIUM_CAPACITY_CHECK default 1  check (AUDITORIUM_CAPACITY between 1 and 300),  -- גלוסעטלמסעü  
   AUDITORIUM_NAME      varchar(50)                                      
)

create table FACULTY 
(    
FACULTY      char(10)   constraint  FACULTY_PK primary key, 
FACULTY_NAME  varchar(50) default '???' 
)

  create table PROFESSION 
  (   PROFESSION   char(20) constraint PROFESSION_PK  primary key, 
       FACULTY    char(10) constraint PROFESSION_FACULTY_FK foreign key  
                            references FACULTY(FACULTY), 
       PROFESSION_NAME varchar(100),    QUALIFICATION   varchar(50)   
  );   

    create table  PULPIT  
(   PULPIT   char(20)  constraint PULPIT_PK  primary key, 
    PULPIT_NAME  varchar(100),  
    FACULTY   char(10)   constraint PULPIT_FACULTY_FK foreign key  
                         references FACULTY(FACULTY)  
);   

 create table TEACHER 
 (   TEACHER    char(10)  constraint TEACHER_PK  primary key, 
     TEACHER_NAME  varchar(100),  
     GENDER     char(1) CHECK (GENDER in ('ל', 'ז')), 
     PULPIT   char(20) constraint TEACHER_PULPIT_FK foreign key  
                         references PULPIT(PULPIT)  
 ); 

 create table SUBJECT 
    (     SUBJECT  char(10) constraint SUBJECT_PK  primary key,  
           SUBJECT_NAME varchar(100) unique, 
           PULPIT  char(20) constraint SUBJECT_PULPIT_FK foreign key  
                         references PULPIT(PULPIT)    
     ); 

	 create table GROUPS  
(   IDGROUP  integer  identity(1,1) constraint GROUP_PK  primary key,               
    FACULTY   char(10) constraint  GROUPS_FACULTY_FK foreign key          
                                                         references FACULTY(FACULTY),  
     PROFESSION  char(20) constraint  GROUPS_PROFESSION_FK foreign key          
                                                         references PROFESSION(PROFESSION), 
    YEAR_FIRST  smallint  check (YEAR_FIRST<=YEAR(GETDATE())),                   
  ); 

  create table STUDENT  
(    IDSTUDENT   integer  identity(1000,1) constraint STUDENT_PK  primary key, 
      IDGROUP   integer  constraint STUDENT_GROUP_FK foreign key          
                      references GROUPS(IDGROUP),         
      NAME   nvarchar(100),  
      BDAY   date, 
      STAMP  timestamp, 
      INFO     xml, 
      FOTO     varbinary 
 ); 

 create table PROGRESS 
 (  SUBJECT   char(10) constraint PROGRESS_SUBJECT_FK foreign key 
                      references SUBJECT(SUBJECT),                 
     IDSTUDENT integer  constraint PROGRESS_IDSTUDENT_FK foreign key          
                      references STUDENT(IDSTUDENT),         
     PDATE    date,  
     NOTE     integer check (NOTE between 1 and 10) 
  ); 