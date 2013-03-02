#!/bin/bash
date=`date +'%Y%m%d%H%M%S'`

if [ $# -ne 3 ] ; then
  echo  "please input parameter deploy_type(all or upgrade) and project_dir and version "
  exit 1;
fi

cd $2

if [ "$1" = "all" ] ; then
  echo "deploy full version"
  find . -type f -print |grep -v "/src"|grep -v ".svn"|grep -v ".log"|grep -v ".klg"|grep -v ".sem"|grep -v ".dbf"|grep -v ".lock"|grep -v ".shm"|grep -v ".sh_history"|grep -v ".profile"|grep -v "/yktv3release"|grep -v ".rand"|grep -v "/test" |xargs tar cvfz /tmp/ykt$3_$1_$date.tar.gz
  echo "full version package ok."
elif [ "$1" = "upgrade" ] ; then
  if [ -e "upgrade_his.log" ] ; then
    echo "deploy upgrade version"
    find . -type f -newer upgrade_his.log |grep -v "/src"|grep -v ".svn"|grep -v ".log"|grep -v ".klg"|grep -v ".sem"|grep -v ".dbf"|grep -v ".lock"|grep -v ".shm"|grep -v ".sh_history"|grep -v ".profile"|grep -v "/yktv3release"|grep -v ".rand"|grep -v "/test" |xargs tar cvfz /tmp/ykt$3_$1_$date.tar.gz
    echo "$date - new package." > upgrade_his.log
    echo "upgrade package ok."
  else
    echo "upgrade_his.log is not exist."
  fi
else
  echo "please input a right parameter.(all or upgrade)"
fi
