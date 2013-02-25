@echo off
rem Licensed to the Apache Software Foundation (ASF) under one or more
rem contributor license agreements.  See the NOTICE file distributed with
rem this work for additional information regarding copyright ownership.
rem The ASF licenses this file to You under the Apache License, Version 2.0
rem (the "License"); you may not use this file except in compliance with
rem the License.  You may obtain a copy of the License at
rem
rem     http://www.apache.org/licenses/LICENSE-2.0
rem
rem Unless required by applicable law or agreed to in writing, software
rem distributed under the License is distributed on an "AS IS" BASIS,
rem WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
rem See the License for the specific language governing permissions and
rem limitations under the License.

if "%OS%" == "Windows_NT" setlocal
rem ---------------------------------------------------------------------------
rem Start script for the SMARTCARD Server
rem
rem $Id: startup.bat 895392 2010-01-03 14:02:31Z kkolinko $
rem ---------------------------------------------------------------------------

rem Guess SMARTCARD_HOME if not defined
set "CURRENT_DIR=%cd%"
echo 000-"%CURRENT_DIR%"
if not "%SMARTCARD_HOME%" == "" goto gotHome
echo 111
set "SMARTCARD_HOME=%CURRENT_DIR%"
if exist "%SMARTCARD_HOME%\bin\bccsvr.bat" goto okHome
echo 222
cd ..
set "SMARTCARD_HOME=%cd%"
cd "%CURRENT_DIR%"
echo 333
:gotHome
if exist "%SMARTCARD_HOME%\bin\bccsvr.bat" goto okHome
echo 444
echo The SMARTCARD_HOME environment variable is not defined correctly
echo This environment variable is needed to run this program
goto end
:okHome

set "EXECUTABLE=%SMARTCARD_HOME%\bin\bccsvr.bat"
echo 555
rem Check that target executable exists
if exist "%EXECUTABLE%" goto okExec
echo 666
echo Cannot find "%EXECUTABLE%"
echo This file is needed to run this program
goto end
:okExec
echo 777
rem Get remaining unshifted command line arguments and save them in the
set CMD_LINE_ARGS=
:setArgs
echo 888
if ""%1""=="""" goto doneSetArgs
echo 88811
set CMD_LINE_ARGS=%CMD_LINE_ARGS% %1
shift
goto setArgs
:doneSetArgs
echo 999
call "%EXECUTABLE%" start %CMD_LINE_ARGS%

:end
echo 000000
pause

