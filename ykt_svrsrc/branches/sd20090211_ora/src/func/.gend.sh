lst=`ls *.sqC`
for i in $lst
do
   SQC=`echo $i|cut -d. -f 1`
   rm -f $SQC.c $SQC.bnd $SQC.o
done
