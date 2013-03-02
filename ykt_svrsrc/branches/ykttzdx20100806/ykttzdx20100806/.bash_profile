# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

umask=027
#stty istrip
PATH=/usr/bin:/usr/ucb:/etc:.:$HOME/ykt/bin:$HOME/ykt/sbin:/bin:/sbin:/usr/sbin:/etc:/usr/local/bin
export PATH
LANG=zh_CN.GBK
export LANG
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:usr/lib:/opt/IBM/db2/V8.1/lib:/home/yktinst1/sqllib/lib

export LD_LIBRARY_PATH
MANPATH=/usr/local/man:/usr/share/man:$MANPATH;export MANPATH
EDITOR=vi
PS1="\$PWD >";export PS1
# The following three lines have been added by UDB DB2.
if [ -f /diskgrp/cur/yktinst1/sqllib/db2profile ]; then
    . /diskgrp/cur/yktinst1/sqllib/db2profile
fi
EDITOR=vi;export EDITOR

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
alias cdtool="cd $HOME/ykt/src/tool"
alias cddrtp="cd $HOME/drtp/linux9/bin"
alias cdbank="cd $HOME/ykt/src/bank"
alias rm="rm -i"
CVSROOT=/cvs/root;export CVSROOT
YKT_DBNAME=yktbase;export YKT_DBNAME
YKT_USER=yktinst1;export YKT_USER
YKT_PWD=k1ng4tz;export YKT_PWD
PHOTO_DBNAME=photo;export PHOTO_DBNAME
PHOTO_USER=db2inst1;export PHOTO_USER
PHOTO_PWD=db2inst1;export PHOTO_PWD
export BIN_PATH=$HOME/ykt/bin
PS1="\u@\w $"
export PS1

unset USERNAME
