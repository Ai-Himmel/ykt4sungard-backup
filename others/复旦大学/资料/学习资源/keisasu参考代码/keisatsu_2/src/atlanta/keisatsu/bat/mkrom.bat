ECHO OFF
REM ----------------------------------------------------------------
REM	HINOROM.BAT For HINOKI3
REM	1998/10/01  By H.Hirao
REM		‚q‚n‚lƒCƒ[ƒWì¬—pƒoƒbƒ`Eƒtƒ@ƒCƒ‹
REM ----------------------------------------------------------------

set ROOT=
set BATCHNAME=%0
if "%DOS16M%" == ""	goto	SET_DOS16M
goto START

:SET_DOS16M
rem set DOS16M=1,@5M:1024
set DOS16M=0,@5M:1024

:START
set MSG=0

rem		Àsƒhƒ‰ƒCƒuƒ`ƒFƒbƒN
if exist \src\atlanta\define\product.h		goto DRV_OK
	echo [1;33mƒJƒŒƒ“ƒg‚Ìƒhƒ‰ƒCƒu(ƒ{ƒŠƒ…[ƒ€)‚ªˆá‚¢‚Ü‚·[0m
	echo [1;33mArisa\usr2‚ÅÀs‚µ‚Ä‰º‚³‚¢[0m
	goto ENDHELP
:DRV_OK


if "%1"=="KEISATSU"		goto	NEXT1
ECHO [ƒ‚ƒfƒ‹–¼‚Ìw’è‚ªˆá‚¢‚Ü‚·]
goto	ENDHELP

:NEXT1

if "%2"=="JPN"	goto	NEXT2

ECHO [‘–¼‚Ìw’è‚ªˆá‚¢‚Ü‚·]
goto	ENDHELP

:NEXT2
if "%3"==""		goto	NONAME
goto NEXT3

:NONAME
ECHO [ƒo[ƒWƒ‡ƒ“–¼‚ğw’è‚µ‚Ä‰º‚³‚¢I]
goto	ENDHELP

:NEXT3

set ROOT=\src\atlanta
set MACHINE=%1
set COUNTRY=%2
set WORK_DIRECTORY=\src\atlanta\%MACHINE%\work\%COUNTRY%\rom

cd	%WORK_DIRECTORY%
echo "****************************************************************" >> %BATCHNAME%.log
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%‚ªã‹L‚Ì‚É‚q‚n‚l‚ğì¬ŠJn" >> %BATCHNAME%.log
echo "****************************************************************" >> %BATCHNAME%.log

if exist \src\atlanta\%MACHINE%\work\%COUNTRY%\%MACHINE%.abs		goto VOL_OK
	echo [%1.abs ‚ª‚ ‚è‚Ü‚¹‚ñ[0m
	goto	END
:VOL_OK

echo on
rem ncopy ..\%MACHINE%.abs %3.abs
rem ncopy ..\%MACHINE%.map %3.map
rem Windows NT?‚Åncopy‚ª‚Å‚«‚È‚¢‚Ì‚Åxcopy‚É•ÏX by H.Hirao 1999/05/13
rem xcopy ..\%MACHINE%.abs %3.ABS /V /F
rem xcopy ..\%MACHINE%.map %3.MAP /V /F
copy ..\%MACHINE%.abs %3.ABS
copy ..\%MACHINE%.map %3.MAP

:MakeMotFile
cnvs %3.abs %3.mot
echo off

if errorlevel 1 goto ERROR

echo on
rem mot2bin %3.mot %3.cpu /f >> %BATCHNAME%.log
if "%4" == "CPU"	goto MAKE_CPU
goto NEXT4

:MAKE_CPU
CPU‚Ì‚q‚n‚lì¬
mot2binr 0 4 %3.mot %3.cpu /f >> %BATCHNAME%.log
lha a -w- %3 %WORK_DIRECTORY%\%3.cpu

:NEXT4
makebin 3 200000 11DE000 %3.mot %3.rom
rem mot2binr 200000 1 %3.mot %3.rom /f >> %BATCHNAME%.log
rem mot2binr 1000000 1 %3.mot %3.rom /f >> %BATCHNAME%.log

REM Œã‚ÅLevel7‚Åˆ³k‚·‚é‚Ì‚ÅC
REM ‚±‚±‚ÅLevel5‚Åˆ³k‚·‚é•K—v‚Í‚ ‚è‚Ü‚¹‚ñ
REM lha a -w- %3 %WORK_DIRECTORY%\%3.abs
REM rem lha a -w- %3 %WORK_DIRECTORY%\%3.obj
REM lha a -w- %3 %WORK_DIRECTORY%\%3.map
REM rem lha a -w- %3 %WORK_DIRECTORY%\%3.mot

:END_MSG
echo off
rem echo [1;42;37mCPU‚Ìƒo[ƒWƒ‡ƒ“[0m
rem checkver %3.cpu 1000
echo [1;42;37mROM‚Ìƒo[ƒWƒ‡ƒ“[0m
checkver %3.rom 0
echo [1;42;37mÄ‚­‘O‚ÉŠm”F‚µ‚Ä‚­‚¾‚³‚¢!![0m
divide8 %3.rom %3.rm0 %3.rm1

REM Œã‚ÅLevel7‚Åˆ³k‚·‚é‚Ì‚ÅC
REM ‚±‚±‚ÅLevel5‚Åˆ³k‚·‚é•K—v‚Í‚ ‚è‚Ü‚¹‚ñ
REM lha a -w- %3 %WORK_DIRECTORY%\%3.rm0
REM lha a -w- %3 %WORK_DIRECTORY%\%3.rm1
echo .
REM sumcheck %3.rm0
REM sumcheck %3.rm1
sumcheck %3.rm?
copy readme.doc readme.txt
echo [1;42;37mŒx@‚e‚`‚w‚Ì‚q‚n‚l‚Å‚«‚Ü‚µ‚½II[0m [1;37m_(^o^)^[0m
goto END1

:ERROR
echo [1;37;41mŒx@‚e‚`‚w‚Ì‚q‚n‚lì¬‚ÍˆÙíI—¹‚µ‚Ü‚µ‚½[0m[1;37m(-_-x[0m
goto END1

:ENDHELP
ECHO "HINOFLA [ÓÃŞÙ–¼] [‘–¼] [ÊŞ°¼Ş®İ–¼] [(CPU)]"
ECHO ƒ‚ƒfƒ‹–¼C‘–¼, ƒo[ƒWƒ‡ƒ“–¼ ‚Í‘å•¶š‚Å“ü—Í‚µ‚Ä‰º‚³‚¢
ECHO ‚b‚o‚t“à‘ ‚q‚n‚lƒCƒ[ƒW‚ª•K—v‚Èê‡A‚b‚o‚t‚Æ•t‚¯‚Ä‰º‚³‚¢
goto END3


:END1
cd %WORK_DIRECTORY%
:END2
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%‚ªã‹L‚Ì‚É‚q‚n‚lì¬‚ğI—¹" >> %BATCHNAME%.log

rem mot‚Í—v‚ç‚È‚¢‚Ì‚Åíœ‚·‚é
del %3.mot

REM Œã‚ÅLZH‚Åˆ³k‚·‚é‚Ì‚ÅÁ‚³‚ê‚Ä‚Í¢‚é
REM rem abs map rom‚à—v‚ç‚È‚¢‚Ì‚Åíœ‚·‚é
REM del %3.abs
REM del %3.map
REM rem del %3.rom

goto END3
set MACHINE=
set COUNTRY=
set S_MK=
set CHECK=
set MSG=
set ROOT=
set WORK_DIRECTORY=
set BATCHNAME=

:END3
ECHO ON

