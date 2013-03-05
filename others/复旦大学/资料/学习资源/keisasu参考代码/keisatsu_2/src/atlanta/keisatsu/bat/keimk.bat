ECHO OFF
REM ----------------------------------------------------------------
REM	ATLMK.BAT For Poplar/Anzu_L
REM
REM		�l�������p�o�b�`�E�t�@�C��
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

rem		���s�h���C�u�`�F�b�N
if exist \src\atlanta\define\product.h		goto DRV_OK
	echo [1;33m�J�����g�̃h���C�u(�{�����[��)���Ⴂ�܂�[0m
	echo [1;33mArisa\usr1�Ŏ��s���ĉ�����[0m
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
set ROOT=\src\atlanta
set MACHINE=%1
set COUNTRY=%2
set WORK_DIRECTORY=\src\atlanta\%MACHINE%\work\%COUNTRY%

REM WORK_DIRECTORY
cd	%WORK_DIRECTORY%
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "%0 %1 %2 %3 %4 %5 %6 %ID%����L�̎����Ƀ��C�N���J�n" >> %BATCHNAME%.log

REM	by O.kimoto 1997/06/12
set MDM_R288F=2

REM	by O.kimoto 1997/08/12
set OPR_KANJI=0

REM ������̐؂蕪��
set MDM_SP322=2

REM	�g�h�m�n�j�h�ŗL�f�[�^���C�N	/*  By O.Kimoto 1998/09/21 */
set HINOKI_DATA=1

REM	�i���o�[�f�B�X�v���C�̃��C�N by H.Hirao 1999/01/12
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
ECHO ���Ȃ��̎w�肵�����W���[���́A���C�N�o�b�`�t�@�C���ɓo�^����Ă��܂���B
ECHO atlmk�̑S�̃��[�N�ɒǉ����Ă��������B���̌ケ�̏������������Ă��������B
goto	END


:COMMON_MODULE
rem --------------------------------
rem	 �b�o�t���ʃ��W���[���ʂ̃����N
rem --------------------------------
ECHO [" %3 " ���W���[���̃����N]
if "%3" == "MDM" goto MDM_MAKE
if "%3" == "mdm" goto MDM_MAKE
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:UNIQUE_MODULE
rem --------------------------------
rem	 �b�o�t�ˑ����W���[���ʂ̃����N
rem --------------------------------
ECHO [" %MACHINE%  %3 " ���W���[���̃����N]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:NEW_MASK_MODULE
rem --------------------------------
rem	 �b�o�t�ˑ����W���[���ʂ̃����N
rem --------------------------------
ECHO [" %MACHINE%  %3 " ���W���[���̃����N]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:COUNTRY_MODULE
rem ----------------------------------
rem	 �e���d�l�ˑ����W���[���ʂ̃����N
rem ----------------------------------
ECHO [" %MACHINE%  %COUNTRY% %3 " ���W���[���̃����N]
 nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%3.mk
if errorlevel 1 goto ERROR
goto	CHECK_OTHER_LINK

:CHECK_OTHER_LINK
set S_MK=1
rem echo --------------------------------
rem echo  ���̃��W���[���������N���܂���
rem echo --------------------------------
SHIFT
goto	MODULE_CHECK

:ALL_MODULE
if "%S_MK%"=="1" GOTO ALL_LINK

rem -----------------------------
rem	 ATLANTA ���ʃ��W���[��
rem -----------------------------
ECHO [ATLANTA �_�C���� ���W���[���i�`�s�c�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\ATD.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �������� ���W���[���i�b�c�b�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\CDC.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ���ʊ֐� ���W���[���i�b�l�m�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\CMN.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ���ʃf�[�^ ���W���[���i�c�`�s�`�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\DATA.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �ʐM�菇 ���W���[���i�e�b�l�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FCM.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �ʐM�R���p�`�`�F�b�N ���W���[���i�e�b�l�Q�b�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FCM_COMP.mk
if errorlevel 1 goto ERROR

rem �g�h�m�n�j�h�͂h�c�o�͎g�p���܂���BBy O.Kimoto 1998/09/07
rem ECHO [ATLANTA �摜���� ���W���[���i�h�c�o�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\IDP.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ���X�g ���W���[���i�k�r�s�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\lst.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ���X�g���[�f�B���O ���W���[���i�k�r�s�Q�v�q�c�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\lstword.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ���ʃ��C�� ���W���[���i�l�`�m�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MAN.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ���f�� ���W���[���i�l�c�l�j�̃����N]	�@��ˑ��̕��Ɏ����Ă��� 1997/02/15	 By T.Yamaguchi
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA �������Ǘ� ���W���[���i�l�d�l�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MEM.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ����Ď����W���[���i�m�b�t�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\NCU.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �I�y���[�V���� ���W���[���i�n�o�q�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPR.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA �\�����[�f�b���O ���W���[���i�n�o�q�Q�v�q�c�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPRWORD.mk
if errorlevel 1 goto ERROR

#ECHO [ATLANTA �W���[�i������ ���W���[���i�o�`�s�j�̃����N]
#nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\pat.mk
#if errorlevel 1 goto ERROR

ECHO [ATLANTA �v�����^ ���W���[���i�o�q�m�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRINT.mk
rem if errorlevel 1 goto ERROR

rem HINOKI�̓X�L���i�[�͕ʃ��W���[���ł��B
rem ECHO [ATLANTA �X�L���i ���W���[���i�r�b�m�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\SCN.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA ���ʂq�n�l�e�[�u���i�s�`�a�k�d�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\TABLE.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �c�l�` ���W���[���i�c�l�`�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\DMA.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA �c�o�q�`�l���W���[���i�c�o�q�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\DPR.mk
rem if errorlevel 1 goto ERROR

rem ECHO [ATLANTA ��]��M���W���[���i�q�n�s�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\ROT.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA S1���W���[���i�r�P�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\s1.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �Q������W���[���i�l�t�k�s�h�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MULTI.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA �N���X�P���W���[���i�b�k�P�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\CL1.mk
rem if errorlevel 1 goto ERROR

REM ECHO [ATLANTA �C���^�[�l�b�g�e�`�w���W���[���i�h�e�`�w�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\IFAX.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA �t���b�V�� ���W���[���i�e�k�`�r�g�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FLASH.mk
if errorlevel 1 goto ERROR

rem -----------------------------
rem	 ATLANTA �b�o�t�ˑ����W���[��
rem -----------------------------
ECHO [ATLANTA �b�o�t�ˑ��f�[�^ ���W���[���i�r�g�c�`�s�`�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\SHDATA.mk
if errorlevel 1 goto ERROR

rem �g�h�m�n�j�h�͂m�����l�������ׁ̈A�l�������t�@�C���ύX
rem ECHO [ATLANTA �X�^�[�g ���W���[���i�h�m�h�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\INI.mk
rem if errorlevel 1 goto ERROR

ECHO [ATLANTA �X�^�[�g ���W���[���i�h�m�h�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\INI.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ������ ���W���[���i�h�m�s�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\hino_int.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA ���j�^ ���W���[���i�l�n�m�j�̃����N]
rem �g�h�m�n�j�h�͂m�����l�������ׁ̈A�l�������t�@�C���ύX
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\MON.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA �b�o�t�ˑ��e�[�u���i�r�g�s�`�a�k�d�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\SHTABLE.mk
if errorlevel 1 goto ERROR

ECHO [ATLANTA �r�b�c���W���[���i�r�b�c�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" \src\cpu\sh7043_a\make\SCD.mk
if errorlevel 1 goto ERROR

rem ECHO [ATLANTA �i�a�h�f���W���[���i�i�a�f�j�̃����N]
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\JBG.mk
rem if errorlevel 1 goto ERROR

rem -----------------------------
rem	 ATLANTA �@��ˑ����W���[��
rem -----------------------------

if "%OPR_KANJI%"=="1" goto OPR_KANJI_MAKE

ECHO [ATLANTA �Q�s�I�y���[�V���� ���W���[���i�n�o�q�@�`�m�j�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPR_ANK.mk
if errorlevel 1 goto ERROR
goto OPR_MAKE_END

:OPR_KANJI_MAKE
ECHO [ATLANTA �S�s�I�y���[�V���� ���W���[���i�n�o�q�@�j�`�m�i�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\OPR_KANJ.mk
if errorlevel 1 goto ERROR
goto OPR_MAKE_END

:OPR_MAKE_END
if "%MDM_SP322%"=="1" goto PRN_SP322_MAKE
if "%MDM_SP322%"=="2" goto PRN_IUTHERML_MAKE

ECHO [ATLANTA �o�g�R�v�����^ ���W���[���i�o�q�m�Q�o�g�R�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRN_PH3.mk
if errorlevel 1 goto ERROR
goto PRN_MAKE_END

:PRN_SP322_MAKE
ECHO [ATLANTA �r�o�R�Q�Q�v�����^ ���W���[���i�o�q�m�Q�r�o�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRN_SP.mk
if errorlevel 1 goto ERROR
goto PRN_MAKE_END

:PRN_IUTHERML_MAKE
ECHO [ATLANTA �h�t�Q�s�g�d�q�l�`�k�v�����^ ���W���[���̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\PRN_IUTH.mk
if errorlevel 1 goto ERROR
goto PRN_MAKE_END

:PRN_MAKE_END

:MDM_MAKE

if "%MDM_R288F%"=="1" goto MDM_R288F_MAKE
if "%MDM_R288F%"=="2" goto MDM_FM336_MAKE
if "%MDM_R288F%"=="3" goto MDM_MN195006		/* �������f���������N���� */

:MDM_ORANGE_MAKE
ECHO [ATLANTA ���f�� ���W���[���i�l�c�l_�n�q�m�f�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM_orng.mk
if errorlevel 1 goto ERROR
goto MDM_END

:MDM_R288F_MAKE
ECHO [ATLANTA ���f�� ���W���[���i�l�c�l_�q�Q�W�W�e�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM_R288.mk
if errorlevel 1 goto ERROR
goto FCM_V34

:MDM_FM336_MAKE
ECHO [ATLANTA ���f�� ���W���[���i�l�c�l�Q�e�l�R�R�U�j�̃����N]
NMAKE "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM.mk
if errorlevel 1 goto ERROR
goto FCM_V34

:MDM_MN195006
ECHO [ATLANTA ���f�� ���W���[���i�l�m�P�X�T�O�O�U�j�̃����N]
NMAKE "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\MDM_MN195006.mk
if errorlevel 1 goto ERROR


:FCM_V34
ECHO [ATLANTA ���f�� ���W���[���i�e�b�l�Q�u�R�S�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\FCM_V34.mk
if errorlevel 1 goto ERROR
goto MDM_END

:MDM_END

if "%HINOKI_DATA%"=="0" goto IU_DATA_END

:HINOKI_DATA_START
ECHO [HINOKI �ŗL�f�[�^�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\iu_data.mk
if errorlevel 1 goto ERROR

ECHO [�g�h�m�n�j�h �r�b�m���W���[�������N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\scn_hino.mk
if errorlevel 1 goto ERROR

goto IU_DATA_END

:IU_DATA_END


if "%MDM_R288F%"=="3" goto ND_MN195006		/* �������f���������N���� */
goto ND_FM336

:ND_FM336
ECHO [ATLANTA �m�����������c�������������i�m�c�j�̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\nd_336.mk
if errorlevel 1 goto ERROR

goto ND_END


:ND_MN195006
ECHO [ATLANTA �m�����������c�������������i�m�c�j�̃����N]
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
rem	 ATLANTA �S�� �����N
rem ---------------------
ECHO [ATLANTA �S�̃��W���[���̃����N]
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%MACHINE%.mk
if errorlevel 1 goto ERROR

rem ##################################
goto LOCATE_EXEC
:ALL1_LINK
rem nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%COUNTRY%\%MACHINE%.mk
nmake "MODEL=%MACHINE%" "COUNTRY=%COUNTRY%" "DEBUG=NONE" %ROOT%\make\%MACHINE%.mk
if errorlevel 1 goto ERROR
rem ##################################

ECHO [ATLANTA �̃����N]
:LOCATE_EXEC
rem ##################################By M.Tachibana 1998/06/02
rem if "%COUNTRY%"=="JP1" goto LOCATE1_EXEC
if "%COUNTRY%"=="JP2" goto LOCATE1_EXEC
rem ##################################
rem LOCATE �������ɂQ�J���Ŏ��s����Ȃ��悤�ɂ���΍�
IF EXIST LOCKFILE.TXT goto NOW_MAKING
echo "���݂l�`�j�d�����s���Ă���̂� %ID%����ł��B"> LOCKFILE.TXT
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
rem	 �f���[�v���P�[�g�E�V���{���̃`�F�b�N
rem --------------------------------------
ECHO [Check Duplicate Symbol]
bgrep -n CANNOT %WORK_DIRECTORY%\%MACHINE%.map > %WORK_DIRECTORY%\Diff.txt
bgrep -n UNDEFINED %WORK_DIRECTORY%\%MACHINE%.map >> %WORK_DIRECTORY%\Diff.txt
bgrep -n DUPLICATE %WORK_DIRECTORY%\%MACHINE%.map >> %WORK_DIRECTORY%\Diff.txt
if errorlevel 1 goto END_MSG
goto END_ERR



:END_ERR
echo Duplicate Duplicate Symbol������܂�(-_-�)
echo %WORK_DIRECTORY%\Diff.txt�Ŋm�F���Ă�������
if "%MSG%"=="0" goto END
rem net send "Error to Duplicate & C_COMMON" %ID% >nul
goto END



:END_MSG
echo ���l�������ł��܂����I�I�_(^o^)�^
echo 
rem net send "�l�������͐���I�����܂����B" %ID% >nul
if "%MSG%"=="0" goto END
rem net send "%MACHINE% %COUNTRY% �� Make �͐���I��" %ID% >nul
goto	END



:ERROR
rem	net send "�l�������ُ͈�I�����܂����B" %ID% >nul
echo �l�������ُ͈�I�����܂���(-_-x
if "%MSG%"=="0" goto END
rem net send "%MACHINE% %COUNTRY% �� Make �ُ͈�I��" %ID% >nul
goto	END



:ENDHELP
ECHO "Ӽޭ��Ҳ�    �{۹��� �|�� ATLMK [���ٖ�] [����] <ү����ON> <Ӽޭ�ٖ�>"
ECHO "�S��Ҳ�      �{۹��� �|�� ATLMK [���ٖ�] [����] <ү����ON>"
ECHO "             �{۹��� �|�� ATLMK [���ٖ�] [����] <ү����ON> <LOCATE>"
ECHO "Ӽޭ��Ҳ��̂�        �|�� ATLMK [���ٖ�] [����] <ү����ON> <Ӽޭ�ٖ�> <STOP>"
ECHO "Ӽޭ��Ҳ�+*.COD      �|�� ATLMK [���ٖ�] [����] <ү����ON> <Ӽޭ�ٖ�> <STOP>"
ECHO "_________________________________________________________________________"
ECHO ���f�����C����, ���W���[���� �͑啶���œ��͂��ĉ�����
ECHO ���W���[���͕����w��o���܂�
ECHO �ꕔ���������C�N�������ꍇ�ɂ�[���W���[����]�̌��[�r�s�n�o]�Ɠ��͂��Ă��������B
ECHO ���D�b�n�c�t�@�C�����~�����ꍇ�����l��[���W���[����]�̌��[�r�s�n�o]�Ɠ��͂��Ă��������B
ECHO ���P�[�^�[�������s�������ꍇ�ɂ́A[�k�n�b�`�s�d]�Ɠ��͂��Ă��������B
ECHO ���C�N�̏I���̃��b�Z�[�W�𑗂肽������[����]�̌��[ON]�Ɠ��͂��Ă��������B
if "%MSG%"=="0" goto END2
rem net send "���͊ԈႢ�ł��B" %ID% >nul
goto END3

:NOW_MAKING
if "%MSG%"=="0" goto MAKING1
rem net send "���݁A���̐l���l�`�j�d���ł��B" %ID% >nul
:MAKING1
ECHO ���݁A�ȉ��̐l���l�`�j�d���ł��B
type lockfile.txt
goto END2

:TERMINATE
if "%MSG%"=="0" goto MSG_TERMINATE
rem net send "�w�蕪�̃��C�N�͐���I�����܂����B" %ID% >nul
:MSG_TERMINATE
ECHO �w�蕪�̃��C�N�͐���I�����܂����B
goto END2

:END
cd %WORK_DIRECTORY%
REM By Eguchi 1996/02/19 del *.cod
REM del *.cod
del lockfile.txt
:END2
REM systime >> %WORK_DIRECTORY%\%BATCHNAME%.log
echo "		%0 %1 %2 %3 %4 %5 %6 %ID%����L�̎����Ƀ��C�N���I��" >> %BATCHNAME%.log

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

