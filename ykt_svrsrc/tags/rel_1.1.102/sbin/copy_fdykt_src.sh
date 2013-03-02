#!/usr/bin/ksh
cp  /export/home/fdykt/fdykt/src/include/*.h  /ykt/src/include/
cp  /export/home/fdykt/fdykt/src/public/*c  /ykt/src/public/
cp  /export/home/fdykt/fdykt/src/public/*cpp  /ykt/src/public/
cp  /export/home/fdykt/fdykt/src/public/*.h  /ykt/src/public/
cp  /export/home/fdykt/fdykt/src/wsn/*c  /ykt/src/func/
cp  /export/home/fdykt/fdykt/src/wsn/*cpp  /ykt/src/func/
cd  /ykt/src/func
/ykt/src/func/rename.sh
