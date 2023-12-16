-- Создание объектного типа данных TaskType
DROP TYPE TaskType;

CREATE TYPE TaskType AS OBJECT (
    TaskID NUMBER,
    Title NVARCHAR2(100),
    Description NVARCHAR2(2000),
    Status NVARCHAR2(50),
    Priority NVARCHAR2(50),
    CreatedAt TIMESTAMP,
    ClosedAt TIMESTAMP,
    UserID NUMBER,
    UserFullName NVARCHAR2(101),
    
    -- Дополнительный конструктор
    CONSTRUCTOR FUNCTION TaskType(p_TaskID NUMBER, p_Title NVARCHAR2, p_Description NVARCHAR2,
        p_Status NVARCHAR2, p_Priority NVARCHAR2, p_CreatedAt TIMESTAMP, p_ClosedAt TIMESTAMP,
        p_UserID NUMBER, p_UserFullName NVARCHAR2) RETURN SELF AS RESULT,
    
    -- Метод сравнения типа MAP
    MEMBER FUNCTION compare(task2 IN TaskType) RETURN NUMBER 
);
/

CREATE OR REPLACE TYPE BODY TaskType AS
    CONSTRUCTOR FUNCTION TaskType(p_TaskID NUMBER, p_Title NVARCHAR2, p_Description NVARCHAR2,
        p_Status NVARCHAR2, p_Priority NVARCHAR2, p_CreatedAt TIMESTAMP, p_ClosedAt TIMESTAMP,
        p_UserID NUMBER, p_UserFullName NVARCHAR2) RETURN SELF AS RESULT IS
    BEGIN
        SELF.TaskID := p_TaskID;
        SELF.Title := p_Title;
        SELF.Description := p_Description;
        SELF.Status := p_Status;
        SELF.Priority := p_Priority;
        SELF.CreatedAt := p_CreatedAt;
        SELF.ClosedAt := p_ClosedAt;
        SELF.UserID := p_UserID;
        SELF.UserFullName := p_UserFullName;
        RETURN;
    END;

    MEMBER FUNCTION compare(task2 IN TaskType) RETURN NUMBER IS
        BEGIN
            -- Ваша реализация сравнения двух объектов TaskType
            IF self.TaskID = task2.TaskID AND self.Title = task2.Title THEN
                RETURN 0; -- Объекты равны
            ELSE
                RETURN 1; -- Объекты разные
            END IF;
        END;
END;
/

DROP TYPE EmployeeType;

-- Создание объектного типа данных EmployeeType
CREATE TYPE EmployeeType AS OBJECT (
    EmployeeID NUMBER,
    FirstName NVARCHAR2(50),
    LastName NVARCHAR2(50),
    Email NVARCHAR2(100),
    Salary NUMBER,
    DepartmentID NUMBER,
    
    -- Метод экземпляра-функция
    MEMBER FUNCTION GetFullName RETURN NVARCHAR2,
    
    -- Метод экземпляра-процедура
    MEMBER PROCEDURE PrintFullName,
    
    MEMBER FUNCTION calculateSalary RETURN NUMBER DETERMINISTIC

);
/

CREATE OR REPLACE TYPE BODY EmployeeType AS
    MEMBER FUNCTION GetFullName RETURN NVARCHAR2 IS
    BEGIN
        RETURN self.FirstName || ' ' || self.LastName;
    END;
    
    MEMBER PROCEDURE PrintFullName IS
    BEGIN
        DBMS_OUTPUT.PUT_LINE(self.FirstName || ' ' || self.LastName);
    END;
    
    MEMBER FUNCTION calculateSalary RETURN NUMBER DETERMINISTIC IS 
    BEGIN
        RETURN Salary * 12; 
    END;
END;
/

drop table TaskTypeTable;
-- Создание таблицы для хранения объектов типа TaskType
CREATE TABLE TaskTypeTable OF TaskType (
    TaskID primary key
);

-- Копирование данных из таблицы Incidents в объектный тип TaskType
INSERT INTO TaskTypeTable
SELECT TaskType(IncidentID, Title, Description, Status, Priority, CreatedAt, ClosedAt, UserID, UserFullName)
FROM Incidents;

-- Создание объектного представления для TaskType
CREATE VIEW TaskTypeView AS
SELECT * FROM TaskTypeTable;

SELECT * FROM TaskTypeView;

drop table EmplTbl;
CREATE TABLE EmplTbl (
    Emp EmployeeType,
    DateAdded DATE DEFAULT SYSDATE
);

-- создание индекса по атрибуту
CREATE INDEX Empl_Index ON EmplTbl(DateAdded);
drop index Empl_Index;

CREATE INDEX SalaryIndex ON EmplTbl((Emp.calculateSalary()));
drop index SalaryIndex;

SELECT * FROM EmplTbl;

-- Вызов дополнительного конструктора для создания объекта TaskType
DECLARE
    v_Task TaskType;
BEGIN
    v_Task := TaskType(1, 'Sample Task', 'Description', 'Open', 'High', SYSTIMESTAMP, NULL, 101, 'John Doe');
    DBMS_OUTPUT.PUT_LINE('TaskID: ' || v_Task.TaskID || ', Title: ' || v_Task.Title || ', Status: ' || v_Task.Status);
END;
/

-- Использование метода экземпляра функции для объекта EmployeeType
DECLARE
    v_Employee EmployeeType := EmployeeType(1, 'Alice', 'Johnson', 'alice@example.com', 50000, 201);
    v_FullName NVARCHAR2(100);
BEGIN
    v_FullName := v_Employee.GetFullName();
    DBMS_OUTPUT.PUT_LINE('Employee Full Name: ' || v_FullName);
END;
/

-- Использование метода экземпляра процедуры для объекта EmployeeType
DECLARE
    v_Employee EmployeeType := EmployeeType(2, 'Bob', 'Smith', 'bob@example.com', 60000, 202);
BEGIN
    v_Employee.PrintFullName();
END;
/

-- Для вызова метода сравнения MAP в PL/SQL нужно иметь два объекта одного типа.
-- Приведу пример простой логики сравнения методом MAP.

DECLARE
    v_Task1 TaskType := TaskType(1, 'Task 1', 'Description 1', 'Open', 'High', SYSTIMESTAMP, NULL, 101, 'John Doe');
    v_Task2 TaskType := TaskType(2, 'Task 2', 'Description 2', 'Closed', 'Low', SYSTIMESTAMP, SYSTIMESTAMP, 102, 'Jane Smith');
    v_CompareResult NUMBER;
BEGIN
    v_CompareResult := TaskType.compare(v_Task1, v_Task2);
    IF v_CompareResult = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Tasks are equal.');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Tasks are different.');
    END IF;
END;
/



