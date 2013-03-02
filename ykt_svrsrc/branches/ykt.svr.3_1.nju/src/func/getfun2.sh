lst=`ls F*.sqc|cut -d. -f 1`
for i in $lst 
do
echo "int $i(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);"
done 
