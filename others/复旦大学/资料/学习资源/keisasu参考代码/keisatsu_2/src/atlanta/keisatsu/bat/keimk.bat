ECHO OFF
REM ----------------------------------------------------------------
REM	ATLMK.BAT For Poplar/Anzu_L
REM
REM		ÇlÇÅÇãÇÖópÉoÉbÉ`ÅEÉtÉ@ÉCÉã
REM
REM		M.Kotani
REM		1996/10/23 From APRCT.BAT
REM ----------------------------------------------------------------

set ROOT=
set BATCHNAME=%0
set ID=%USERNAME%

if "%DOS16M%" == ""	goto	SET_DOS16M
goto START

:SET_DOS16M
rem set DOS16M=1,@5M:1024
rem set DOS16M=0,@5M:3M

:START
set MSG=0

rem		é¿çsÉhÉâÉCÉuÉ`ÉFÉbÉN
if exist \src\atlanta\define\product.h		goto DRV_OK
	echo [1;33mÉJÉåÉìÉgÇÃÉhÉâÉCÉu(É{ÉäÉÖÅ[ÉÄ)Ç™à·Ç¢Ç‹Ç∑[0m
	echo [1;33mArisa\usr1Ç≈é¿çsÇµÇƒâ∫Ç≥Ç¢[0m
	goto ENDHELP
:DRV_OK


if "%1"=="KEISATSU"		goto	NEXT1
ECHO [ÉÇÉfÉãñºÇÃéwíËÇ™à·Ç¢Ç‹Ç∑]
goto	ENDHELP

:NEXT1

if "%2"=="JPN"	goto	NEXT2
ECHO [çëñºÇÃéwíËÇ™à·Ç¢Ç‹Ç∑]
goto	ENDHELP

:NEXT2
set ROOT=\src\atlanta
set MACHINE=%1
set COUNTRY=%2
set WORK_DIRECTORY=\src\atlanta\%MACHINE%\work\%COUNTRY%

REM WORK_DIRECTORY
cd	%WORK_DIRECTORY%
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%Ç™è„ãLÇÃéûçèÇ…ÉÅÉCÉNÇäJén" >> %BATCHNAME%.log

REM	by O.kimoto 1997/06/12
set MDM_R288F=2

REM	by O.kimoto 1997/08/12
set OPR_KANJI=0

REM Ãﬂÿ›¿ÇÃêÿÇËï™ÇØ
set MDM_SP322=2

REM	ÇgÇhÇmÇnÇjÇhå≈óLÉfÅ[É^ÉÅÉCÉN	/*  By O.Kimoto 1998/09/21 */
set HINOKI_DATA=1

REM	ÉiÉìÉoÅ[ÉfÉBÉXÉvÉåÉCÇÃÉÅÉCÉN by H.Hirao 1999/01/12
set ND=0
if "COUNTRY"=="JPN"			set ND=1
if "COUNTRY"=="HONCHO"		set ND=1
if "COUNTRY"=="KOBAN"		set ND=1

rem SHIFT
set S_MK=0


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
if "%3"=="IFAX"	goto	NOREGIST
if "%3"=="SHDATA"	goto	NEW_MASK_MODULE
if "%3"=="SHTABLE"	goto	NEW_MASK_MODULE
if "%3"=="INI"		goto	NEW_MASK_MODULE
if "%3"=="MON"		goto	NEW_MASK_MODULE
if "%3"=="SCD"		goto	NEW_MASK_MODULE
if "%3"=="INT"		goto	NEW_MASK_MODULE
if "%3"=="HINO_INT"	goto	NEW_MASK_MODULE
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
if "%3" == "MDM" goto MDM_MAKE
if "%3" == "mdm" goto MDM_MAKE
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:UNIQUE_MODULE
rem --------------------------------
rem	 ÇbÇoÇtàÀë∂ÉÇÉWÉÖÅ[Éãï ÇÃÉäÉìÉN
rem --------------------------------
ECHO [" %MACHINE%  %3 " ÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:NEW_MASK_MODULE
rem --------------------------------
rem	 ÇbÇoÇtàÀë∂ÉÇÉWÉÖÅ[Éãï ÇÃÉäÉìÉN
rem --------------------------------
ECHO [" %MACHINE%  %3 " ÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:COUNTRY_MODULE
rem ----------------------------------
rem	 äeçëédólàÀë∂ÉÇÉWÉÖÅ[Éãï ÇÃÉäÉìÉN
rem ----------------------------------
ECHO [" %MACHINE%  %COUNTRY% %3 " ÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%3.mk
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
ECHO [ATLANTA É_ÉCÉÑÉâ ÉÇÉWÉÖÅ[ÉãÅiÇ`ÇsÇcÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\ATD.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ïÑçÜèàóù ÉÇÉWÉÖÅ[ÉãÅiÇbÇcÇbÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\CDC.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ã§í ä÷êî ÉÇÉWÉÖÅ[ÉãÅiÇbÇlÇmÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\CMN.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ã§í ÉfÅ[É^ ÉÇÉWÉÖÅ[ÉãÅiÇcÇ`ÇsÇ`ÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\DATA.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA í êMéËèá ÉÇÉWÉÖÅ[ÉãÅiÇeÇbÇlÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FCM.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA í êMÉRÉìÉpÉ`É`ÉFÉbÉN ÉÇÉWÉÖÅ[ÉãÅiÇeÇbÇlÅQÇbÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FCM_COMP.mk
if errorlevel 1 goto ERROR

rem ÇgÇhÇmÇnÇjÇhÇÕÇhÇcÇoÇÕégópÇµÇ‹ÇπÇÒÅBBy O.Kimoto 1998/09/07
rem ECHO [ATLANTA âÊëúèàóù ÉÇÉWÉÖÅ[ÉãÅiÇhÇcÇoÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\IDP.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉäÉXÉg ÉÇÉWÉÖÅ[ÉãÅiÇkÇrÇsÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\lst.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉäÉXÉgÉèÅ[ÉfÉBÉìÉO ÉÇÉWÉÖÅ[ÉãÅiÇkÇrÇsÅQÇvÇqÇcÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\lstword.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ã§í ÉÅÉCÉì ÉÇÉWÉÖÅ[ÉãÅiÇlÇ`ÇmÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MAN.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ÉÇÉfÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇlÇcÇlÅjÇÃÉäÉìÉN]	ã@éÌàÀë∂ÇÃï˚Ç…éùÇ¡ÇƒÇ¢Ç≠ 1997/02/15	 By T.Yamaguchi
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉÅÉÇÉää«óù ÉÇÉWÉÖÅ[ÉãÅiÇlÇdÇlÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MEM.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA âÒê¸äƒéãÉÇÉWÉÖÅ[ÉãÅiÇmÇbÇtÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\NCU.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉIÉyÉåÅ[ÉVÉáÉì ÉÇÉWÉÖÅ[ÉãÅiÇnÇoÇqÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPR.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ï\é¶ÉèÅ[ÉfÉbÉìÉO ÉÇÉWÉÖÅ[ÉãÅiÇnÇoÇqÅQÇvÇqÇcÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPRWORD.mk
if errorlevel 1 goto ERROR

#ECHO [ATLANTA ÉWÉÉÅ[ÉiÉãì¡ãñ ÉÇÉWÉÖÅ[ÉãÅiÇoÇ`ÇsÅjÇÃÉäÉìÉN]
#nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\pat.mk
#if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉvÉäÉìÉ^ ÉÇÉWÉÖÅ[ÉãÅiÇoÇqÇmÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRINT.mk
rem if errorlevel 1 goto ERROR

rem HINOKIÇÕÉXÉLÉÉÉiÅ[ÇÕï ÉÇÉWÉÖÅ[ÉãÇ≈Ç∑ÅB
rem ECHO [ATLANTA ÉXÉLÉÉÉi ÉÇÉWÉÖÅ[ÉãÅiÇrÇbÇmÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\SCN.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ã§í ÇqÇnÇlÉeÅ[ÉuÉãÅiÇsÇ`ÇaÇkÇdÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\TABLE.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÇcÇlÇ` ÉÇÉWÉÖÅ[ÉãÅiÇcÇlÇ`ÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\DMA.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ÇcÇoÇqÇ`ÇlÉÇÉWÉÖÅ[ÉãÅiÇcÇoÇqÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\DPR.mk
rem if errorlevel 1 goto ERROR

rem ECHO [ATLANTA âÒì]éÛêMÉÇÉWÉÖÅ[ÉãÅiÇqÇnÇsÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\ROT.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA S1ÉÇÉWÉÖÅ[ÉãÅiÇrÇPÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\s1.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÇQâÒê¸ÉÇÉWÉÖÅ[ÉãÅiÇlÇtÇkÇsÇhÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MULTI.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ÉNÉâÉXÇPÉÇÉWÉÖÅ[ÉãÅiÇbÇkÇPÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\CL1.mk
rem if errorlevel 1 goto ERROR

REM ECHO [ATLANTA ÉCÉìÉ^Å[ÉlÉbÉgÇeÇ`ÇwÉÇÉWÉÖÅ[ÉãÅiÇhÇeÇ`ÇwÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\IFAX.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉtÉâÉbÉVÉÖ ÉÇÉWÉÖÅ[ÉãÅiÇeÇkÇ`ÇrÇgÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FLASH.mk
if errorlevel 1 goto ERROR

rem -----------------------------
rem	 ATLANTA ÇbÇoÇtàÀë∂ÉÇÉWÉÖÅ[Éã
rem -----------------------------
ECHO [ATLANTA ÇbÇoÇtàÀë∂ÉfÅ[É^ ÉÇÉWÉÖÅ[ÉãÅiÇrÇgÇcÇ`ÇsÇ`ÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\SHDATA.mk
if errorlevel 1 goto ERROR

rem ÇgÇhÇmÇnÇjÇhÇÕÇmÇÖÇóÇlÇÅÇìÇãÇÃà◊ÅAÇlÇÅÇãÇÖÉtÉ@ÉCÉãïœçX
rem ECHO [ATLANTA ÉXÉ^Å[Ég ÉÇÉWÉÖÅ[ÉãÅiÇhÇmÇhÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\INI.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉXÉ^Å[Ég ÉÇÉWÉÖÅ[ÉãÅiÇhÇmÇhÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\INI.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA äÑçûÇ› ÉÇÉWÉÖÅ[ÉãÅiÇhÇmÇsÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\hino_int.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÉÇÉjÉ^ ÉÇÉWÉÖÅ[ÉãÅiÇlÇnÇmÅjÇÃÉäÉìÉN]
rem ÇgÇhÇmÇnÇjÇhÇÕÇmÇÖÇóÇlÇÅÇìÇãÇÃà◊ÅAÇlÇÅÇãÇÖÉtÉ@ÉCÉãïœçX
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\MON.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ÇbÇoÇtàÀë∂ÉeÅ[ÉuÉãÅiÇrÇgÇsÇ`ÇaÇkÇdÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\SHTABLE.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ÇrÇbÇcÉÇÉWÉÖÅ[ÉãÅiÇrÇbÇcÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\SCD.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ÇiÇaÇhÇfÉÇÉWÉÖÅ[ÉãÅiÇiÇaÇfÅjÇÃÉäÉìÉN]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\JBG.mk
rem if errorlevel 1 goto ERROR

rem -----------------------------
rem	 ATLANTA ã@éÌàÀë∂ÉÇÉWÉÖÅ[Éã
rem -----------------------------

if "%OPR_KANJI%"=="1" goto OPR_KANJI_MAKE

ECHO [ATLANTA ÇQçsÉIÉyÉåÅ[ÉVÉáÉì ÉÇÉWÉÖÅ[ÉãÅiÇnÇoÇqÅ@Ç`ÇmÇjÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPR_ANK.mk
if errorlevel 1 goto ERROR
goto OPR_MAKE_END

:OPR_KANJI_MAKE
ECHO [ATLANTA ÇSçsÉIÉyÉåÅ[ÉVÉáÉì ÉÇÉWÉÖÅ[ÉãÅiÇnÇoÇqÅ@ÇjÇ`ÇmÇiÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPR_KANJ.mk
if errorlevel 1 goto ERROR
goto OPR_MAKE_END

:OPR_MAKE_END
if "%MDM_SP322%"=="1" goto PRN_SP322_MAKE
if "%MDM_SP322%"=="2" goto PRN_IUTHERML_MAKE

ECHO [ATLANTA ÇoÇgÇRÉvÉäÉìÉ^ ÉÇÉWÉÖÅ[ÉãÅiÇoÇqÇmÅQÇoÇgÇRÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRN_PH3.mk
if errorlevel 1 goto ERROR
goto PRN_MAKE_END

:PRN_SP322_MAKE
ECHO [ATLANTA ÇrÇoÇRÇQÇQÉvÉäÉìÉ^ ÉÇÉWÉÖÅ[ÉãÅiÇoÇqÇmÅQÇrÇoÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRN_SP.mk
if errorlevel 1 goto ERROR
goto PRN_MAKE_END

:PRN_IUTHERML_MAKE
ECHO [ATLANTA ÇhÇtÅQÇsÇgÇdÇqÇlÇ`ÇkÉvÉäÉìÉ^ ÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRN_IUTH.mk
if errorlevel 1 goto ERROR
goto PRN_MAKE_END

:PRN_MAKE_END

:MDM_MAKE

if "%MDM_R288F%"=="1" goto MDM_R288F_MAKE
if "%MDM_R288F%"=="2" goto MDM_FM336_MAKE
if "%MDM_R288F%"=="3" goto MDM_MN195006		/* èºâ∫ÉÇÉfÉÄÇÉäÉìÉNÇ∑ÇÈ */

:MDM_ORANGE_MAKE
ECHO [ATLANTA ÉÇÉfÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇlÇcÇl_ÇnÇqÇmÇfÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM_orng.mk
if errorlevel 1 goto ERROR
goto MDM_END

:MDM_R288F_MAKE
ECHO [ATLANTA ÉÇÉfÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇlÇcÇl_ÇqÇQÇWÇWÇeÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM_R288.mk
if errorlevel 1 goto ERROR
goto FCM_V34

:MDM_FM336_MAKE
ECHO [ATLANTA ÉÇÉfÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇlÇcÇlÅQÇeÇlÇRÇRÇUÅjÇÃÉäÉìÉN]
NMAKE "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM.mk
if errorlevel 1 goto ERROR
goto FCM_V34

:MDM_MN195006
ECHO [ATLANTA ÉÇÉfÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇlÇmÇPÇXÇTÇOÇOÇUÅjÇÃÉäÉìÉN]
NMAKE "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM_MN195006.mk
if errorlevel 1 goto ERROR


:FCM_V34
ECHO [ATLANTA ÉÇÉfÉÄ ÉÇÉWÉÖÅ[ÉãÅiÇeÇbÇlÅQÇuÇRÇSÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FCM_V34.mk
if errorlevel 1 goto ERROR
goto MDM_END

:MDM_END

if "%HINOKI_DATA%"=="0" goto IU_DATA_END

:HINOKI_DATA_START
ECHO [HINOKI å≈óLÉfÅ[É^ÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\iu_data.mk
if errorlevel 1 goto ERROR

ECHO [ÇgÇhÇmÇnÇjÇh ÇrÇbÇmÉÇÉWÉÖÅ[ÉãÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\scn_hino.mk
if errorlevel 1 goto ERROR

goto IU_DATA_END

:IU_DATA_END


if "%MDM_R288F%"=="3" goto ND_MN195006		/* èºâ∫ÉÇÉfÉÄÇÉäÉìÉNÇ∑ÇÈ */
goto ND_FM336

:ND_FM336
ECHO [ATLANTA ÇmÇïÇçÇÇÇÖÇíÇcÇâÇìÇêÇåÇÅÇôÅiÇmÇcÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\nd_336.mk
if errorlevel 1 goto ERROR

goto ND_END


:ND_MN195006
ECHO [ATLANTA ÇmÇïÇçÇÇÇÖÇíÇcÇâÇìÇêÇåÇÅÇôÅiÇmÇcÅjÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\nd_195006.mk
if errorlevel 1 goto ERROR

goto ND_END


:ND_END

goto	ALL_LINK

:ALL_LINK
rem ##################################By M.Tachibana 1998/06/02
if "%COUNTRY%"=="JP1" goto ALL1_LINK
if "%COUNTRY%"=="JP2" goto ALL1_LINK
rem ##################################
rem ---------------------
rem	 ATLANTA ëSëÃ ÉäÉìÉN
rem ---------------------
ECHO [ATLANTA ëSëÃÉÇÉWÉÖÅ[ÉãÇÃÉäÉìÉN]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%MACHINE%.mk
if errorlevel 1 goto ERROR

rem ##################################
goto LOCATE_EXEC
:ALL1_LINK
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%COUNTRY%\%MACHINE%.mk
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%MACHINE%.mk
if errorlevel 1 goto ERROR
rem ##################################

ECHO [ATLANTA ÇÃÉäÉìÉN]
:LOCATE_EXEC
rem ##################################By M.Tachibana 1998/06/02
rem if "%COUNTRY%"=="JP1" goto LOCATE1_EXEC
if "%COUNTRY%"=="JP2" goto LOCATE1_EXEC
rem ##################################
rem LOCATE Ç™ìØéûÇ…ÇQÉJèäÇ≈é¿çsÇ≥ÇÍÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈëŒçÙ
IF EXIST LOCKFILE.TXT goto NOW_MAKING
echo "åªç›ÇlÇ`ÇjÇdÇé¿çsÇµÇƒÇ¢ÇÈÇÃÇÕ %ID%Ç≥ÇÒÇ≈Ç∑ÅB"> LOCKFILE.TXT
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" %ROOT%\make\loc
if errorlevel 1 goto ERROR

rem ##################################
goto CHECK_DUPLICATE_SYMBOL
:LOCATE1_EXEC
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" %ROOT%\make\%COUNTRY%\loc
if errorlevel 1 goto ERROR
rem ##################################

:CHECK_DUPLICATE_SYMBOL
rem --------------------------------------
rem	 ÉfÉÖÅ[ÉvÉäÉPÅ[ÉgÅEÉVÉìÉ{ÉãÇÃÉ`ÉFÉbÉN
rem --------------------------------------
ECHO [Check Duplicate Symbol]
bgrep -n CANNOT %WORK_DIRECTORY%\%MACHINE%.map > %WORK_DIRECTORY%\Diff.txt
bgrep -n UNDEFINED %WORK_DIRECTORY%\%MACHINE%.map >> %WORK_DIRECTORY%\Diff.txt
bgrep -n DUPLICATE %WORK_DIRECTORY%\%MACHINE%.map >> %WORK_DIRECTORY%\Diff.txt
if errorlevel 1 goto END_MSG
goto END_ERR



:END_ERR
echo Duplicate Duplicate SymbolÇ™Ç†ÇËÇ‹Ç∑(-_-“)
echo %WORK_DIRECTORY%\Diff.txtÇ≈ämîFÇµÇƒÇ≠ÇæÇ≥Ç¢
if "%MSG%"=="0" goto END
rem net send "Error to Duplicate & C_COMMON" %ID% >nul
goto END



:END_MSG
echo ÅùÇlÇÅÇãÇÖÇ≈Ç´Ç‹ÇµÇΩÅIÅIÅ_(^o^)Å^
echo 
rem net send "ÇlÇÅÇãÇÖÇÕê≥èÌèIóπÇµÇ‹ÇµÇΩÅB" %ID% >nul
if "%MSG%"=="0" goto END
rem net send "%MACHINE% %COUNTRY% ÇÃ Make ÇÕê≥èÌèIóπ" %ID% >nul
goto	END



:ERROR
rem	net send "ÇlÇÅÇãÇÖÇÕàŸèÌèIóπÇµÇ‹ÇµÇΩÅB" %ID% >nul
echo ÇlÇÅÇãÇÖÇÕàŸèÌèIóπÇµÇ‹ÇµÇΩ(-_-x
if "%MSG%"=="0" goto END
rem net send "%MACHINE% %COUNTRY% ÇÃ Make ÇÕàŸèÌèIóπ" %ID% >nul
goto	END



:ENDHELP
ECHO "”ºﬁ≠∞Ÿ“≤∏    Å{€π∞¿∞ Å|ÅÑ ATLMK [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <”ºﬁ≠∞Ÿñº>"
ECHO "ëSëÃ“≤∏      Å{€π∞¿∞ Å|ÅÑ ATLMK [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON>"
ECHO "             Å{€π∞¿∞ Å|ÅÑ ATLMK [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <LOCATE>"
ECHO "”ºﬁ≠∞Ÿ“≤∏ÇÃÇ›        Å|ÅÑ ATLMK [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <”ºﬁ≠∞Ÿñº> <STOP>"
ECHO "”ºﬁ≠∞Ÿ“≤∏+*.COD      Å|ÅÑ ATLMK [”√ﬁŸñº] [çëñº] <“Øæ∞ºﬁON> <”ºﬁ≠∞Ÿñº> <STOP>"
ECHO "_________________________________________________________________________"
ECHO ÉÇÉfÉãñºÅCçëñº, ÉÇÉWÉÖÅ[Éãñº ÇÕëÂï∂éöÇ≈ì¸óÕÇµÇƒâ∫Ç≥Ç¢
ECHO ÉÇÉWÉÖÅ[ÉãÇÕï°êîå¬éwíËèoóàÇ‹Ç∑
ECHO àÍïîï™ÇæÇØÉÅÉCÉNÇµÇΩÇ¢èÍçáÇ…ÇÕ[ÉÇÉWÉÖÅ[Éãñº]ÇÃå„Ç…[ÇrÇsÇnÇo]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
ECHO ÅñÅDÇbÇnÇcÉtÉ@ÉCÉãÇ™ó~ÇµÇ¢èÍçáÇ‡ìØólÇ…[ÉÇÉWÉÖÅ[Éãñº]ÇÃå„Ç…[ÇrÇsÇnÇo]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
ECHO ÉçÉPÅ[É^Å[ÇæÇØé¿çsÇµÇΩÇ¢èÍçáÇ…ÇÕÅA[ÇkÇnÇbÇ`ÇsÇd]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
ECHO ÉÅÉCÉNÇÃèIóπÇÃÉÅÉbÉZÅ[ÉWÇëóÇËÇΩÇ¢ï˚ÇÕ[çëñº]ÇÃå„Ç…[ON]Ç∆ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
if "%MSG%"=="0" goto END2
rem net send "ì¸óÕä‘à·Ç¢Ç≈Ç∑ÅB" %ID% >nul
goto END3

:NOW_MAKING
if "%MSG%"=="0" goto MAKING1
rem net send "åªç›ÅAëºÇÃêlÇ™ÇlÇ`ÇjÇdíÜÇ≈Ç∑ÅB" %ID% >nul
:MAKING1
ECHO åªç›ÅAà»â∫ÇÃêlÇ™ÇlÇ`ÇjÇdíÜÇ≈Ç∑ÅB
type lockfile.txt
goto END2

:TERMINATE
if "%MSG%"=="0" goto MSG_TERMINATE
rem net send "éwíËï™ÇÃÉÅÉCÉNÇÕê≥èÌèIóπÇµÇ‹ÇµÇΩÅB" %ID% >nul
:MSG_TERMINATE
ECHO éwíËï™ÇÃÉÅÉCÉNÇÕê≥èÌèIóπÇµÇ‹ÇµÇΩÅB
goto END2

:END
cd %WORK_DIRECTORY%
REM By Eguchi 1996/02/19 del *.cod
REM del *.cod
del lockfile.txt
:END2
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "		%0 %1 %2 %3 %4 %5 %6 %ID%Ç™è„ãLÇÃéûçèÇ…ÉÅÉCÉNÇèIóπ" >> %BATCHNAME%.log

goto END3

:END3
set MACHINE=
set COUNTRY=
set S_MK=
set MSG=
set ROOT=
set WORK_DIRECTORY=
set BATCHNAME=
set MDM_SP322=
set MDM_R288F=
set OPR_KANJI=
ECHO ON

