ECHO OFF
REM ----------------------------------------------------------------
REM	ATL_F.BAT For Poplar/Anzu_L
REM
REM		フラッシュＲＯＭ書き換え用
REM		ＩＣＥ起動用バッチ・ファイル
REM
REM		T.Nose
REM		1996/11/11
REM ----------------------------------------------------------------

if "%1"=="POPLAR_B"		goto	NEXT1
if "%1"=="POPLAR_H"		goto	NEXT1
if "%1"=="POPLAR_L"		goto	NEXT1
if "%1"=="ANZU_L"		goto	NEXT1
ECHO [モデル名の指定が違います]
goto	ENDHELP

:NEXT1
if "%2"=="JPN"		goto	NEXT2
if "%2"=="USA"		goto	NEXT2
ECHO [国名の指定が違います]
goto	ENDHELP

:NEXT2
set MACHINE=%1
set COUNTRY=%2

rem cd \src\atlanta\%MACHINE%\work\%COUNTRY%
rem cesh704x -I\src\atlanta\ice\%MACHINE%.cfg
cd \src\atlanta\flash\work\\%MACHINE%
cesh704x -I\src\atlanta\ice\flash\%MACHINE%.cfg
goto END

:ENDHELP
ECHO "ATL_F [ﾓﾃﾞﾙ名] [国名]"
ECHO モデル名，国名 は大文字で入力して下さい

:END
ECHO ON
