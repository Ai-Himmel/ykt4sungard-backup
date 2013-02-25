#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3
outfile=$4
#set -x
#dos2unix $2
sed -e 's/|/ \t/g' $dzfile|awk -v bankid=$bankid -v bankdate=$bankdate '
  BEGIN {rowno=0;totalcnt=0;totalamt=0;}
  {
        if(NR==1)
        {
           totalcnt=$1;
           totalamt=$2;
        }
        else
        {
          rowno++;
          localsno=sprintf("%c%s%c",39,substr($1,1,14),39);
          stuempno=sprintf("%c%s%c",39,substr($1,15),39);
          bankcardno=sprintf("%c%s%c",39,$2,39);
          transamt=$3;
          printf("INS:(bankid,bankdate,recordno,transdate,amount,localsno,stuempno,bankcardno) ");
          print "values (1,",bankdate,",",rowno,",",bankdate,",",transamt,",",localsno,",",stuempno,",",bankcardno,")";
        }
  }
  END { printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",totalcnt,totalamt,bankid,bankdate);}
 ' >$outfile
if [ $? == 0 ];then
        echo "success"
else
        echo "failed"
fi