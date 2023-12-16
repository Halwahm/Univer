use [mshoad]


exec sp_configure 'clr_enabled', 1;
reconfigure;

EXEC sp_configure 'show advanced options', 1;
RECONFIGURE;

EXEC sp_configure 'clr strict security', 0;
RECONFIGURE;


--CREATE ASSEMBLY lab10
--FROM 'C:\mshoad\lab10\lab10\bin\Debug\lab10.dll'
--WITH PERMISSION_SET = SAFE;

--drop ASSEMBLY lab10;

--CREATE PROCEDURE DeleteFileProcedure
--    @directoryPath NVARCHAR(255),
--    @fileName NVARCHAR(255)
--AS EXTERNAL NAME lab10.FileOperations.DeleteFile;

--drop procedure DeleteFileProcedure;

EXEC DeleteFile 'C:\mshoad', '111.txt';


CREATE TABLE TypeTable (
    Id INT PRIMARY KEY,
    TestColumn CustomType
);


INSERT INTO TypeTable (Id, TestColumn) VALUES (1, 'success');
INSERT INTO TypeTable (Id, TestColumn) VALUES (2, 'success');
INSERT INTO TypeTable (Id, TestColumn) VALUES (3, 'success');
INSERT INTO TypeTable (Id, TestColumn) VALUES (4, 'failure');

select * from TypeTable;

drop table TypeTable;