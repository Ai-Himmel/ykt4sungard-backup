@echo off
echo [INFO] ´Ó"src/main/webapp/WEB-INF/lib" É¾³ýÄ¿Â¼.

cd %~dp0

call ant -f ../build.xml targetToclasses

pause
