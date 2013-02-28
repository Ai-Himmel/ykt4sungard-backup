#!/bin/bash
# vim: tabstop=4
TAR=/bin/tar

BUSDIR="buspos/incoming"

BASE="/home/dgyd/${BUSDIR}"

BUSDATE=$1
tarfile="${BUSDATE}.tar.gz"


fullpath="${BASE}/${BUSDATE}"

if [ -d $fullpath ]; then
	cd $BASE 
	$TAR cfz $tarfile $BUSDATE/ > /dev/null 2>&1
	if [ -f $tarfile ]; then
		echo "${BUSDIR}/$tarfile"
		exit 0
	else
		echo "faild"
		exit 1
	fi
else
	echo "failed"
	exit 1
fi

