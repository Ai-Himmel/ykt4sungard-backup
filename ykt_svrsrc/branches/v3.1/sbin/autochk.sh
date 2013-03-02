#!/usr/bin/ksh 
export HOME=/ecard
# The following three lines have been added by UDB DB2.
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
        . $HOME/.profile
fi

year=`date +%Y`
mon=`date +%m`
day=`date +%d`
day=`expr $day - 1`
if [ $day -eq 0 ]
     then
         mon=`expr $mon - 1`
         if [ $mon -eq 0 ]
         then
             mon=12
             year=`expr $year - 1`
         fi
         lastline=`cal $mon $year | grep "[0-9]" | tail -1`
         day=`echo $lastline | sed "s/.* \([0-9][0-9]*\)/\1/"`
     fi
    
     if [ ${#mon} -eq 1 ]
     then
   mon="0$mon"
     fi
    
     if [ ${#day} -eq 1 ]
     then
      day="0$day"
fi
dat="$year$mon$day"
BANKCHKFILE="icnju${dat}.circle"
echo $BANKCHKFILE
cd /tmp
ftp -in 172.22.1.12 <<!
user njgh njgh
bi
mget $BANKCHKFILE
bye
!
if [ -f $BANKCHKFILE ];then
  /ecard/ykt/bin/nj_bank_acccheck $dat $BANKCHKFILE >>$HOME/ykt/log/autochk$dat.log
  if [ $? == 0 ];then
	  echo "check $BANKCHKFILE succ!"
  else
	  echo "check $BANKCHKFILE failed!"
  fi
fi
