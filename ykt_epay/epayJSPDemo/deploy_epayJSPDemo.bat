@echo off
call mvn clean
call mvn package 

echo "*****************************************************************************"
echo "***********Finish deploying, the package is target/epayJSPDemo.war***********"
echo "*****************************************************************************"
echo.
PAUSE
