@echo off
if "%1"=="debug" goto appDebug
echo "you has been deploy full package,you can use add a param : debug to reduce redeploy times."
echo "debug type: just compile --> jar --> copies."
call mvn clean 
call mvn assembly:assembly -Dmaven.test.skip=true
cd .\target
mkdir deploy

echo "uncompress smartcard-operator-0.0.1-SNAPSHOT-bin.zip"
jar xvf smartcard-operator-0.0.1-SNAPSHOT-bin.zip

:deployAPP
echo "------------ deploy app files..."
mkdir .\deploy\conf
xcopy/s ".\smartcard-operator-0.0.1-SNAPSHOT\conf\*.*" .\deploy\conf
copy/y .\smartcard-operator-0.0.1-SNAPSHOT\start.bat .\deploy
copy/y .\smartcard-operator-0.0.1-SNAPSHOT\log4j.properties .\deploy
mkdir .\deploy\lib
xcopy/s/e ".\smartcard-operator-0.0.1-SNAPSHOT\lib\*.*" .\deploy\lib
copy/y .\smartcard-operator-0.0.1-SNAPSHOT\*.jar .\deploy\lib\ext

cd ..\

echo "deploy finished. All files put into 'deploy/*'"
goto end

:appDebug
call mvn compile
call mvn jar:jar
copy/y .\target\smartcard-operator-0.0.1-SNAPSHOT.jar .\target\deploy
cd .\target\deploy
echo "new jar file created, please test it."
goto end

:exit
exit /b 1

:end
exit /b 0
