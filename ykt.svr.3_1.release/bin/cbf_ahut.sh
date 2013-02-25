#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3
outfile=$4
#dos2unix $2
sed -e 's///g' $dzfile|awk  -v bankid=$bankid -v bankdate=$bankdate '
  BEGIN {rowno=0;totalcnt=0;totalamt=0;}
  {
	if(NF==2)
	{
	   totalcnt=substr($1,9,6);
	   sub(/^[0]+/,"",totalcnt);
	   totalamt=$2;
	}
	else if(NF==4)
	{
	  rowno++;
	  bsno=substr($1,9,20);
	  sub(/^[0]+/,"",bsno);
	  banksno=sprintf("%c%s%c",39,bsno,39);
	  localsno=sprintf("%c%s%c",39,substr($2,1,14),39);
	  transdate=substr($2,1,8);
	  stuempno=sprintf("%c%s%c",39,$3,39);
	  transamt=$4;
	  printf("INS:(bankid,bankdate,recordno,transdate,amount,banksno,localsno,stuempno) ");
	  print "values (1,",bankdate,",",rowno,",",transdate,",",transamt,",",banksno,",",localsno,",",stuempno,")";
	}
	else
	{
	    exit 1;
	}
  }
  END { printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",totalcnt,totalamt,bankid,bankdate);}
 ' >$outfile
if [ $? == 0 ];then
	echo "success"
else
	echo "failed"
fi 
