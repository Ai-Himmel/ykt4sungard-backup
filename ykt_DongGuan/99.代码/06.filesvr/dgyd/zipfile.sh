#!/bin/bash
# vim: tabstop=4
TAR=/bin/tar
MV=/bin/mv
MKDIR=/bin/mkdir


renamefile=$2
unitno=$1

BUSDIR="bus${unitno}/incoming"
BASE="/home/${BUSDIR}"

fullpath="${BASE}"
backuppath="${fullpath}/backup"


do_checkbackup()
{
        p=$1
        if [ -d $p ]; then
                return
        else
                $MKDIR -p $p
        fi
}

if [ $renamefile = "rename" ]; then
        f=$3
        pkgfile="${fullpath}/${f}"
        if [ -z $f ]; then
                echo "failed"
                exit 1
        fi
        if [ -f $pkgfile ]; then
                do_checkbackup $backuppath
                md5filename=`echo $pkgfile|cut -d'.' -f 1`
                md5filename="${md5filename}.md5"
                $MV $pkgfile $backuppath
                $MV $md5filename $backuppath
                echo "Success"
        else
                echo "failed"
                exit 1
        fi
else
if [ -d $fullpath ]; then
        cd $BASE
        allfile=`ls $fullpath/*.md5` > /dev/null 2>&1
    for md5file in $allfile
    do
                fullname=`echo $md5file|cut -d'.' -f 1`
                zipfile="${fullname}.zip"
                if [ -f $zipfile ]; then
                        f=`basename $zipfile`
                        echo "${BUSDIR}/${f}"
                        exit 0
                fi
    done
        echo "failed"
        exit 1
else
        echo "failed"
        exit 1
fi

fi
