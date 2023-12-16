use lab1
go

--�������������
-- ������������� ��� ������ �������� ��������
CREATE VIEW ActiveRequests AS
SELECT * FROM Requests WHERE Status = 'Active';

-- ������������� ��� ������ ���������� � ������� �����������
CREATE VIEW HighPriorityIncidents AS
SELECT * FROM Incidents WHERE Priority = 'High';

-- ������������� ��� ������ ������� �� ��������� �����
CREATE VIEW ReportsLastMonth AS
SELECT * FROM Reports WHERE DATEDIFF(MONTH, CreatedAt, GETDATE()) <= 1;


--�������
-- ������ ��� �������� ����� UserID � ������� Requests
CREATE INDEX IX_Requests_UserID ON Requests(UserID);

-- ������ ��� �������� ����� UserID � ������� Incidents
CREATE INDEX IX_Incidents_UserID ON Incidents(UserID);

-- ������ ��� �������� ����� UserID � ������� Comments
CREATE INDEX IX_Comments_UserID ON Comments(UserID);


--������������������
-- ������������������ ��� RequestID
CREATE SEQUENCE RequestIDSeq START WITH 1 INCREMENT BY 1;

-- ������������������ ��� IncidentID
CREATE SEQUENCE IncidentIDSeq START WITH 1 INCREMENT BY 1;

-- ������������������ ��� ReportID
CREATE SEQUENCE ReportIDSeq START WITH 1 INCREMENT BY 1;

--���������
-- ��������� ��� �������� ������ �������
CREATE PROCEDURE CreateNewRequest
    @Title NVARCHAR(100),
    @Description NVARCHAR(MAX),
    @UserID INT
AS
BEGIN
    INSERT INTO Requests (RequestID, Title, Description, Status, Priority, CreatedAt, UpdatedAt, UserID, UserFullName)
    VALUES (NEXT VALUE FOR RequestIDSeq, @Title, @Description, 'Active', 'Medium', GETDATE(), GETDATE(), @UserID, (SELECT UserFullName FROM Users WHERE UserID = @UserID));
END;

-- ��������� ��� �������� �������
CREATE PROCEDURE CloseRequest
    @RequestID INT
AS
BEGIN
    UPDATE Requests
    SET Status = 'Closed', UpdatedAt = GETDATE()
    WHERE RequestID = @RequestID;
END;

-- ��������� ��� �������� ������ �����������
CREATE PROCEDURE AddComment
    @Text NVARCHAR(MAX),
    @UserID INT,
    @RequestID INT,
    @IncidentID INT
AS
BEGIN
    INSERT INTO Comments (CommentID, Text, CreatedAt, UserID, UserFullName, RequestID, IncidentID)
    VALUES (NEXT VALUE FOR CommentIDSeq, @Text, GETDATE(), @UserID, (SELECT UserFullName FROM Users WHERE UserID = @UserID), @RequestID, @IncidentID);
END;


--�������
-- ������� ��� ��������� ���������� ������������ � �������
CREATE FUNCTION GetCommentCountForRequest(@RequestID INT)
RETURNS INT
AS
BEGIN
    DECLARE @CommentCount INT;
    SELECT @CommentCount = COUNT(CommentID)
    FROM Comments
    WHERE RequestID = @RequestID;
    RETURN @CommentCount;
END;

-- ������� ��� ��������� ������ ���������� ��������, ��������� ������ �������������
CREATE FUNCTION GetUserRequestCount(@UserID INT)
RETURNS INT
AS
BEGIN
    DECLARE @RequestCount INT;
    SELECT @RequestCount = COUNT(RequestID)
    FROM Requests
    WHERE UserID = @UserID;
    RETURN @RequestCount;
END;

-- ������� ��� ������� ���������� ���� � ������� ���������� ���������� �������
CREATE FUNCTION DaysSinceLastUpdate(@RequestID INT)
RETURNS INT
AS
BEGIN
    DECLARE @DaysSinceLastUpdate INT;
    SELECT @DaysSinceLastUpdate = DATEDIFF(DAY, UpdatedAt, GETDATE())
    FROM Requests
    WHERE RequestID = @RequestID;
    RETURN @DaysSinceLastUpdate;
END;


--for report

-- Список таблиц и атрибутов
SELECT 
    t.name AS TableName,
    c.name AS ColumnName,
    ty.name AS DataType,
    CASE WHEN c.is_nullable = 1 THEN 'NULLABLE' ELSE 'NOT NULL' END AS ConstraintType,
    ep.value AS Description
FROM sys.tables t
JOIN sys.columns c ON t.object_id = c.object_id
LEFT JOIN sys.extended_properties ep ON t.object_id = ep.major_id AND c.column_id = ep.minor_id
JOIN sys.types ty ON c.user_type_id = ty.user_type_id;

-- Список индексов
SELECT 
    t.name AS TableName,
    i.name AS IndexName,
    i.type_desc AS IndexType
FROM sys.tables t
JOIN sys.indexes i ON t.object_id = i.object_id;

-- Список последовательностей
SELECT 
    name AS SequenceName
FROM sys.sequences;

-- Список функций
SELECT 
    schema_name(schema_id) AS SchemaName,
    name AS FunctionName,
    OBJECT_DEFINITION(object_id) AS FunctionDefinition
FROM sys.objects
WHERE type_desc LIKE '%FUNCTION%';

-- Список процедур
SELECT 
    schema_name(schema_id) AS SchemaName,
    name AS ProcedureName,
    OBJECT_DEFINITION(object_id) AS ProcedureDefinition
FROM sys.objects
WHERE type_desc LIKE '%PROCEDURE%';

-- Список представлений
SELECT 
    schema_name(schema_id) AS SchemaName,
    name AS ViewName,
    OBJECT_DEFINITION(object_id) AS ViewDefinition
FROM sys.objects
WHERE type_desc LIKE '%VIEW%';