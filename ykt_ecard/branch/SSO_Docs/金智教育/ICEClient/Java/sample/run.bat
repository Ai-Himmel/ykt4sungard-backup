@echo off
SET IDS_LIB=..\lib

set CLASSPATH=%CLASSPATH%;%IDS_LIB%\Ice.jar
set CLASSPATH=%CLASSPATH%;%IDS_LIB%\idstar_2.1.jar
set CLASSPATH=%CLASSPATH%;..\lib\jakarta-regexp-1.3.jar
set CLASSPATH=%CLASSPATH%;.

%JAVA_HOME%\bin\java GetUserAttribute ..\..\client.properties
pause