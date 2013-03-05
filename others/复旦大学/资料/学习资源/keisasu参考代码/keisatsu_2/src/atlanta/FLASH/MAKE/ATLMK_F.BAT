ECHO OFF
REM ----------------------------------------------------------------
REM	ATLMK_F.BAT For Poplar/Anzu_L
REM
REM		ÉtÉâÉbÉVÉÖèëÇ´ä∑Ç¶ÇqÇnÇl ÇlÇÅÇãÇÖópÉoÉbÉ`ÅEÉtÉ@ÉCÉã
REM
REM		M.Tachibana
REM		1997/05/17 From ATLMK.BAT
REM ----------------------------------------------------------------

set ROOT=
set BATCHNAME=%0
if "%DOS16M%" == ""	goto	SET_DOS16M
goto START

:SET_DOS16M
rem set DOS16M=1,@5M:1024
set DOS16M=0,@5M:3M

:START
set MSG=0

rem		é¿çsÉhÉâÉCÉuÉ`ÉFÉbÉN
if exist \src\atlanta\define\product.h		goto DRV_OK
	echo [1;33mÉJÉåÉìÉgÇÃÉhÉâÉCÉu(É{ÉäÉÖÅ[ÉÄ)Ç™à·Ç¢Ç‹Ç∑[0m
	echo [1;33mArisa\usr1Ç≈é¿çsÇµÇƒâ∫Ç≥Ç¢[0m
	goto ENDHELP
:DRV_OK


if "%1"=="POPLAR_B"		goto	NEXT1
if "%1"=="POPLAR_H"		goto	NEXT1
if "%1"=="POPLAR_L"		goto	NEXT1
if "%1"=="ANZU_L"		goto	NEXT1
if "%1"=="SAKAKI"		goto	NEXT1
if "%1"=="HINOKI"		goto	NEXT1
if "%1"=="HINOKI2"		goto	NEXT1
if "%1"=="SATSUKI2"		goto	NEXT1
ECHO [ÉÇÉfÉãñºÇÃéwíËÇ™à·Ç¢Ç‹Ç∑]
goto	ENDHELP

:NEXT1

if "%2"=="JPN"		goto	NEXT2
if "%2"=="JP0"		goto	NEXT2
if "%2"=="USA"		goto	NEXT2
if "%2"=="USAMLT"		goto	NEXT2

ECHO [çëñºÇÃéwíËÇ™à·Ç¢Ç‹Ç∑]
goto	ENDHELP

:NEXT2
set ROOT=\src\atlanta
set MACHINE=%1
set COUNTRY=%2
rem set WORK_DIRECTORY=\src\atlanta\%MACHINE%\work\%COUNTRY%
if "%2"== "JP0"	 goto NEXT2A
set WORK_DIRECTORY=\src\atlanta\flash\work\%MACHINE%
goto NEXT2B

REM V851 JG2ÇÃÇΩÇﬂÇ…WORKÉfÉBÉåÉNÉgÉäÇí«â¡Ç∑ÇÈÅBBy Y.Suzuki 1902/06/28
:NEXT2A
set WORK_DIRECTORY=\src\atlanta\flash\work\%MACHINE%\%COUNTRY%

:NEXT2B
cd	%WORK_DIRECTORY%
systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%Ç™è„ãLÇÃéûçèÇ…ÉÅÉCÉNÇäJén" >> %BATCHNAME%.log


rem SHIFT
set S_MK=0
set CHECK=0


if "%3"=="ON"		goto	MESSAGE_ON
goto MODULE_CHECK

:MESSAGE_ON
set MSG=1
SHIFT
goto MODULE_CHECK

:MODULE_CHECK
if "%3"==""			goto	ALL_MODULE
if "%3"=="STOP"		goto	TERMINATE
if "%3"=="LOCATE"	goto	LOCATE_EXEC

goto	COMMON_MODULE

:NOREGIST
ECHO Ç†Ç»ÇΩÇÃéwíËÇµÇΩÉÇÉWÉÖÅ[ÉãÇÕÅAÉÅÉCÉNÉoÉbÉ`ÉtÉ@ÉCÉãÇ…ìoò^Ç≥ÇÍÇƒÇ¢Ç‹ÇπÇÒÅB
ECHO atlmkÇÃëSëÃÉÅÅ[ÉNÇ…í«â¡ÇµÇƒÇ≠ÇæÇ≥Ç¢ÅBÇªÇÃå„Ç±ÇÃèàóùÇâèúÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
goto	END


:COMMON_MODULE
rem --------------------------------
rem	 ÇbÇoÇtã§í ÉÇÉWÉÖÅ[Éãï ÇÃÉäÉìÉN
rem --------------------------------
ECHO [" %3 " ÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\flash\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:CHECK_OTHER_LINK
set S_MK=1
rem echo --------------------------------
rem echo  ëºÇÃÉÇÉWÉÖÅ[ÉãÇ‡ÉäÉìÉNÇµÇ‹Ç∑Ç©
rem echo --------------------------------
SHIFT
goto	MODULE_CHECK

:ALL_MODULE
if "%S_MK%"=="1" GOTO ALL_LINK

rem -----------------------------
rem	 ATLANTA ã§í ÉÇÉWÉÖÅ[Éã
rem -----------------------------
ECHO [ATLANTA ÉtÉâÉbÉVÉÖèëÇ´ä∑Ç¶ÉVÉXÉeÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇeÇkÇ`ÇrÇgÇrÇxÇrÅjÇÃÉäÉìÉN]
rem LOC		..\..\..\flash\make\FLASHSYS.VER
rem make
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\flash\make\FLASHSYS.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉtÉâÉbÉVÉÖ ÉÇÉWÉÖÅ[ÉãÅiÇeÇkÇ`ÇrÇgÅjÇÃÉäÉìÉN]
rem LOC		..\..\..\flash\make\FLASH.VER
rem make
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\flash\make\FLASH.mk
if errorlevel 1 goto ERROR

:ALL_LINK
rem ---------------------
rem	 ATLANTA ëSëÃ ÉäÉìÉN
rem ---------------------
ECHO [ATLANTA ëSëÃÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
rem LOC		..\..\..\flash\make\ATLANTA.VER
rem make
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\flash\make\%MACHINE%.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÇÃÉäÉìÉN]
:LOCATE_EXEC
rem LOCATE Ç™ìØéûÇ…ÇQÉJèäÇ≈é¿çsÇ≥ÇÍÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈëŒçÙ
IF EXIST LOCKFILE.TXT goto NOW_MAKING
echo "åªç›ÇlÇ`ÇjÇdÇé¿çsÇµÇƒÇ¢ÇÈÇÃÇÕ %ID%Ç≥ÇÒÇ≈Ç∑ÅB"> LOCKFILE.TXT
rem	CIM-E MUGEN âêÕóp	Absolute-FileÇÃéwíË
rem	CIM-E MUGEN âêÕóp	Map-FileÇÃéwíË
rem make
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" %ROOT%\flash\make\loc
if errorlevel 1 goto ERROR


:CHECK_DUPLICATE_SYMBOL
rem --------------------------------------
rem	 ÉfÉÖÅ[ÉvÉäÉPÅ[ÉgÅEÉVÉìÉ{ÉãÇÃÉ`ÉFÉbÉN
rem --------------------------------------
ECHO [Check Duplicate Symbol & C_COMMON]

bgrep -n Different *.mp1 > Diff.lst
if errorlevel 1 goto CHECK0
set CHECK=1
goto CHECK0

REM By S.K Dec.15,1995
:CHECK0
REM bgrep -n Different ..\common\*.mp1 >> Diff.lst
REM bgrep -n Different *.mp1 >> Diff.lst
REM if errorlevel 1 goto NEXT_CHECK
REM set CHECK=1
goto NEXT_CHECK

:NEXT_CHECK
REM Added the next line on May.24,1994 By S.K
bgrep -n C_COMMON *.mp1 >> Diff.lst
if errorlevel 1 goto END_MSG

:END_ERR
echo [1;37;41m Duplicate SymbolÇ©C_COMMONÇ™Ç†ÇËÇ‹Ç∑[0m[1;37m(-_-“)[0m
echo [1;37;41m Diff.lstÇ≈ämîFÇµÇƒÇ≠ÇæÇ≥Ç¢[0m
vz Diff.lst
if "%MSG%"=="0" goto END
send "Error to Duplicate & C_COMMON" JUN/%ID% >nul
goto	END

:END_MSG
if "%CHECK%"=="1" GOTO END_ERR
echo [1;42;37mÅùÇlÇÅÇãÇÖÇ≈Ç´Ç‹ÇµÇΩÅIÅI[0m [1;37mÅ_(^o^)Å^[0m
echo 
rem	send "ÇlÇÅÇãÇÖÇÕê≥èÌèIóπÇµÇ‹ÇµÇΩÅB" JUN/%ID% >nul
if "%MSG%"=="0" goto END
send "%MACHINE% %COUNTRY% ÇÃ Make ÇÕê≥èÌèIóπ" JUN/%ID% >nul
goto	END

:ERROR
rem	send "ÇlÇÅÇãÇÖÇÕàŸèÌèIóπÇµÇ‹ÇµÇΩÅB" JUN/%ID% >nul
echo [1;37;41mÇlÇÅÇãÇÖÇÕàŸèÌèIóπÇµÇ‹ÇµÇΩ[0m[1;37m(-_-x[0m
if "%MSG%"=="0" goto END
send "%MACHINE% %COUNTRY% ÇÃ Make ÇÕàŸèÌèIóπ" JUN/%ID% >nul
goto	END

:ENDHELP
ECHO "”ºﬁ≠∞Ÿ“≤∏    Å{€π∞¿∞ Å|ÅÑ ATLMK_F [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <”ºﬁ≠∞Ÿñº>"
ECHO "ëSëÃ“≤∏      Å{€π∞¿∞ Å|ÅÑ ATLMK_F [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON>"
ECHO "             Å{€π∞¿∞ Å|ÅÑ ATLMK_F [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <LOCATE>"
ECHO "”ºﬁ≠∞Ÿ“≤∏ÇÃÇ›        Å|ÅÑ ATLMK_F [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <”ºﬁ≠∞Ÿñº> <STOP>"
ECHO "”ºﬁ≠∞Ÿ“≤∏+*.COD      Å|ÅÑ ATLMK_F [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <”ºﬁ≠∞Ÿñº> <STOP>"
ECHO "_________________________________________________________________________"
ECHO ÉÇÉfÉãñºÅCçëñº, ÉÇÉWÉÖÅ[Éãñº ÇÕëÂï∂éöÇ≈ì¸óÕÇµÇƒâ∫Ç≥Ç¢
ECHO ÉÇÉWÉÖÅ[ÉãÇÕï°êîå¬éwíËèoóàÇ‹Ç∑
ECHO àÍïîï™ÇæÇØÉÅÉCÉNÇµÇΩÇ¢èÍçáÇ…ÇÕ[ÉÇÉWÉÖÅ[Éãñº]ÇÃå„Ç…[ÇrÇsÇnÇo]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
ECHO ÅñÅDÇbÇnÇcÉtÉ@ÉCÉãÇ™ó~ÇµÇ¢èÍçáÇ‡ìØólÇ…[ÉÇÉWÉÖÅ[Éãñº]ÇÃå„Ç…[ÇrÇsÇnÇo]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
ECHO ÉçÉPÅ[É^Å[ÇæÇØé¿çsÇµÇΩÇ¢èÍçáÇ…ÇÕÅA[ÇkÇnÇbÇ`ÇsÇd]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
ECHO ÉÅÉCÉNÇÃèIóπÇÃÉÅÉbÉZÅ[ÉWÇëóÇËÇΩÇ¢ï˚ÇÕ[çëñº]ÇÃå„Ç…[ON]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
if "%MSG%"=="0" goto END2
send "ì¸óÕä‘à·Ç¢Ç≈Ç∑ÅB" JUN/%ID% >nul
goto END3

:NOW_MAKING
if "%MSG%"=="0" goto MAKING1
send "åªç›ÅAëºÇÃêlÇ™ÇlÇ`ÇjÇdíÜÇ≈Ç∑ÅB" JUN/%ID% >nul
:MAKING1
ECHO åªç›ÅAà»â∫ÇÃêlÇ™ÇlÇ`ÇjÇdíÜÇ≈Ç∑ÅB
type lockfile.txt
goto END2

:TERMINATE
if "%MSG%"=="0" goto MSG_TERMINATE
send "éwíËï™ÇÃÉÅÉCÉNÇÕê≥èÌèIóπÇµÇ‹ÇµÇΩÅB" JUN/%ID% >nul
:MSG_TERMINATE
ECHO éwíËï™ÇÃÉÅÉCÉNÇÕê≥èÌèIóπÇµÇ‹ÇµÇΩÅB
goto END2

:END
cd %WORK_DIRECTORY%
REM By Eguchi 1996/02/19 del *.cod
REM del *.cod
del lockfile.txt
:END2
systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "		%0 %1 %2 %3 %4 %5 %6 %ID%Ç™è„ãLÇÃéûçèÇ…ÉÅÉCÉNÇèIóπ" >> %BATCHNAME%.log

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

