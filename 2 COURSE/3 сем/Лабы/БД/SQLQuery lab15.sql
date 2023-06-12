use Halaleenko_laba4;

-- 1
select TEACHER.TEACHER[Код_преподавателя], TEACHER.TEACHER_NAME[Имя_преподавателя],TEACHER.GENDER[Пол], TEACHER.PULPIT[Кафедра] 
	from TEACHER 
		where  TEACHER.PULPIT = 'ИСиТ'
	for xml path('TEACHER'), 
	root('Преподаватели_кафедры_ИСиТ'), elements;
go



-- 2
select a.AUDITORIUM_NAME, at.AUDITORIUM_TYPENAME, a.AUDITORIUM_CAPACITY
		from AUDITORIUM a 
		Inner Join AUDITORIUM_TYPE at on at.AUDITORIUM_TYPE=a.AUDITORIUM_TYPE
			where a.AUDITORIUM_TYPE='ЛК' 
for xml auto, 
root('Лекционные_аудитории'), elements;
go 



-- 3 
begin tran
declare @h int = 0,
      @xml varchar(2000) = '<?xml version="1.0" encoding="windows-1251" ?>
							<SUBJECTS> 
								<SUBJECT SUBJECT="РПР" SUBJECT_NAME="Разработка программных роботов" PULPIT="ИСиТ" /> 
								<SUBJECT SUBJECT="ИГИГ" SUBJECT_NAME="Инженерная геометрия и графика" PULPIT="ТЛ" /> 
								<SUBJECT SUBJECT="ПГИГ" SUBJECT_NAME="Полиграфическая геометрия и графика" PULPIT="ТиП"  />  
							</SUBJECTS>'

exec sp_xml_preparedocument @h output, @xml;
select * from openxml(@h, '/SUBJECTS/SUBJECT', 0)
	with(SUBJECT char(10), SUBJECT_NAME varchar(100), PULPIT char(20))    

insert into SUBJECT select * from openxml(@h, '/SUBJECTS/SUBJECT', 0)
	with(SUBJECT char(10), SUBJECT_NAME varchar(100), PULPIT char(20)) 

select * from SUBJECT where SUBJECT LIKE '%ИГ'

exec sp_xml_removedocument @h          

rollback 

--select * from SUBJECT
go



-- 4
create table Students
(
	STUDENT nvarchar(100) primary key ,
	PasportData xml
);
 
insert into Students 
values ('Манакова Анастасия Владимировна',
		'<Pasport>
			<Sereal>MP</Sereal>
				<Number>22223333</Number>
				<PersonalNumber>124124124</PersonalNumber>
				<Date>15/05/2015</Date>
				<Addres>ул.Первомайская, д.110</Addres>
		</Pasport>'),
	   ('Махно Нестр Петрович',
		'<Pasport>
			<Sereal>MP</Sereal>
			<Number>1234555</Number>
			<PersonalNumber>9412412</PersonalNumber>
			<Date>01/04/2014</Date>
			<Addres>ул.Свердлова, д.53</Addres>
		</Pasport>')

 select Students.STUDENT,
		PasportData.value('(/Pasport/Sereal)[1]','varchar(5)')[Серия паспорта],
		PasportData.value('(/Pasport/Number)[1]','int')[Номер паспорта],
		PasportData.value('(/Pasport/PersonalNumber)[1]','varchar(100)')[Личный номер],
		PasportData.value('(/Pasport/Date)[1]','date')[Дата выдачи],
		PasportData.value('(/Pasport/Addres)[1]','varchar(100)')[Адрес студента],
		PasportData.query('/Pasport') [Паспортные данные]
			from Students;

update Students 
	  set PasportData = '<Pasport>
							<Sereal>MM</Sereal>
							<Number>55666777</Number>
							<PersonalNumber>123456</PersonalNumber>
							<Date>16/06/2015</Date>
							<Addres>ул.Свердлова, д.53</Addres>
						</Pasport>'
				where PasportData.value('(/Pasport/Number)[1]','int')=1234555

  select Students.STUDENT[Name],
		PasportData.value('(/Pasport/Sereal)[1]','varchar(5)')[Серия паспорта],
		PasportData.value('(/Pasport/Number)[1]','int')[Номер паспорта],
		PasportData.query('/Pasport') [Паспортные данные]
			from Students;



drop table Students
go



-- 5. 
create xml schema collection Studentss as 
N'<?xml version="1.0" encoding="utf-16" ?>
<xs:schema attributeFormDefault="unqualified" 
		elementFormDefault="qualified"
		xmlns:xs="http://www.w3.org/2001/XMLSchema">
	<xs:element name="студент">
	<xs:complexType><xs:sequence>
	<xs:element name="паспорт" maxOccurs="1" minOccurs="1">
	<xs:complexType>
    <xs:attribute name="серия" type="xs:string" use="required" />
    <xs:attribute name="номер" type="xs:unsignedInt" use="required"/>
    <xs:attribute name="дата"  use="required"  >
	<xs:simpleType>  <xs:restriction base ="xs:string">
	<xs:pattern value="[0-9]{2}.[0-9]{2}.[0-9]{4}"/>
	</xs:restriction>	</xs:simpleType>
    </xs:attribute>	</xs:complexType>
	</xs:element>
	<xs:element maxOccurs="3" name="телефон" type="xs:unsignedInt"/>
	<xs:element name="адрес">   <xs:complexType><xs:sequence>
	<xs:element name="страна" type="xs:string" />
    <xs:element name="город" type="xs:string" />
    <xs:element name="улица" type="xs:string" />
    <xs:element name="дом" type="xs:string" />
    <xs:element name="квартира" type="xs:string" />
</xs:sequence></xs:complexType>  </xs:element>
</xs:sequence></xs:complexType>
</xs:element>
</xs:schema>';
go

create table STUDENTSS
( 
	IDSTUDENT integer  identity(1000,1) 
		 constraint STUDENTSS_PK  primary key,
   IDGROUP integer constraint STUDENTSS_GROUP_FK
		 foreign key  references GROUPS(IDGROUP),        
  NAME nvarchar(100), 
  BDAY  date,
  STAMP timestamp,
  INFO     xml(STUDENTSS), 
  FOTO   varbinary
);

--insert into STUDENTSS
--values ('fdsklmb')

drop table STUDENTSS;
drop xml schema collection Studentss
go



--6.
use test;
create table TestXml 
(TestField xml)

insert into TestXml (TestField) values
('<стоимость><валюта>доллар</валюта><значение>35</значение></стоимость>')

select * from TestXml
go

--7. отчет
use Halaleenko_laba4;
select rtrim(FACULTY.FACULTY) as '@код',
(select COUNT(*) from PULPIT where PULPIT.FACULTY = FACULTY.FACULTY) as 'количество_кафедр',
(select rtrim(PULPIT.PULPIT) as '@код',
(select rtrim(TEACHER.TEACHER) as 'преподаватель/@код', TEACHER.TEACHER_NAME as 'преподаватель'
from TEACHER where TEACHER.PULPIT = PULPIT.PULPIT for xml path('преподаватели'), type, root('преподаватели'))
from PULPIT where PULPIT.FACULTY = FACULTY.FACULTY for xml path('кафедра'), type, root('кафедры'))
from FACULTY for xml path('факультет'), type, root('университет')