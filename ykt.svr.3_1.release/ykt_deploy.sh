#!/bin/bash
date=`date +'%Y%m%d%H%M%S'`
command_name=

err_exit()
{
    echo "Error: $1"
    exit 1
}

usage() {
    echo "usage: `basename $0` "
    printf "\t-a,--all\tmake binary packages\n"
    printf "\t-u,--upgrade\tmake source tar\n"
    printf "\tparams: deploy_type project_dir version \n"
    exit 1
}

make_all() {
  echo "deploy full version"
  find . -type f -print |grep -v "/src"|grep -v ".svn"|grep -v ".log"|grep -v ".klg"|grep -v ".sem"|grep -v ".dbf"|grep -v ".lock"|grep -v ".shm"|grep -v ".sh_history"|grep -v "/yktv3release"|grep -v ".rand"|grep -v "/test"|grep -v "/bin/syssts"|grep -v "ykt_deploy.sh"|grep -v "yktsetup.sh"|grep -v "setup.sh"|grep -v "compile.sh"|grep -v "/install"|grep -v "RMFile.lst"|grep -v "AutoInstall.sh"|grep -v "sql_upgrade" |xargs tar cvfz /tmp/ykt_$1_$2_$date.tar.gz
  echo "full version package ok. pacakge file is /tmp/ykt_$1_$2_$date.tar.gz"
  cp ./AutoInstall.sh /tmp
  exit 0
}

make_upgrade() {
  if [ -e "upgrade_his.log" ] ; then
    echo "deploy upgrade version"
    find . -type f -newer upgrade_his.log |grep -v "/src"|grep -v ".svn"|grep -v ".log"|grep -v ".klg"|grep -v ".sem"|grep -v ".dbf"|grep -v ".lock"|grep -v ".shm"|grep -v ".sh_history"|grep -v "/yktv3release"|grep -v ".rand"|grep -v "/test"|grep -v "/bin/syssts"|grep -v "ykt_deploy.sh"|grep -v "yktsetup.sh"|grep -v "setup.sh"|grep -v "compile.sh"|grep -v "/install"|grep -v "RMFile.lst"|grep -v "AutoInstall.sh"|grep -v "sql_initial"|grep -v "ksmbcc.ini" |grep -v "drtp.ini" |xargs tar cvfz /tmp/ykt_$1_$2_$date.tar.gz
    echo "$date - new package." > upgrade_his.log
    echo "upgrade package ok. pacakge file is /tmp/ykt_$1_$2_$date.tar.gz"
    exit 0
  else
    err_exit "upgrade_his.log is not exist."
  fi
}

if [ $# -ne 3 ] ; then
    usage
fi

case $1 in
    -a|--all)
    echo "package a full version..."
    command_name="all"
    ;;
    -u|--upgrade)
    echo "package a upgrade version..."
    command_name="upgrade"
    ;;
    *)usage
    ;;
esac


SRCDIR=$2
YKTVER=$3
cd $SRCDIR

if [ $command_name = "all" ]; then
    make_all $YKTVER $command_name
elif [ $command_name = "upgrade" ]; then
    make_upgrade $YKTVER $command_name
else
    usage
fi

exit 0