@echo off
SET IDS_LIB=..\lib

set CLASSPATH=%CLASSPATH%;%IDS_LIB%\Ice.jar
set CLASSPATH=%CLASSPATH%;%IDS_LIB%\idstar_2.1.jar
set CLASSPATH=%CLASSPATH%;..\lib\jakarta-regexp-1.3.jar
set CLASSPATH=%CLASSPATH%;.

%JAVA_HOME%\bin\java benchmark.GetCurrentUser ..\..\client.properties AQIC5wM2LY4SfcwltO5He/a+AL9GBS5JiuFGQU0a5FA8Pqw=@tzxu.zty.com-2b6%%3A409f2174%%3A392c26e194fe499   100000
pause