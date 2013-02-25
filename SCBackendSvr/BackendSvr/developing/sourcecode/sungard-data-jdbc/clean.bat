@echo off
echo [INFO] Use maven clean clean target dir.

cd %~dp0
call mvn clean

pause