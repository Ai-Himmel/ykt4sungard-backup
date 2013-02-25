@echo off

if "%OS%" == "Windows_NT" setlocal

echo TEMP "%TEMP%"
rem Suppress Terminate batch job on CTRL+C
if not ""%1"" == ""run"" goto mainEntry
if ""%TEMP%"" == """" goto mainEntry
if exist "%TEMP%\%~nx0.run" goto mainEntry
echo Y>"%TEMP%\%~nx0.run"
if not exist "%TEMP%\%~nx0.run" goto mainEntry
echo Y>"%TEMP%\%~nx0.Y"
call "%~f0" %* <"%TEMP%\%~nx0.Y"
rem Use provided errorlevel
set RETVAL=%ERRORLEVEL%
del /Q "%TEMP%\%~nx0.Y" >NUL 2>&1
exit /B %RETVAL%
:mainEntry
echo TEMP "222"
del /Q "%TEMP%\%~nx0.run" >NUL 2>&1

rem Guess SMARTCARD_HOME if not defined
set "CURRENT_DIR=%cd%"
if not "%SMARTCARD_HOME%" == "" goto gotHome
set "SMARTCARD_HOME=%CURRENT_DIR%"
if exist "%SMARTCARD_HOME%\bin\bccsvr.bat" goto okHome
cd ..
set "SMARTCARD_HOME=%cd%"
cd "%CURRENT_DIR%"
:gotHome
if exist "%SMARTCARD_HOME%\bin\bccsvr.bat" goto okHome
echo The SMARTCARD_HOME environment variable is not defined correctly
echo This environment variable is needed to run this program
goto end
:okHome
rem Ensure that any user defined CLASSPATH variables are not used on startup,
rem but allow them to be specified in setenv.bat, in rare case when it is needed.
set CLASSPATH=

rem Get standard environment variables
if "%SMARTCARD_BASE%" == "" goto gotSetenvHome
if exist "%SMARTCARD_BASE%\bin\setenv.bat" call "%SMARTCARD_BASE%\bin\setenv.bat"
goto gotSetenvBase
:gotSetenvHome
if exist "%SMARTCARD_HOME%\bin\setenv.bat" call "%SMARTCARD_HOME%\bin\setenv.bat"
:gotSetenvBase

rem Get standard Java environment variables
if exist "%SMARTCARD_HOME%\bin\setclasspath.bat" goto okSetclasspath
echo Cannot find "%SMARTCARD_HOME%\bin\setclasspath.bat"
echo This file is needed to run this program
goto end
:okSetclasspath
set "BASEDIR=%SMARTCARD_HOME%"
call "%SMARTCARD_HOME%\bin\setclasspath.bat" %1
if errorlevel 1 goto end

rem Add on extra jar file to CLASSPATH
rem Note that there are no quotes as we do not want to introduce random
rem quotes into the CLASSPATH
if "%CLASSPATH%" == "" goto emptyClasspath
set "CLASSPATH=%CLASSPATH%;"
:emptyClasspath
set "CLASSPATH=%CLASSPATH%%SMARTCARD_HOME%\bin\bootstrap.jar"
if not "%SMARTCARD_BASE%" == "" goto gotBase
set "SMARTCARD_BASE=%SMARTCARD_HOME%"
:gotBase

if not "%SMARTCARD_TMPDIR%" == "" goto gotTmpdir
set "SMARTCARD_TMPDIR=%SMARTCARD_BASE%\temp"
:gotTmpdir

rem Add tomcat-juli.jar to classpath
rem tomcat-juli.jar can be over-ridden per instance
if not exist "%SMARTCARD_BASE%\bin\tomcat-juli.jar" goto juliClasspathHome
set "CLASSPATH=%CLASSPATH%;%SMARTCARD_BASE%\bin\tomcat-juli.jar"
goto juliClasspathDone
:juliClasspathHome
set "CLASSPATH=%CLASSPATH%;%SMARTCARD_HOME%\bin\tomcat-juli.jar"
:juliClasspathDone

if not "%LOGGING_CONFIG%" == "" goto noJuliConfig
set LOGGING_CONFIG=-Dnop
if not exist "%SMARTCARD_BASE%\conf\logging.properties" goto noJuliConfig
set LOGGING_CONFIG=-Djava.util.logging.config.file="%SMARTCARD_BASE%\conf\logging.properties"
:noJuliConfig
set JAVA_OPTS=%JAVA_OPTS% %LOGGING_CONFIG%

if not "%LOGGING_MANAGER%" == "" goto noJuliManager
set LOGGING_MANAGER=-Djava.util.logging.manager=org.apache.juli.ClassLoaderLogManager
:noJuliManager
set JAVA_OPTS=%JAVA_OPTS% %LOGGING_MANAGER%

rem ----- Execute The Requested Command ---------------------------------------

echo Using SMARTCARD_BASE:   "%SMARTCARD_BASE%"
echo Using SMARTCARD_HOME:   "%SMARTCARD_HOME%"
echo Using SMARTCARD_TMPDIR: "%SMARTCARD_TMPDIR%"
if ""%1"" == ""debug"" goto use_jdk
echo Using JRE_HOME:        "%JRE_HOME%"
goto java_dir_displayed
:use_jdk
echo Using JAVA_HOME:       "%JAVA_HOME%"
:java_dir_displayed
echo Using CLASSPATH:       "%CLASSPATH%"

set _EXECJAVA=%_RUNJAVA%
set MAINCLASS=org.apache.catalina.startup.Bootstrap
set ACTION=start
set SECURITY_POLICY_FILE=
set DEBUG_OPTS=
set JPDA=

if not ""%1"" == ""jpda"" goto noJpda
set JPDA=jpda
if not "%JPDA_TRANSPORT%" == "" goto gotJpdaTransport
set JPDA_TRANSPORT=dt_socket
:gotJpdaTransport
if not "%JPDA_ADDRESS%" == "" goto gotJpdaAddress
set JPDA_ADDRESS=8000
:gotJpdaAddress
if not "%JPDA_SUSPEND%" == "" goto gotJpdaSuspend
set JPDA_SUSPEND=n
:gotJpdaSuspend
if not "%JPDA_OPTS%" == "" goto gotJpdaOpts
set JPDA_OPTS=-agentlib:jdwp=transport=%JPDA_TRANSPORT%,address=%JPDA_ADDRESS%,server=y,suspend=%JPDA_SUSPEND%
:gotJpdaOpts
shift
:noJpda

if ""%1"" == ""debug"" goto doDebug
if ""%1"" == ""run"" goto doRun
if ""%1"" == ""start"" goto doStart
if ""%1"" == ""stop"" goto doStop
if ""%1"" == ""version"" goto doVersion

echo Usage:  catalina ( commands ... )
echo commands:
echo   debug             Start Catalina in a debugger
echo   debug -security   Debug Catalina with a security manager
echo   jpda start        Start Catalina under JPDA debugger
echo   run               Start Catalina in the current window
echo   run -security     Start in the current window with security manager
echo   start             Start Catalina in a separate window
echo   start -security   Start in a separate window with security manager
echo   stop              Stop Catalina
echo   version           What version of tomcat are you running?
goto end

:doDebug
shift
set _EXECJAVA=%_RUNJDB%
set DEBUG_OPTS=-sourcepath "%SMARTCARD_HOME%\..\..\java"
if not ""%1"" == ""-security"" goto execCmd
shift
echo Using Security Manager
set "SECURITY_POLICY_FILE=%SMARTCARD_BASE%\conf\catalina.policy"
goto execCmd

:doRun
shift
if not ""%1"" == ""-security"" goto execCmd
shift
echo Using Security Manager
set "SECURITY_POLICY_FILE=%SMARTCARD_BASE%\conf\catalina.policy"
goto execCmd

:doStart
shift
if not "%OS%" == "Windows_NT" goto noTitle
if "%TITLE%" == "" set TITLE=Tomcat
set _EXECJAVA=start "%TITLE%" %_RUNJAVA%
goto gotTitle
:noTitle
set _EXECJAVA=start %_RUNJAVA%
:gotTitle
if not ""%1"" == ""-security"" goto execCmd
shift
echo Using Security Manager
set "SECURITY_POLICY_FILE=%SMARTCARD_BASE%\conf\catalina.policy"
goto execCmd

:doStop
shift
set ACTION=stop
set CATALINA_OPTS=
goto execCmd

:doVersion
%_EXECJAVA% -classpath "%SMARTCARD_HOME%\lib\catalina.jar" org.apache.catalina.util.ServerInfo
goto end


:execCmd
rem Get remaining unshifted command line arguments and save them in the
set CMD_LINE_ARGS=
:setArgs
if ""%1""=="""" goto doneSetArgs
set CMD_LINE_ARGS=%CMD_LINE_ARGS% %1
shift
goto setArgs
:doneSetArgs

