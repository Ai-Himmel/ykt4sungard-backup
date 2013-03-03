ECHO OFF
REM ----------------------------------------------------------------
REM	HINOROM.BAT For HINOKI3
REM	1998/10/01  By H.Hirao
REM		�q�n�l�C���[�W�쐬�p�o�b�`�E�t�@�C��
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

rem		���s�h���C�u�`�F�b�N
if exist \src\atlanta\define\product.h		goto DRV_OK
	echo [1;33m�J�����g�̃h���C�u(�{�����[��)���Ⴂ�܂�[0m
	echo [1;33mArisa\usr2�Ŏ��s���ĉ�����[0m
	goto ENDHELP
:DRV_OK


if "%1"=="KEISATSU"		goto	NEXT1
ECHO [���f�����̎w�肪�Ⴂ�܂�]
goto	ENDHELP

:NEXT1

if "%2"=="JPN"	goto	NEXT2

ECHO [�����̎w�肪�Ⴂ�܂�]
goto	ENDHELP

:NEXT2
if "%3"==""		goto	NONAME
goto NEXT3

:NONAME
ECHO [�o�[�W���������w�肵�ĉ������I]
goto	ENDHELP

:NEXT3

set ROOT=\src\atlanta
set MACHINE=%1
set COUNTRY=%2
set WORK_DIRECTORY=\src\atlanta\%MACHINE%\work\%COUNTRY%\rom

cd	%WORK_DIRECTORY%
echo "****************************************************************" >> %BATCHNAME%.log
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%����L�̎����ɂq�n�l���쐬�J�n" >> %BATCHNAME%.log
echo "****************************************************************" >> %BATCHNAME%.log

if exist \src\atlanta\%MACHINE%\work\%COUNTRY%\%MACHINE%.abs		goto VOL_OK
	echo [%1.abs ������܂���[0m
	goto	END
:VOL_OK

echo on
rem ncopy ..\%MACHINE%.abs %3.abs
rem ncopy ..\%MACHINE%.map %3.map
rem Windows NT?��ncopy���ł��Ȃ��̂�xcopy�ɕύX by H.Hirao 1999/05/13
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
CPU�̂q�n�l�쐬
mot2binr 0 4 %3.mot %3.cpu /f >> %BATCHNAME%.log
lha a -w- %3 %WORK_DIRECTORY%\%3.cpu

:NEXT4
makebin 3 200000 11DE000 %3.mot %3.rom
rem mot2binr 200000 1 %3.mot %3.rom /f >> %BATCHNAME%.log
rem mot2binr 1000000 1 %3.mot %3.rom /f >> %BATCHNAME%.log

REM ���Level7�ň��k����̂ŁC
REM ������Level5�ň��k����K�v�͂���܂���
REM lha a -w- %3 %WORK_DIRECTORY%\%3.abs
REM rem lha a -w- %3 %WORK_DIRECTORY%\%3.obj
REM lha a -w- %3 %WORK_DIRECTORY%\%3.map
REM rem lha a -w- %3 %WORK_DIRECTORY%\%3.mot

:END_MSG
echo off
rem echo [1;42;37mCPU�̃o�[�W����[0m
rem checkver %3.cpu 1000
echo [1;42;37mROM�̃o�[�W����[0m
checkver %3.rom 0
echo [1;42;37m�Ă��O�Ɋm�F���Ă�������!![0m
divide8 %3.rom %3.rm0 %3.rm1

REM ���Level7�ň��k����̂ŁC
REM ������Level5�ň��k����K�v�͂���܂���
REM lha a -w- %3 %WORK_DIRECTORY%\%3.rm0
REM lha a -w- %3 %WORK_DIRECTORY%\%3.rm1
echo .
REM sumcheck %3.rm0
REM sumcheck %3.rm1
sumcheck %3.rm?
copy readme.doc readme.txt
echo [1;42;37m���x�@�e�`�w�̂q�n�l�ł��܂����I�I[0m [1;37m�_(^o^)�^[0m
goto END1

:ERROR
echo [1;37;41m�x�@�e�`�w�̂q�n�l�쐬�ُ͈�I�����܂���[0m[1;37m(-_-x[0m
goto END1

:ENDHELP
ECHO "HINOFLA [���ٖ�] [����] [�ް�ޮݖ�] [(CPU)]"
ECHO ���f�����C����, �o�[�W������ �͑啶���œ��͂��ĉ�����
ECHO �b�o�t�����q�n�l�C���[�W���K�v�ȏꍇ�A�b�o�t�ƕt���ĉ�����
goto END3


:END1
cd %WORK_DIRECTORY%
:END2
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%����L�̎����ɂq�n�l�쐬���I��" >> %BATCHNAME%.log

rem mot�͗v��Ȃ��̂ō폜����
del %3.mot

REM ���LZH�ň��k����̂ŏ�����Ă͍���
REM rem abs map rom���v��Ȃ��̂ō폜����
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

