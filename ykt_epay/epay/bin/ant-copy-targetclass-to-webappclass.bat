@echo off
echo [INFO] ��"src/main/webapp/WEB-INF/lib" ɾ��Ŀ¼.

cd %~dp0

call ant -f ../build.xml targetToclasses

pause
