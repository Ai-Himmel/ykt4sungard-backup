@echo off
echo [INFO] ��maven�ֿ⸴��jar��������ĿĿ¼.

cd %~dp0

call mvn -f ../../../pom.xml dependency:copy-dependencies -DoutputDirectory=./target/classes/lib/ext -DincludeScope=runtime


pause
