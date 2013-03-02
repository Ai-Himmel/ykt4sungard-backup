#!/usr/bin/sh
DATE=`date +%m%d`		
FILENAME=$HOME/bak/yktsrc$DATE.tar
flist=`find $HOME/fdykt -type f  -print|egrep  "\.c$|\.sqc$|\.h$|\.cpp$|\.act$|\.sh$|\.ini$|\.inc$|\.a$|\.so$|\.lst$|.cfg$|\.del$|\.upd$|\.ins$|\.sqC$|make" `
tar cvf  $FILENAME  $flist
#compress /fudanykt/fudanykt/bak/yktsrc$DATE.tar
