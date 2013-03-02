@echo off
call mvn clean 
call mvn package -Dmaven.test.skip=true

echo "deploy finished. All files put into 'target/*'"