#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3
outfile=$4
set -x
#dos2unix $2
sed -e 's/\s//g' $dzfile |awk -F\| -v bankid=$bankid -v bankdate=$bankdate '
  BEGIN {rowno=0;totalcnt=0;totalamt=0;}
  {
	if(NF==4)
	{
	   totalcnt=$1;
	   totalamt=$2;
	}
	else if(NF==8)
	{
	  rowno++;
	  bsno=$1;
	  banksno=sprintf("%c%s%c",39,$1,39);
	  bankcardno=sprintf("%c%s%c",39,$2,39);
	  localsno=sprintf("%c%s%s%c",39,$6,$3,39);
	  transdate=$6;
	  stuempno=sprintf("%c%s%c",39,$4,39);
	  transamt=$5;
	  printf("INS:(bankid,bankdate,recordno,transdate,amount,banksno,localsno,stuempno,bankcardno) ");
	  print "values (1,",bankdate,",",rowno,",",transdate,",",transamt,",",banksno,",",localsno,",",stuempno,",",bankcardno,")";
	}
  }
  END { printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",totalcnt,totalamt,bankid,bankdate);}
 ' >$outfile
if [ $? == 0 ];then
	echo "success"
else
	echo "failed"
fi 
