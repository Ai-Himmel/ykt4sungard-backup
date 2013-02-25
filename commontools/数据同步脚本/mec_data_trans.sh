#!/bin/bash
BASE_HOME=$HOME
LOGFILE=$BASE_HOME/log/transfer.log
MEC_FTP_USER=ykt
MEC_FTP_PASSWD=ykt
MEC_FTP_IP=10.64.100.111

YKT_FTP_USER=ykt
YKT_FTP_PWD=ks123ykt
YKT_FTP_IP=172.18.109.101

TEMP_DATA=$BASE_HOME/tmp_data
TEMP_DATA_BACK=$TEMP_DATA/backup
YKT_DATA=ykt/mec_data
FTP_CMD="/usr/kerberos/bin/ftp -i -n -u"
LIST_FILE=$TEMP_DATA/newer.lst

do_check_env()
{
	if [ -d $TEMP_DATA ]; then
		echo -n ""
	else
		mkdir $TEMP_DATA
		if [ $?!=0 ]; then
			exit 1
		fi
	fi
}

do_get_list()
{
	echo -n "fetch file list! "
	echo $LIST_FILE
	$FTP_CMD $MEC_FTP_IP<<EOF
	user $MEC_FTP_USER $MEC_FTP_PASSWD
	nlist * $LIST_FILE
	quit
EOF
	#cat $LIST_FILE
}

do_ftp_download_file()
{
	echo "download file $1"
	$FTP_CMD $MEC_FTP_IP<<EOF
	user $MEC_FTP_USER $MEC_FTP_PASSWD
	bi
	lcd $TEMP_DATA
	mget $1
	quit
EOF
}

do_download_mec_data()
{
	ALL_FILES=''
	echo "start download file..."
	while read line
	do
		if [ -f $TEMP_DATA_BACK/$line ]; then
			echo "skipp file $line"
		else
			#ALL_FILES="$ALL_FILES $line"
			do_ftp_download_file $line
			if [ $? != 0 ]; then
				echo "download file error!"
				do_clear_local_file
				exit 1
			fi
		fi
	done<$LIST_FILE
	echo "download load success!"
}

do_clear_local_file()
{
	/bin/rm -f *.log *.txt *.inf
}

do_update_mec_data()
{
	$FTP_CMD $YKT_FTP_IP<<EOF
	user $YKT_FTP_USER $YKT_FTP_PWD
	bi
	cd $YKT_DATA
	lcd $TEMP_DATA
	mput *.log
	quit
EOF

	if [ $? = 0 ]; then
		echo "update data success!"
		echo "clear up all temp data"
		cd $TEMP_DATA && mv *.log *.inf *.txt $TEMP_DATA_BACK >/dev/null 2>&1
	else
		echo "upload data failed!"
		exit 1
	fi

}

do_check_env
do_get_list
cd $TEMP_DATA && do_download_mec_data
cd $TEMP_DATA && do_update_mec_data

exit 0


