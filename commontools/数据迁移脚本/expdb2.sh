#!/bin/sh

DBNAME=

if [ $# -lt 1 ]; then
	echo "please enter scheme name!"
	exit 1
fi

printf "enter database name :"
read DBNAME

if [ -z $DBNAME ]; then
	echo "Please enter database name !!!"
	exit 1
fi



do_export_scheme()
#
{
	SCHEME=`echo $1|tr [a-z] [A-Z]`
	#SCHEME=$1
	echo "export scheme $SCHEME ..."
	db2 "SELECT NAME FROM SYSIBM.SYSTABLES WHERE CREATOR='$SCHEME' AND (TYPE='T' OR TYPE='N') ORDER BY NAME" \
	| grep -e "\ [^[:alnum:]_ ]*"|grep -v -e "^$" |grep -v "^NAME"|grep -v -e "selected\.$" > tab.lst
	TABS=`cat tab.lst`
	#echo $TABS
	if [ -d $SCHEME ]; then
		rm -rf $SCHEME
	fi
	mkdir $SCHEME
	touch $SCHEME/outdb.lst
	for line in $TABS
	do
		echo "export table $line"
		#db2 "SELECT NAME FROM SYSIBM.SYSCOLUMNS WHERE TBCREATOR='$SCHEME' AND TBNAME='$line' "| \
		#grep -e "\ [^[:alnum:]_ ]*" |grep -v -e "^$" |grep -v "^NAME"|grep -v -e "selected\.$" |\
		#sed 's/[ ]*$/,/g'|sed '/^$/d'|sed '$s/,//g'>fld.lst
		#cat fld.lst
		db2 "EXPORT TO $SCHEME/$line.txt OF DEL SELECT * FROM $SCHEME.$line " > out.lst 2>&1
		grep "Number of rows" out.lst
		printf "$line: " >> $SCHEME/outdb.lst
		REC=`cat out.lst | awk -F: '{printf "%s\n",$2;}'`
		echo $REC >> $SCHEME/outdb.lst
		cd $SCHEME
		#FLDS=`cat fld.lst`
		#printf "LOAD DATA \nINFILE '$line.txt'\n TRUNCATE \nINTO TABLE $SCHEME.$line \n\
		#FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' \n($FLDS)" > $line.ctl
		../gen_ora_ctl.py -d $DBNAME -t $SCHEME.$line -o $line.ctl
		cd ..
	done 
	#< tab.lst
	echo "begin tar table files ..."
	rm -f $SCHEME.tar $SCHEME.tar.gz
	tar cvf $SCHEME.tar $SCHEME > /dev/null 2>&1
	gzip $SCHEME.tar
	#rm -fr tab.lst $SCHEME
	printf "export scheme $SCHEME successfully !!!\n\n"
}

db2 connect to $DBNAME > /dev/null 2>&1
if [ $? -ne 0 ]; then
	echo "connect to database [$DBNAME] error !"
	exit 1
fi

while  [ $# -gt 0 ]
do
	SCHEME=$1
	do_export_scheme $SCHEME
	shift 
done

db2 connect reset > /dev/null 2>&1
exit 0

