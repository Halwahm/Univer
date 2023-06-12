--1
USE ����������_�������;
GO
SET NOCOUNT ON;

IF EXISTS (SELECT * FROM SYS.OBJECTS WHERE OBJECT_ID = OBJECT_ID(N'DBO.NewT'))
	DROP TABLE NewT;

DECLARE	@C int, @FLAG char = 'C';

SET IMPLICIT_TRANSACTIONS ON;
CREATE TABLE NewT (
	FIELD int
);
INSERT INTO NewT
	VALUES (1), (2), (3);

SET @C = (SELECT COUNT(*) FROM NewT);
PRINT ('���������� ����� � ������� NewT: ' + CAST(@C AS char(2)));
IF @FLAG = 'C'
	COMMIT;
ELSE ROLLBACK;

IF EXISTS (SELECT * FROM SYS.OBJECTS WHERE OBJECT_ID = OBJECT_ID(N'DBO.NewT'))
	PRINT '������� NewT ����';
ELSE
	PRINT '������� NewT ���'

--2
USE Halaleenko_laba4;
GO
SET NOCOUNT ON;
DECLARE @TRCOUNT int;
BEGIN TRY
  BEGIN TRAN
    DELETE AUDITORIUM_TYPE
    WHERE AUDITORIUM_TYPENAME = '����� ����������';
    INSERT AUDITORIUM_TYPE
      VALUES ('��-�', '����� ����������');
    INSERT AUDITORIUM_TYPE
      VALUES ('��-�', '����� ����������');
  COMMIT TRAN;
END TRY
BEGIN CATCH
  PRINT '������ ' + CASE
    WHEN ERROR_NUMBER() = 2627 AND
      PATINDEX('%AUDITORIUM_TYPE_PK%', ERROR_MESSAGE()) > 0 THEN '������������ ���� ���������' 
    ELSE '����������� ������: ' + CAST(ERROR_NUMBER() AS varchar(5))
  END;
  SET @TRCOUNT = @@TRANCOUNT;
  PRINT '���-�� ��������� ����������: ' + CAST(@TRCOUNT AS varchar(2));
  IF @@TRANCOUNT > 0
    ROLLBACK TRAN;
END CATCH;


SELECT * FROM AUDITORIUM_TYPE
--DELETE FROM AUDITORIUM_TYPE WHERE AUDITORIUM_TYPE LIKE ('��-�')
GO

--3
DECLARE @point varchar(32);
BEGIN TRY
  BEGIN TRAN				
    DELETE AUDITORIUM_TYPE
    WHERE AUDITORIUM_TYPENAME = '����� ����������';
    SET @point = 'p1';
    SAVE TRAN @point;

    INSERT AUDITORIUM_TYPE
      VALUES ('��-�', '����� ����������');
    SET @point = 'p2';
    SAVE TRAN @point;

    INSERT AUDITORIUM_TYPE
      VALUES ('��-�', '����� ����������');
  --INSERT AUDITORIUM_TYPE VALUES ('��-��', '���������� ����������');
  COMMIT TRAN;
END TRY
BEGIN CATCH
  PRINT '������: ' + CASE
    WHEN ERROR_NUMBER() = 2627 AND
      PATINDEX('%AUDITORIUM_TYPE_PK%', ERROR_MESSAGE()) > 0 THEN '������������ ���� ���������'
    ELSE '����������� ������: ' + CAST(ERROR_NUMBER() AS varchar(5)) + ERROR_MESSAGE()
  END;
  IF @@TRANCOUNT > 0
  BEGIN
    PRINT '����������� �����: ' + @point;
    ROLLBACK TRAN @point;		
    COMMIT TRAN;			
  END
END CATCH
GO

SELECT * FROM AUDITORIUM_TYPE
GO


--8
USE ����������_�������;
BEGIN TRAN
	INSERT ����������
		VALUES ('����', 100, '����������')
	BEGIN TRAN
		UPDATE ����������
		SET ���������� = '����'
		WHERE ������� = 100
	COMMIT;
	IF @@TRANCOUNT > 0
		ROLLBACK
	SELECT (SELECT
			COUNT(*)
		FROM ����������
		WHERE ���������� = '����')
		'����������'