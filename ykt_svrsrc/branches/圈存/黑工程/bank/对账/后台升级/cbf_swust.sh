#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3   
outfile=$4    
#dos2unix $2
sed -e 's/|/\t/g' $dzfile|awk -v bankid=$bankid -v bankdate=$bankdate '
  BEGIN {rowno=0;totalamt=0;}
  {
        banksno=sprintf("%c%s%c",39,$2,39);
        transdate=substr(bankdate,1,6)
        localsno=sprintf("%c%s%c",39,$1,39);
        stuempno=sprintf("%c%s%c",39,$5,39);;
        transamt=$6/100.0;
        if($7>0) next;
        totalamt+=transamt;
        rowno++;
        printf("INS:(bankid,bankdate,recordno,transdate,amount,banksno,localsno,stuempno) ");
        print "values (1,",bankdate,",",rowno,",",bankdate,",",transamt,",",banksno,",",localsno,",",stuempno,")";
  } 
  END { printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",rowno,totalamt,bankid,bankdate);}
 ' >$outfile
if [ $? == 0 ];then
        echo "success"
else
        echo "failed"
fi
