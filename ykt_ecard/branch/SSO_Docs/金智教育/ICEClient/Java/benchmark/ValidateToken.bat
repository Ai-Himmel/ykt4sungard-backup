@echo off
SET IDS_LIB=..\lib

set CLASSPATH=%CLASSPATH%;%IDS_LIB%\Ice.jar
set CLASSPATH=%CLASSPATH%;%IDS_LIB%\idstar_2.1.jar
set CLASSPATH=%CLASSPATH%;..\lib\jakarta-regexp-1.3.jar
set CLASSPATH=%CLASSPATH%;.

%JAVA_HOME%\bin\java benchmark.ValidateToken ..\..\client.properties AQIC5wM2LY4Sfcw2zeujgM1Wzenfsi8sflZbH+XCHzVoZP8=@tzxu.zty.com-2c9%%3A409f244f%%3Ab6105a3fe2146d91   100000
pause