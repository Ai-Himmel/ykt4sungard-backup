@echo off
if "%1"=="debug" goto appDebug
echo "you has been deploy full package,you can use add a param : debug to reduce redeploy times."
echo "debug type: just compile --> jar --> copies."
call mvn clean 
call mvn assembly:assembly -Dmaven.test.skip=true
cd .\target
mkdir deploy

echo "uncompress CardReader-bin.zip"
jar xvf CardReader-bin.zip

if not "%JAVA_HOME%" == "" goto delpoyJRE
echo JAVA_HOME should point to a JDK in order to run in debug mode.
goto exit

:delpoyJRE
echo "------------ deploy jre files..."
xcopy/s "%JAVA_HOME%\jre\*.*" ".\deploy"
del/q .\deploy\*

:deployAPP
echo "------------ deploy app files..."
copy/y .\CardReader\*.dll .\deploy\bin
mkdir .\deploy\bin\Microsoft.VC90.CRT
mkdir .\deploy\bin\Microsoft.VC90.MFC
xcopy/s ".\CardReader\Microsoft.VC90.CRT\*.*" .\deploy\bin\Microsoft.VC90.CRT
xcopy/s ".\CardReader\Microsoft.VC90.MFC\*.*" .\deploy\bin\Microsoft.VC90.MFC
copy/y .\CardReader\kscardinterface_online.dll .\deploy\bin\kscardinterface.dll
copy/y .\CardReader\cpack.dat .\deploy\bin
copy/y .\CardReader\pub.key .\deploy\bin
copy/y .\CardReader\log4j-1.2.16.jar .\deploy\bin
copy/y .\CardReader\mytools-1.0-SNAPSHOT.jar .\deploy\bin
copy/y .\CardReader\commons-lang-2.6.jar .\deploy\bin
copy/y .\CardReader\jnative-1.4.jar .\deploy\bin
copy/y .\CardReader\looks-2.1.4.jar .\deploy\bin
copy/y .\CardReader\ojdbc14-10.2.0.4.0.jar .\deploy\bin
copy/y .\CardReader\poi-3.7.jar .\deploy\bin
copy/y .\CardReader\MedicalClient.bat .\deploy\bin
copy/y ..\doc\MedicalClient.txt .\deploy
copy/y ..\doc\medical.sql .\deploy

:deployLicense
echo "--------- deploy customer license and config files. please modify before using."
copy/y .\CardReader\license-sicau.lcs .\deploy\bin\license.lcs
copy/y .\classes\app_config\kscard.ini .\deploy\bin
copy/y .\classes\app_config\kscardinterface.ini .\deploy\bin
copy/y .\classes\app_config\MedicalClient.properties .\deploy\bin\CardReader.properties
copy/y .\classes\app_config\log4j.properties .\deploy\bin

cd ..\

echo "make obf main jar"
java -jar -Xmx128m -Xms128m ./src/main/assembly/allatori.jar ./src/main/assembly/obf_MedicalClient.xml

echo "deploy finished. All files put into 'deploy/*'"
goto end

:appDebug
call mvn compile
call mvn jar:jar
copy/y .\target\CardReader.jar .\target\deploy\bin
cd .\target\deploy\bin
echo "new jar file created, please test it."
goto end

:exit
exit /b 1

:end
exit /b 0
