/*
Скрипт развертывания для lab10

Этот код был создан программным средством.
Изменения, внесенные в этот файл, могут привести к неверному выполнению кода и будут потеряны
в случае его повторного формирования.
*/

GO
SET ANSI_NULLS, ANSI_PADDING, ANSI_WARNINGS, ARITHABORT, CONCAT_NULL_YIELDS_NULL, QUOTED_IDENTIFIER ON;

SET NUMERIC_ROUNDABORT OFF;


GO
:setvar DatabaseName "lab10"
:setvar DefaultFilePrefix "lab10"
:setvar DefaultDataPath "C:\Program Files\Microsoft SQL Server\MSSQL16.SQLEXPRESS\MSSQL\DATA\"
:setvar DefaultLogPath "C:\Program Files\Microsoft SQL Server\MSSQL16.SQLEXPRESS\MSSQL\DATA\"

GO
:on error exit
GO
/*
Проверьте режим SQLCMD и отключите выполнение скрипта, если режим SQLCMD не поддерживается.
Чтобы повторно включить скрипт после включения режима SQLCMD выполните следующую инструкцию:
SET NOEXEC OFF; 
*/
:setvar __IsSqlCmdEnabled "True"
GO
IF N'$(__IsSqlCmdEnabled)' NOT LIKE N'True'
    BEGIN
        PRINT N'Для успешного выполнения этого скрипта должен быть включен режим SQLCMD.';
        SET NOEXEC ON;
    END


GO
USE [$(DatabaseName)];


GO
PRINT N'Идет создание Определяемый пользователем тип [dbo].[CustomType]…';


GO
CREATE TYPE [dbo].[CustomType]
     EXTERNAL NAME [lab10].[CustomType];


GO
PRINT N'Идет создание Процедура [dbo].[DeleteFile]…';


GO
CREATE PROCEDURE [dbo].[DeleteFile]
@directoryPath NVARCHAR (MAX) NULL, @fileName NVARCHAR (MAX) NULL
AS EXTERNAL NAME [lab10].[FileOperations].[DeleteFile]


GO
PRINT N'Обновление завершено.';


GO
