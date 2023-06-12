use Halaleenko_laba4

select * from AUDITORIUM;
SELECT max(AUDITORIUM.AUDITORIUM_CAPACITY)[Max �����������], 
	   min(AUDITORIUM.AUDITORIUM_CAPACITY)[Min �����������], 
	   avg(AUDITORIUM.AUDITORIUM_CAPACITY)[������� ����������� ���������], 
	   sum(AUDITORIUM.AUDITORIUM_CAPACITY)[��������� ����������� ���� ���������], 
	   count(*)[����� ���������� ���������]
	FROM AUDITORIUM;

---------------------------------------------------------------------------2------------------
SELECT AUDITORIUM_TYPE.AUDITORIUM_TYPENAME[��� ���������], 
	   max(AUDITORIUM.AUDITORIUM_CAPACITY)[Max �����������], 
	   min(AUDITORIUM.AUDITORIUM_CAPACITY)[Min �����������], 
	   avg(AUDITORIUM.AUDITORIUM_CAPACITY)[������� ����������� ���������], 
	   sum(AUDITORIUM.AUDITORIUM_CAPACITY)[��������� ����������� ���� ���������], 
	   count(*)[����� ���������� ���������]
	FROM AUDITORIUM INNER JOIN AUDITORIUM_TYPE
	ON AUDITORIUM.AUDITORIUM_TYPE = AUDITORIUM_TYPE.AUDITORIUM_TYPE
	GROUP BY AUDITORIUM_TYPE.AUDITORIUM_TYPENAME

---------------------------------------------------------------------------3------------------
SELECT * FROM 
			(SELECT Case 
				when PROGRESS.NOTE = 10 then '10'
				when PROGRESS.NOTE between 8 and 9 then '8-9'
				when PROGRESS.NOTE between 6 and 7 then '6-7'
				when PROGRESS.NOTE between 4 and 5 then '4-5'
				when PROGRESS.NOTE between 1 and 3 then '1-3'
				end [������], count(*)[����������]
					FROM PROGRESS
					GROUP BY Case
						when PROGRESS.NOTE = 10 then '10'
						when PROGRESS.NOTE between 8 and 9 then '8-9'
						when PROGRESS.NOTE between 6 and 7 then '6-7'
						when PROGRESS.NOTE between 4 and 5 then '4-5'
						when PROGRESS.NOTE between 1 and 3 then '1-3'
						end) as T
						ORDER BY Case [������]
						when '10' then 1
						when '8-9' then 2
						when '6-7' then 3
						when '4-5' then 4
						else 0
						end;

---------------------------------------------------------------------------4------------------
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		g.YEAR_FIRST[��� �����������],
		round(avg(cast(p.NOTE as float(4))),2)[������� ������]
	FROM FACULTY f 
	INNER JOIN GROUPS g ON f.FACULTY = g.FACULTY
	INNER JOIN STUDENT s ON g.IDGROUP = s.IDGROUP
	INNER JOIN PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	GROUP BY f.FACULTY, g.PROFESSION, g.YEAR_FIRST
	ORDER BY [������� ������] desc;


SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		g.YEAR_FIRST[��� �����������],
		round(avg(cast(p.NOTE as float(4))),2)[������� ������]
	FROM FACULTY f 
	INNER JOIN GROUPS g ON f.FACULTY = g.FACULTY
	INNER JOIN STUDENT s ON g.IDGROUP = s.IDGROUP
	INNER JOIN PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE p.SUBJECT IN('��', '����')
	GROUP BY f.FACULTY, g.PROFESSION, g.YEAR_FIRST
	ORDER BY [������� ������] desc;

---------------------------------------------------------------------------5-6-----------------
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT

--ROLLUP
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY ROLLUP (f.FACULTY, g.PROFESSION, p.SUBJECT)

--CUBE
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY CUBE (f.FACULTY, g.PROFESSION, p.SUBJECT)
---------------------------------------------------------------------------7------------------
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT

UNION ALL

SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('����')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT;

---------------------------------------------------------------------------8------------------
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT

INTERSECT

SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT


---------------------------------------------------------------------------9------------------
SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT

EXCEPT

SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('����')
	GROUP BY f.FACULTY, g.PROFESSION, p.SUBJECT

