#!/bin/sh
set -x
lst=`ls  *.eC`
for i in $lst
do
	echo $i
#vim  $i <<!
#:%s/#include/ESQL #include/g
#
#
#:x
#!
sed -e 's/ESQL #include/#include/g' $i|sed -e 's/#include/ESQL #include/' >tmp
mv tmp $i
done
