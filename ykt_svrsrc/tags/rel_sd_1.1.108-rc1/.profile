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
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi
EDITOR=vi;export EDITOR
alias l="ls -la"
alias c=clear
alias cdi="cd $HOME/ykt/src/include"
alias cdp="cd $HOME/ykt/src/public"
alias cddb="cd $HOME/ykt/src/db"
alias cds="cd $HOME/ykt/src"
alias cdf="cd $HOME/ykt/src/func"
alias cdlog="cd $HOME/ykt/log"
alias cdbin="cd $HOME/ykt/bin"
alias rm="rm -i"

export YKT_DBNAME=yktbase
export YKT_USER=db2inst1
export YKT_PWD=ykt123sd
export YKT_BU=yktsd_bu
export BIN_PATH=$HOME/ykt/bin