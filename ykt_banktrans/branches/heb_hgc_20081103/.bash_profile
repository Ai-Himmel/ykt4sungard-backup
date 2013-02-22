# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

PATH=$PATH:$HOME/bin
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/bank/lib
YKT_USER=ykt_cur;export YKT_USER
YKT_PWD=kingstar;export YKT_PWD
export USEROPTS=" -g"
export YKT_BU=ykt_bu
ulimit  -c unlimited


if [ -f ~/bank/yktprofile ]; then
    . ~/bank/yktprofile
fi


alias ls="ls --color=tty"
alias ls="ls -F --color=tty"
alias l="ls -la"
alias lf="ls -CF"
alias c=clear
alias rm="rm -i"
export LD_LIBRARY_PATH
export PATH

