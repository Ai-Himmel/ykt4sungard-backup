@echo off
echo [INFO] call command mvn deploy -Dmaven.test.skip=true  .

cd %~dp0
call mvn install -Dmaven.test.skip=true

pause