lst=`ls BT*c`
lst=$lst
for i in $lst
do
   echo  "mv $i w$i"
   mv $i w$i
done
