@echo off
if "%1"=="debug" goto appDebug
echo "you has been deploy full package,you can use add a param : debug to reduce redeploy times."
echo "debug type: just compile --> jar --> copies."
call mvn clean 
call mvn assembly:assembly -Dmaven.test.skip=true
cd .\target
mkdir deploy

echo "uncompress TicketSys-bin.zip"
jar xvf TicketSys-bin.zip

if not "%JAVA_HOME%" == "" goto delpoyJRE
echo JAVA_HOME should point to a JDK in order to run in debug mode.
goto exit

:delpoyJRE
echo "------------ deploy jre files..."
xcopy/s "%JAVA_HOME%"\jre\*.* .\deploy
del/q .\deploy\*

:deployAPP
echo "------------ deploy app files..."
copy/y .\TicketSys\*.dll .\deploy\bin
copy/y .\TicketSys\kscard.lib .\deploy\bin
copy/y .\TicketSys\cpack.dat .\deploy\bin
copy/y .\TicketSys\ksinfo.db .\deploy\bin
copy/y .\TicketSys\kstrans.db .\deploy\bin
copy/y .\TicketSys\pub.key .\deploy\bin
copy/y .\TicketSys\ksitfcdaemon.exe .\deploy\bin
copy/y .\TicketSys\sli4j-*.jar .\deploy\bin
copy/y .\TicketSys\ojdbc14-10.2.0.4.0.jar .\deploy\bin
copy/y .\TicketSys\hibernate-*.jar .\deploy\bin
copy/y .\TicketSys\persistence-api-1.0.jar .\deploy\bin
copy/y .\TicketSys\cglib-*.jar .\deploy\bin
copy/y .\TicketSys\asm-*.jar .\deploy\bin
copy/y .\TicketSys\javassist-*.jar .\deploy\bin
copy/y .\TicketSys\antlr-2.7.6.jar .\deploy\bin
copy/y .\TicketSys\jta-1.1.jar .\deploy\bin
copy/y .\TicketSys\ehcache-1.2.3.jar .\deploy\bin
copy/y .\TicketSys\slf4j-*.jar .\deploy\bin
copy/y .\TicketSys\log4j-*.jar .\deploy\bin
copy/y .\TicketSys\dom4j-1.6.1.jar .\deploy\bin
copy/y .\TicketSys\jnative-1.4.jar .\deploy\bin
copy/y .\TicketSys\mytools-1.0-SNAPSHOT.jar .\deploy\bin
copy/y .\TicketSys\commons-*.jar .\deploy\bin

rem copy .\TicketSys\TicketSys-1.0-SNAPSHOT.jar .\deploy\bin
copy/y .\TicketSys\TicketServer.bat .\deploy\bin

:deployLicense
echo "--------- deploy customer license and config files. please modify before using."
copy/y .\TicketSys\license-swust.lcs .\deploy\bin\license.lcs
copy/y .\classes\app_config\hibernate.cfg.xml .\deploy\bin
copy/y .\classes\app_config\kscard.ini .\deploy\bin
copy/y .\classes\app_config\kscardinterface.ini .\deploy\bin
copy/y .\classes\app_config\Ticket.properties .\deploy\bin
copy/y .\classes\app_config\log4j.properties .\deploy\bin

cd ..\

echo "make obf main jar"
java -jar -Xmx128m -Xms128m ./src/main/assembly/allatori.jar ./src/main/assembly/obf_TicketSys.xml

echo "deploy finished. All files put into 'deploy/*'"
goto end

:appDebug
call mvn compile
call mvn jar:jar
copy/y .\target\TicketSys.jar .\target\deploy\bin
cd .\target\deploy\bin
echo "new jar file created, please test it."
goto end

:exit
exit /b 1

:end
exit /b 0
