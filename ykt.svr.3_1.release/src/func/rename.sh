#!/usr/bin/ksh
lst=`ls w*c`
lst=$lst
for i in $lst
do
   NEWFILE=`echo $i|cut -c 2-`
   echo  "mv $i $NEWFILE"
   mv $i $NEWFILE 
done