rem Execute Java with the applicable properties
if not "%JPDA%" == "" goto doJpda
if not "%SECURITY_POLICY_FILE%" == "" goto doSecurity
%_EXECJAVA% %JAVA_OPTS% %CATALINA_OPTS% %DEBUG_OPTS% -Djava.endorsed.dirs="%JAVA_ENDORSED_DIRS%" -classpath "%CLASSPATH%" -Dcatalina.base="%SMARTCARD_BASE%" -Dcatalina.home="%SMARTCARD_HOME%" -Djava.io.tmpdir="%SMARTCARD_TMPDIR%" %MAINCLASS% %CMD_LINE_ARGS% %ACTION%
goto end
:doSecurity
%_EXECJAVA% %JAVA_OPTS% %CATALINA_OPTS% %DEBUG_OPTS% -Djava.endorsed.dirs="%JAVA_ENDORSED_DIRS%" -classpath "%CLASSPATH%" -Djava.security.manager -Djava.security.policy=="%SECURITY_POLICY_FILE%" -Dcatalina.base="%SMARTCARD_BASE%" -Dcatalina.home="%SMARTCARD_HOME%" -Djava.io.tmpdir="%SMARTCARD_TMPDIR%" %MAINCLASS% %CMD_LINE_ARGS% %ACTION%
goto end
:doJpda
if not "%SECURITY_POLICY_FILE%" == "" goto doSecurityJpda
%_EXECJAVA% %JAVA_OPTS% %CATALINA_OPTS% %JPDA_OPTS% %DEBUG_OPTS% -Djava.endorsed.dirs="%JAVA_ENDORSED_DIRS%" -classpath "%CLASSPATH%" -Dcatalina.base="%SMARTCARD_BASE%" -Dcatalina.home="%SMARTCARD_HOME%" -Djava.io.tmpdir="%SMARTCARD_TMPDIR%" %MAINCLASS% %CMD_LINE_ARGS% %ACTION%
goto end
:doSecurityJpda
%_EXECJAVA% %JAVA_OPTS% %CATALINA_OPTS% %JPDA_OPTS% %DEBUG_OPTS% -Djava.endorsed.dirs="%JAVA_ENDORSED_DIRS%" -classpath "%CLASSPATH%" -Djava.security.manager -Djava.security.policy=="%SECURITY_POLICY_FILE%" -Dcatalina.base="%SMARTCARD_BASE%" -Dcatalina.home="%SMARTCARD_HOME%" -Djava.io.tmpdir="%SMARTCARD_TMPDIR%" %MAINCLASS% %CMD_LINE_ARGS% %ACTION%
goto end

:end
pause