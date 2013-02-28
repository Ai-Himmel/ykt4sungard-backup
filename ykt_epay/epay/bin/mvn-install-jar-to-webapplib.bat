@echo off
echo [INFO] 从maven仓库复制jar到所有项目目录.

cd %~dp0

call mvn -f ../pom.xml dependency:copy-dependencies -DoutputDirectory=./src/main/webapp/WEB-INF/lib -DincludeScope=runtime


pause
