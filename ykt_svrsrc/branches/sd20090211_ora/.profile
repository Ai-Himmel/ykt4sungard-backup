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

YKT_DBNAME=yktdb;export YKT_DBNAME
YKT_USER=ykt_cur;export YKT_USER
YKT_PWD=kingwyb@hydx;export YKT_PWD
export YKT_BU=ykt_bu
export ORA_HOME_PATH=/oradata/oracle/product/10.2.0.1

if [ -f ~/ykt/yktprofile ]; then
    . ~/ykt/yktprofile
fi


alias ls="ls --color=tty"
alias ls="ls -F --color=tty"
alias l="ls -la"
alias lf="ls -CF"
alias c=clear
alias rm="rm -i"

