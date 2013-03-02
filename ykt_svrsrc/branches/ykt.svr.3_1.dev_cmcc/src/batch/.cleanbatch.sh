lst=`ls *.sqC`
for i in $lst
do
	SQC=`echo $i|cut -d. -f1`
	rm -f  $SQC.eC $SQC.cpp $SQC.bnd $SQC.o
done
