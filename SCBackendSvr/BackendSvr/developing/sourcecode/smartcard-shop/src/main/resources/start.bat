@echo off

if "%OS%" == "Windows_NT" setlocal

echo *****启动bccsvr服务器  %date:~0,10% %time:~0,8%*****

set "CURRENT_DIR=%cd%"
set "SMARTCARD_HOME=%cd%"

if "%JAVA_HOME%" == "" goto noJavaHome

set classpath=%classpath%;.;%SMARTCARD_HOME%\lib\*;%SMARTCARD_HOME%\lib\ext\*;
set PATH=%JAVA_HOME%\bin;%PATH%;

echo **********************************************
echo JAVA_HOME="%JAVA_HOME%"
echo CLASSPATH="%CLASSPATH%"
echo **********************************************

java -server -Xms128m -Xmx384m -Djava.library.path=%SMARTCARD_HOME%\lib -Dclass=com.sungard.smartcard.bccsvr.FunctionOne com.sungard.smartcard.bccsvr.ServerBoot
if errorlevel 1 (
echo ----------------------------------------------
echo   ****错误***: 请设置好JAVA_HOME环境变量再运行或者检查你的classpath路径
pause
)
goto end

:noJavaHome
echo ----------------------------------------------
echo   ****错误***: 请设置好JAVA_HOME环境变量再运行或者检查你的classpath路径
goto exit

:exit
pause
exit /b 1

:end
echo *****bccsvr服务器正常启动  %date:~0,10% %time:~0,8%*****
pause
exit /b 0

