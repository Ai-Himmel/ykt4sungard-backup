#
# Copyright (c) 2001 by Sun Microsystems, Inc.
# All rights reserved.
#
# ident	"@(#)local.profile	1.10	01/06/23 SMI"
umask=027
#stty istrip
DBTYPE=ORA
#DBTYPE=DB2
export DBTYPE
# include .bashrc if it exists
if [ -f ~/.bashrc ]; then
    . ~/.bashrc
fi

# set PATH so it includes user's private bin if it exists
if [ -d ~/bin ] ; then
    PATH=~/bin:$PATH
fi

if [ $DBTYPE = "DB2" ]; then
    if [ -f /home/db2inst1/sqllib/db2profile ]; then
        . /home/db2inst1/sqllib/db2profile
    fi
    YKT_DBNAME=ykttest;export YKT_DBNAME
    YKT_USER=db2inst1;export YKT_USER
    YKT_PWD=db2inst1;export YKT_PWD
else
    ORACLE_SID=YKTDB
    export ORACLE_SID
    ORACLE_BASE=/opt/oracle
    export ORACLE_BASE
    ORACLE_HOME=$ORACLE_BASE/product/10.2.0/db_1
    export ORACLE_HOME
    export PATH=$PATH:$ORACLE_HOME/bin
    YKT_DBNAME=YKTDB;export YKT_DBNAME
    YKT_USER=ykt_cur;export YKT_USER
    YKT_PWD=kingstar;export YKT_PWD
    LD_LIBRARY_PATH=/usr/lib:/usr/local/lib:$ORACLE_HOME/lib:$ORACLE_HOME/rdbms/lib
    export LD_LIBRARY_PATH
    #export LANGUAGE=en_US.iso88591
    export NLS_LANG=american_america.ZHS16GBK
fi
export YKT_BU=ykt_bu
export LANG=zh_CN.gbk
#export LANG=zh_CN.GBK
#export LANGUAGE=zh_CN.GBK
#export LC_CTYPE=zh_CN.GBK
#export LC_MESSAGES=zh_CN.GBK
#export LANG=zh_CN.UTF-8
#export LANGUAGE=zh_CN.UTF-8
#export LC_ALL="C"
#export LC_CTYPE="zh_CN.GBK"

alias ls="ls --color=tty"
alias ls="ls -F --color=tty"
alias l="ls -la"
alias lf="ls -CF"
alias c=clear
alias cdw="cd $HOME/ykt/src/watch"
alias cdi="cd $HOME/ykt/src/include"
alias cdp="cd $HOME/ykt/src/public"
alias cddb="cd $HOME/ykt/src/db"
alias cds="cd $HOME/ykt/src"
alias cdf="cd $HOME/ykt/src/func"
alias cdlog="cd $HOME/ykt/log"
alias cdbin="cd $HOME/ykt/bin"
alias cdsbin="cd $HOME/ykt/sbin"
alias cdbak="cd $HOME/db_bak"
alias cdt="cd $HOME/ykt/src/test"
alias cdtest="cd $HOME/test"
alias rm="rm -i"
#PHOTO_DBNAME=photo;export PHOTO_DBNAME
#PHOTO_USER=db2inst4;export PHOTO_USER
#PHOTO_PWD=db2inst4;export PHOTO_PWD

export PATH=$PATH:$HOME/ykt/sbin:$HOME/ykt/bin:$HOME/ykt/src/func:$HOME/ykt/src/db:$HOME/ykt/src/public
export BIN_PATH=$HOME/ykt/bin
