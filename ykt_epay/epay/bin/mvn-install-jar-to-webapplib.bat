@echo off
echo [INFO] ��maven�ֿ⸴��jar��������ĿĿ¼.

cd %~dp0

call mvn -f ../pom.xml dependency:copy-dependencies -DoutputDirectory=./src/main/webapp/WEB-INF/lib -DincludeScope=runtime


pause
