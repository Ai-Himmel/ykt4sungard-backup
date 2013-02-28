lst=`ls F*.sqc|cut -d. -f 1`
for i in $lst 
do
k=`echo $i|tr -d "F"`
echo "{$k ,$i, \"xxx\", \"wj\", 1, false, 0,0,0,0,0},"
done 
