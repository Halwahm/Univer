USE Halaleenko_laba4;  
--1 разработать представление
GO
CREATE VIEW [Преподаватели]
AS SELECT TEACHER [Код], TEACHER_NAME [Имя преподавателя], GENDER [Пол],PULPIT [Код кафедры] 
FROM TEACHER
GO
SELECT * FROM Преподаватели;
--2 
GO
CREATE VIEW [Количество кафедр] 
AS SELECT FACULTY.FACULTY_NAME [Факультет], count (*) [Количество кафедр] FROM FACULTY join PULPIT
on FACULTY.FACULTY = PULPIT.FACULTY
GROUP BY FACULTY.FACULTY_NAME;
GO
SELECT * FROM [Количество кафедр];
GO


--3
DROP VIEW [Аудитории]
CREATE VIEW [Аудитории] (Код, Наименование, Тип)
AS SELECT AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_TYPE
FROM AUDITORIUM
WHERE AUDITORIUM_TYPE LIKE 'ЛК%'
go
SELECT * FROM Аудитории

INSERT Аудитории VALUES('300-4', '300-4', 'ЛК')
INSERT Аудитории VALUES('301-4', '301-4', 'ЛК')
INSERT Аудитории VALUES('302-4', '302-4', 'ЛК')
UPDATE Аудитории SET Код = '303-4' 
WHERE Наименование = '302-4'
DELETE FROM Аудитории WHERE Код = '301-4'
--4
CREATE VIEW [Лекционные аудитории] (Код, Наименование, Тип)
AS SELECT AUDITORIUM, AUDITORIUM_NAME, AUDITORIUM_TYPE
FROM AUDITORIUM
WHERE AUDITORIUM_TYPE LIKE 'ЛК%'
WITH CHECK OPTION;
go
SELECT * FROM [Лекционные аудитории]

INSERT [Лекционные аудитории] VALUES('306-4', '306-4', 'ЛБ-К')
INSERT [Лекционные аудитории] VALUES('305-4', '305-4', 'ЛК')
UPDATE [Лекционные аудитории] SET Тип = 'Л' 
WHERE Наименование = '306-4'
 --5
GO
CREATE VIEW [Дисциплины]
AS SELECT TOP 10 SUBJECT [код], SUBJECT_NAME [имя дисциплины], PULPIT [код кафедры] FROM SUBJECT
ORDER BY [имя дисциплины]
GO
SELECT * FROM Дисциплины;
 --6
GO
ALTER VIEW [Количество кафедр] WITH SCHEMABINDING
AS SELECT FACULTY.FACULTY_NAME [Факультет], count (*) [Количество кафедр] FROM  dbo.FACULTY JOIN dbo.PULPIT
ON FACULTY.FACULTY = PULPIT.FACULTY
GROUP BY FACULTY.FACULTY_NAME;
GO
SELECT * FROM [Количество кафедр];