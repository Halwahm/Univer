--1
SELECT * FROM DBA_TABLESPACES;
--2
SELECT * FROM DBA_DATA_FILES;
SELECT * FROM V$LOGFILE;
--3
SELECT GROUP#, MEMBERS, STATUS FROM V$LOG;
--4
SELECT * FROM V$LOG;
--5
ALTER SESSION SET CONTAINER = CDB$ROOT;
ALTER SESSION SET CONTAINER = PDB_POT;
ALTER SYSTEM SWITCH LOGFILE;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
--6
--GROUP
ALTER SESSION SET CONTAINER = CDB$ROOT;
ALTER DATABASE ADD LOGFILE GROUP 4 'C:\app\ora_install_user\oradata\orcl\PAVREDO01.LOG'
SIZE 50M BLOCKSIZE 512;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
--FILE
ALTER DATABASE ADD LOGFILE MEMBER 'C:\app\ora_install_user\oradata\orcl\PAVREDO011.LOG' TO GROUP 4;
ALTER DATABASE ADD LOGFILE MEMBER 'C:\app\ora_install_user\oradata\orcl\PAVREDO012.LOG' TO GROUP 4;
ALTER DATABASE ADD LOGFILE MEMBER 'C:\app\ora_install_user\oradata\orcl\PAVREDO013.LOG' TO GROUP 4;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
ALTER SYSTEM SWITCH LOGFILE;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
--7
ALTER DATABASE DROP LOGFILE MEMBER 'C:\app\ora_install_user\oradata\orcl\PAVREDO011.LOG';
ALTER DATABASE DROP LOGFILE MEMBER 'C:\app\ora_install_user\oradata\orcl\PAVREDO012.LOG';
ALTER DATABASE DROP LOGFILE MEMBER 'C:\app\ora_install_user\oradata\orcl\PAVREDO013.LOG';
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
ALTER DATABASE DROP LOGFILE GROUP 4;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;

ALTER SYSTEM SWITCH LOGFILE;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
ALTER SYSTEM CHECKPOINT;
--8
SELECT NAME, LOG_MODE FROM V$DATABASE;
SELECT INSTANCE_NAME, ARCHIVER, ACTIVE_STATE FROM V$INSTANCE;

SELECT NAME, LOG_MODE FROM V$DATABASE;
SELECT INSTANCE_NAME, ARCHIVER, ACTIVE_STATE FROM V$INSTANCE;
SELECT * FROM V$LOG;

ALTER SYSTEM SWITCH LOGFILE;
SELECT * FROM V$ARCHIVED_LOG;

ALTER SYSTEM SWITCH LOGFILE;
SELECT GROUP#, SEQUENCE#, BYTES, MEMBERS, STATUS, FIRST_CHANGE# FROM V$LOG;
SELECT NAME, FIRST_CHANGE#, NEXT_CHANGE# FROM V$ARCHIVED_LOG;

ARCHIVE LOG LIST;

SHOW PARAMETER DB_RECOVERY;

select * from v$controlfile;



