CREATE DATABASE yktdummy
MAXINSTANCES 8
MAXLOGHISTORY 32
MAXLOGFILES 32
MAXLOGMEMBERS 3
MAXDATAFILES 2048
character set AL32UTF8
NATIONAL CHARACTER SET AL16UTF16
DATAFILE '/yktdummydb/system01.dbf' size 300M autoextend on next 64K maxsize unlimited
sysaux DATAFILE '/yktdummydb/sysaux01.dbf' size 100M autoextend on next 64K maxsize unlimited
DEFAULT TEMPORARY TABLESPACE TEMP TEMPFILE '/yktdummydb/temp01.dbf' size 50M autoextend on MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL UNIFORM SIZE 1024K
UNDO TABLESPACE UNDOTBS1 datafile '/yktdummydb/undotbs01.dbf' SIZE 300M autoextend on next 64K maxsize unlimited
LOGFILE
GROUP 1 ('/yktdummydb/redo0101.dbf') SIZE 50M REUSE,
GROUP 2 ('/yktdummydb/redo0201.dbf') SIZE 50M REUSE,
GROUP 3 ('/yktdummydb/redo0301.dbf') SIZE 50M REUSE;
