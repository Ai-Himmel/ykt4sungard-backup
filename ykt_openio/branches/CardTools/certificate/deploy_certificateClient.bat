@echo off
if "%1"=="debug" goto appDebug
echo "you has been deploy full package,you can use add a param : debug to reduce redeploy times."
echo "debug type: just compile --> jar --> copies."
call mvn clean 
call mvn assembly:assembly -Dmaven.test.skip=true
cd .\target
mkdir deploy

echo "uncompress certificate-bin.zip"
jar xvf certificate-bin.zip

if not "%JAVA_HOME%" == "" goto delpoyJRE
echo JAVA_HOME should point to a JDK in order to run in debug mode.
goto exit

:delpoyJRE
echo "------------ deploy jre files..."
xcopy/s "%JAVA_HOME%\jre\*.*" ".\deploy"
del/q .\deploy\*

:deployAPP
echo "------------ deploy app files..."
copy/y .\certificate\*.dll .\deploy\bin
mkdir .\deploy\bin\Microsoft.VC90.CRT
mkdir .\deploy\bin\Microsoft.VC90.MFC
xcopy/s ".\certificate\Microsoft.VC90.CRT\*.*" .\deploy\bin\Microsoft.VC90.CRT
xcopy/s ".\certificate\Microsoft.VC90.MFC\*.*" .\deploy\bin\Microsoft.VC90.MFC
copy/y .\certificate\kscardinterface_online.dll .\deploy\bin\kscardinterface.dll
copy/y .\certificate\cpack.dat .\deploy\bin
copy/y .\certificate\pub.key .\deploy\bin
copy/y .\certificate\log4j-1.2.16.jar .\deploy\bin
copy/y .\certificate\mytools-1.0-SNAPSHOT.jar .\deploy\bin
copy/y .\certificate\commons-lang-2.6.jar .\deploy\bin
copy/y .\certificate\jnative-1.4.jar .\deploy\bin
copy/y .\certificate\looks-2.1.4.jar .\deploy\bin
copy/y .\certificate\ojdbc14-10.2.0.4.0.jar .\deploy\bin
copy/y .\certificate\poi-3.7.jar .\deploy\bin
copy/y .\certificate\certificateClient.bat .\deploy\bin
copy/y ..\doc\certificateClient.txt .\deploy
copy/y ..\doc\medical.sql .\deploy

:deployLicense
echo "--------- deploy customer license and config files. please modify before using."
copy/y .\certificate\license-sicau.lcs .\deploy\bin\license.lcs
copy/y .\classes\app_config\kscard.ini .\deploy\bin
copy/y .\classes\app_config\kscardinterface.ini .\deploy\bin
copy/y .\classes\app_config\certificateClient.properties .\deploy\bin\CardReader.properties
copy/y .\classes\app_config\log4j.properties .\deploy\bin

cd ..\

echo "make obf main jar"
java -jar -Xmx128m -Xms128m ./src/main/assembly/allatori.jar ./src/main/assembly/obf_MedicalClient.xml

echo "deploy finished. All files put into 'deploy/*'"
goto end

:appDebug
call mvn compile
call mvn jar:jar
copy/y .\target\certificate