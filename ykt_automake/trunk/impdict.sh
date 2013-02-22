#!/bin/sh

DBNAME=$1
DEVNAME=
RET=

if [ -z $DBNAME ]
then
	echo "please enter database name "
	exit 1
fi


printf "please enter user name [测试大学]:"
read DEVNAME

if [ -z $DEVNAME ] 
then
	echo "error "
	exit 1
fi

tar xvf dbtabs.tar > /dev/null 2>&1
echo "start import dictionary..."
cd dbtabs && db2move $DBNAME import > /dev/null 2>&1
cd ..
RET=$?
/bin/rm -Rf dbtabs
if [ $RET != 0 ]; then
	echo "import dictionary error!"
	exit 1
fi

echo "import dictionary success!!"

db2 <<!
connect to $DBNAME
delete from ykt_cur.t_pif_device where device_id!=1
update ykt_cur.t_pif_device set device_name='$DEVNAME' where device_id=1
delete from ykt_cur.t_cif_shop where shop_id != 1
update ykt_cur.t_cif_shop set shop_name='$DEVNAME' where shop_id=1
delete from ykt_cur.t_pif_area where area_no!=1
update ykt_cur.t_pif_area set area_name='$DEVNAME' where area_no=1
update ykt_cur.t_pif_syskey set key_value=10
quit
!

if [ $? != 0 ]; then
	echo "update dictionary error"
	exit 1
fi

echo "update dictionary success!"
exit 0