---------------------------------------------------------------------------10------------------
SELECT p1.SUBJECT[�������], p1.NOTE[������],
		(SELECT COUNT(*) FROM PROGRESS p2
					WHERE p1.NOTE = p2.NOTE AND p1.SUBJECT = p2.SUBJECT) [����������]
	FROM PROGRESS p1
	 GROUP BY p1.SUBJECT, p1.NOTE
	 HAVING NOTE IN(8, 9)

	 SELECT f.FACULTY[���������], 
		g.PROFESSION[�������������], 
		p.SUBJECT[����������],
		round(avg(cast(p.NOTE as float(4))), 2)[������� ������]
	FROM FACULTY f 
	Inner Join GROUPS g ON f.FACULTY = g.FACULTY
	Inner Join STUDENT s ON g.IDGROUP = s.IDGROUP
	Inner Join PROGRESS p ON p.IDSTUDENT = s.IDSTUDENT
	WHERE f.FACULTY IN('���')
	GROUP BY CUBE (f.FACULTY, g.PROFESSION, p.SUBJECT)
---------------------------------------------------------------------------12----------------

SELECT AUDITORIUM.AUDITORIUM_TYPE [��� ���������], 
	   AUDITORIUM.AUDITORIUM_NAME [����� ���������], 
	   count(*) [����������] FROM AUDITORIUM 
	    	GROUP BY CUBE (AUDITORIUM.AUDITORIUM_TYPE, AUDITORIUM.AUDITORIUM_NAME);

-----------------------------------------------------------
SELECT FACULTY.FACULTY_NAME [���������], 
		GROUPS.IDGROUP [����� ������],
		count(*) [����������]
   FROM FACULTY
		Inner Join GROUPS ON FACULTY.FACULTY = GROUPS.FACULTY
		Inner Join STUDENT on STUDENT.IDGROUP = GROUPS.IDGROUP
   GROUP BY CUBE (FACULTY_NAME, GROUPS.IDGROUP)
   ORDER BY FACULTY_NAME, GROUPS.IDGROUP


   SELECT AUDITORIUM_TYPE.AUDITORIUM_TYPE [���������], 
   AUDITORIUM.AUDITORIUM_CAPACITY [�����������],
   COUNT(*) [����������] 
   FROM AUDITORIUM INNER JOIN AUDITORIUM_TYPE
   ON AUDITORIUM.AUDITORIUM_TYPE = AUDITORIUM_TYPE.AUDITORIUM_TYPE
   GROUP BY CUBE (AUDITORIUM_TYPE.AUDITORIUM_TYPE, AUDITORIUM.AUDITORIUM_CAPACITY)
   ORDER BY AUDITORIUM_TYPE.AUDITORIUM_TYPE, AUDITORIUM.AUDITORIUM_CAPACITY

SELECT * FROM 
			(SELECT Case 
				when STUDENT.IDGROUP = 3 then '3'
				when STUDENT.IDGROUP = 4 then '4'
				when STUDENT.IDGROUP = 5 then '5'
				when STUDENT.IDGROUP = 6 then '6'
				when STUDENT.IDGROUP = 7 then '7'
				when STUDENT.IDGROUP = 8 then '8'
				when STUDENT.IDGROUP = 9 then '9'
				when STUDENT.IDGROUP = 10 then '10'
				when STUDENT.IDGROUP = 11 then '11'
				when STUDENT.IDGROUP = 12 then '12'
				when STUDENT.IDGROUP = 13 then '13'
				when STUDENT.IDGROUP = 14 then '14'
				when STUDENT.IDGROUP = 15 then '15'
				when STUDENT.IDGROUP = 16 then '16'
				when STUDENT.IDGROUP = 17 then '17'
				when STUDENT.IDGROUP = 18 then '18'
				end [������], 
				count(*)[����������] FROM STUDENT
					GROUP BY Case
						when STUDENT.IDGROUP = 3 then '3'
						when STUDENT.IDGROUP = 4 then '4'
						when STUDENT.IDGROUP = 5 then '5'
						when STUDENT.IDGROUP = 6 then '6'
						when STUDENT.IDGROUP = 7 then '7'
						when STUDENT.IDGROUP = 8 then '8'
						when STUDENT.IDGROUP = 9 then '9'
						when STUDENT.IDGROUP = 10 then '10'
						when STUDENT.IDGROUP = 11 then '11'
						when STUDENT.IDGROUP = 12 then '12'
						when STUDENT.IDGROUP = 13 then '13'
						when STUDENT.IDGROUP = 14 then '14'
						when STUDENT.IDGROUP = 15 then '15'
						when STUDENT.IDGROUP = 16 then '16'
						when STUDENT.IDGROUP = 17 then '17'
						when STUDENT.IDGROUP = 18 then '18'
						end) as T
							ORDER BY Case [������]
							when '3' then 1
							when '4' then 2
							when '5' then 3
							when '6' then 4
							when '7' then 5
							when '8' then 6
							when '9' then 7
							when '10' then 8
							when '11' then 9
							when '12' then 10
							when '13' then 11
							when '14' then 12
							when '15' then 13
							when '16' then 14
							when '17' then 15
							when '18' then 16
						else 0
						end;
