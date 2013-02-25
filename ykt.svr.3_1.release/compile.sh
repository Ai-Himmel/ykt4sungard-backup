#!/bin/bash
CLEAN=""
if [ $# -eq 1 ] ; then
  echo  "need clean. "
  CLEAN=$1
fi
echo "begin ---- re-making $HOME/ykt/src/db"
cd $HOME/ykt/src/db
chmod u+x $HOME/ykt/src/db/.cleandb.sh
if [ "$CLEAN" = "clean" ] ; then
  make clean
fi
make
make install
echo "end   ---- re-making $HOME/ykt/src/db"
sleep 3
echo "begin ---- re-making $HOME/ykt/src/public"
cd $HOME/ykt/src/public
chmod u+x $HOME/ykt/src/public/.cleanpublic.sh
if [ "$CLEAN" = "clean" ] ; then
  make clean
fi
make
echo "end ---- re-making $HOME/ykt/src/public"
sleep 3
echo "begin ---- re-making $HOME/ykt/src/func"
cd $HOME/ykt/src/func
chmod u+x $HOME/ykt/src/func/.cleanfunc.sh
if [ "$CLEAN" = "clean" ] ; then
  make clean
fi
make
echo "end ---- re-making $HOME/ykt/src/func"
sleep 3
echo "begin ---- re-making $HOME/ykt/src/batch"
cd $HOME/ykt/src/batch
chmod u+x $HOME/ykt/src/batch/.cleanbatch.sh
if [ "$CLEAN" = "clean" ] ; then
  make clean
fi
make
echo "end ---- re-making $HOME/ykt/src/batch"
