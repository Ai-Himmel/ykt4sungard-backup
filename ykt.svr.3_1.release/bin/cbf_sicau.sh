#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3
outfile=$4 
#dos2unix $2
sed -e 's/|/\t/g' $dzfile|awk -v bankid=$bankid -v bankdate=$bankdate '
  BEGIN {rowno=0;totalamt=0;}
  {
        rowno++;
		banksno=sprintf("%c%s%c",39,substr($0,1,9),39);
        transdate=substr($0,71,8);
        localsno=sprintf("%c%s%s%c",39,bankdate,substr($0,65,6),39);
		stuempno=substr($0,39,18);
		sub("^[ ]*", "", stuempno);
		sub("[ ]*$", "", stuempno);
        stuempno=sprintf("%c%s%c",39,stuempno,39);
        bankcardno=substr($0,20,19);
		sub("^[ ]*", "", bankcardno);
		sub("[ ]*$", "", bankcardno);
        bankcardno=sprintf("%c%s%c",39,bankcardno,39);
        transamt=substr($0,85,18);;
		sub("^[ ]*", "", transamt);
		sub("[ ]*$", "", transamt);
		transamt=transamt/100.0;
        totalamt+=transamt;
        printf("INS:(bankid,bankdate,recordno,transdate,amount,banksno,localsno,stuempno,bankcardno) ");
        print "values (1,",bankdate,",",rowno,",",transdate,",",transamt,",",banksno,",",localsno,",",stuempno,",",bankcardno,")";
  } 
  END { printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",rowno,totalamt,bankid,bankdate);}
 ' >$outfile
if [ $? == 0 ];then
        echo "success"
else
        echo "failed"
fi