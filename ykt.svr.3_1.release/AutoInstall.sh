#!/bin/bash
if [ ! $LOGNAME = "root" ] then
  echo "must run me by root."
  exit 1
fi
if [ $# -ne 1 ] ; then
  echo "please provide ykt install package file(.tar.gz)."
  exit 1
fi
USERNAME=ykt
GROUPNAME=ykt
groupadd $GROUPNAME
useradd -g $USERNAME -d /home/$USERNAME $USERNAME
gpasswd -a $USERNAME dba
gpasswd -a $USERNAME oinstall
su - $USERNAME -c "mkdir -p /home/$USERNAME/ykt"
tar xvfz $1 -C /home/$USERNAME/ykt
chown -R $USERNAME:$GROUPNAME /home/$USERNAME/ykt
su - $USERNAME -c "chmod u+x $HOME/ykt/Install_v3.sh"
su - ykt -c "$HOME/ykt/Install_v3.sh"