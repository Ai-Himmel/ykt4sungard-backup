lst=`ls *.act`
for i in $lst
do
   SQC=`echo $i|cut -d. -f 1`
   rm -f $SQC.sqC $SQC.eC $SQC.cpp $SQC.bnd $SQC.o *stru.h
done
