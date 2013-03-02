#
# Copyright (c) 2001 by Sun Microsystems, Inc.
# All rights reserved.
#
# ident	"@(#)local.profile	1.10	01/06/23 SMI"
umask=027
#stty istrip
PATH=/usr/bin:/usr/ucb:/etc:.:$HOME/bin:/bin:/sbin:/usr/sbin:/etc:/usr/local/bin
export PATH
LANG=zh.GBK
export LANG
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:usr/lib:/opt/IBM/db2/V8.1/lib:/export/home/db2inst4/sqllib/lib

export LD_LIBRARY_PATH
MANPATH=/usr/local/man:/usr/share/man:$MANPATH;export MANPATH
EDITOR=vi
PS1="\$PWD >";export PS1
# The following three lines have been added by UDB DB2.
#DBTYPE=ORA
DBTYPE=DB2
export DBTYPE
YKT_DBNAME=ykt;export YKT_DBNAME
YKT_USER=db2inst1;export YKT_USER
YKT_PWD=db2inst1;export YKT_PWD
export YKT_BU=ykt_bu
export DB2_INSTANCE_PATH=/home/db2inst1
export ORA_HOME_PATH=/opt/oracle/product/10.2.0/db_1

if [ -f ~/ykt/yktprofile ]; then
    . ~/ykt/yktprofile
fi

alias ls="ls --color=tty"
alias ls="ls -F --color=tty"
alias l="ls -la"
alias lf="ls -CF"
alias c=clear
alias rm="rm -i"
