USE Halaleenko_laba4;  
--1 ����������� �������������
GO
CREATE VIEW [�������������]
AS SELECT TEACHER [���], TEACHER_NAME [��� �������������], GENDER [���],PULPIT [��� �������] 
FROM TEACHER
GO
SELECT * FROM �������������;
--2 
GO
CREATE VIEW [���������� ������] 
AS SELECT FACULTY.FACULTY_NAME [���������], count (*) [���������� ������] FROM FACULTY join PULPIT
on FACULTY.FACULTY = PULPIT.FACULTY
GROUP BY FACULTY.FACULTY_NAME;
GO
SELECT * FROM [���������� ������];
GO


--3
DROP VIEW [���������]
CREATE VIEW [���������] (���, ������������, ���)
AS SELECT AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_TYPE
FROM AUDITORIUM
WHERE AUDITORIUM_TYPE LIKE '��%'
go
SELECT * FROM ���������

INSERT ��������� VALUES('300-4', '300-4', '��')
INSERT ��������� VALUES('301-4', '301-4', '��')
INSERT ��������� VALUES('302-4', '302-4', '��')
UPDATE ��������� SET ��� = '303-4' 
WHERE ������������ = '302-4'
DELETE FROM ��������� WHERE ��� = '301-4'
--4
CREATE VIEW [���������� ���������] (���, ������������, ���)
AS SELECT AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_TYPE
FROM AUDITORIUM
WHERE AUDITORIUM_TYPE LIKE '��%'
WITH CHECK OPTION;
go
SELECT * FROM [���������� ���������]

INSERT [���������� ���������] VALUES('306-4', '306-4', '��-�')
INSERT [���������� ���������] VALUES('305-4', '305-4', '��')
UPDATE [���������� ���������] SET ��� = '�' 
WHERE ������������ = '306-4'
 --5
GO
CREATE VIEW [����������]
AS SELECT TOP 10 SUBJECT [���], SUBJECT_NAME [��� ����������], PULPIT [��� �������] FROM SUBJECT
ORDER BY [��� ����������]
GO
SELECT * FROM ����������;
 --6
GO
ALTER VIEW [���������� ������] WITH SCHEMABINDING
AS SELECT FACULTY.FACULTY_NAME [���������], count (*) [���������� ������] FROM  dbo.FACULTY JOIN dbo.PULPIT
ON FACULTY.FACULTY = PULPIT.FACULTY
GROUP BY FACULTY.FACULTY_NAME;
GO
SELECT * FROM [���������� ������];