@echo off&setlocal EnableDelayedExpansion 
set currdir=%~dp0

if "%1"=="" goto usage
if "%1"=="/?" goto usage
if "%1"=="help" goto usage 

if not exist "%currdir%*.lcs" (
  echo license file not exist. please put it to %currdir%. 
  echo if you has not it, please contact with development.
  goto end
)

taskkill /F /IM iexplore.exe
regsvr32 /s /u %windir%\system32\RF35OCX.ocx
echo copying dll to windows system32 directory...
copy/y *.dll  %windir%\system32
copy/y *.ini  %windir%\system32
copy/y *.lcs  %windir%\system32
copy/y *.ocx  %windir%\system32
copy/y *.data  %windir%\system32
copy/y *.key  %windir%\system32
copy/y *.dat  %windir%\system32


echo register %windir%\system32\RF35OCX.ocx to your system
regsvr32 /s %windir%\system32\RF35OCX.ocx

echo dll update over.

if exist "firstrun.html" (
  del firstrun.html
)
for /f "delims=" %%b in ('type %currdir%firstrun.html.orig') do ( 
  set "str=%%b"&set "str=!str:$(targetURL)=%1!"
  echo !str! >>%currdir%firstrun.html
) 
echo config "%currdir%firstrun.html" ok.

reg add hkcu\software\microsoft\windows\currentversion\run /v SungardYKT /t reg_sz /d %currdir%bin\project1.exe /f
echo It is successful to add checkNet into startup.

goto end

:usage
echo please input a parameter of target url.
echo like:  %currdir%%0  http://192.168.0.1:8080/smartcardweb

:end
