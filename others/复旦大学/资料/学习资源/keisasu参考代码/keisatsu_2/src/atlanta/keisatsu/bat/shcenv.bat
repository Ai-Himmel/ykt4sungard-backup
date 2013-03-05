echo on
rem --------------------------------------------------------------------------
rem 	Set environment to use SHC3.1
rem --------------------------------------------------------------------------
rem 
net use F: /DELETE
net use V: /DELETE
net use W: /DELETE
net use X: /DELETE
net use Y: /DELETE

rem HIKARU‚Ìƒ}ƒEƒ“ƒg
net use F: \\hikaru\ryoko_usr1

net use Y: \\hikaru\ryoko_usr1
cd y:\public\cc\shc\bin
net use X: \\hikaru\ryoko_usr1
cd x:\public\ibm\c6\bin
net use W: \\hikaru\ryoko_usr1
cd w:\public\ibm\c6\binb
net use V: \\hikaru\ryoko_usr1
cd v:\public\utils


set SHC_LIB=y:\public\cc\shc\bin
set SHC_INC=y:\public\cc\shc\include
set SHC_TMP=c:\temp
set SHC_VER=SHC3.1
set PATH=f:;v:\public\utils;w:\public\ibm\c6\binb;x:\public\ibm\c6\bin;Y:\public\cc\shc\bin;%DEF_PATH%
if "%DOS16M%" == ""	goto	SET_DOS16M
goto DOS16M_OK

:SET_DOS16M
rem set DOS16M=1,@5M:1024
rem set DOS16M=0,@5M:3M
set DOS16M=0@:4M
:DOS16M_OK

echo The environmental variables for SHC3.1 have been set.
doskey
