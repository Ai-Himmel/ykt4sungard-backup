#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3   
outfile=$4    
#dos2unix $2
sed -e 's/|/ \t/g' $dzfile|awk -v bankid=$bankid -v bankdate=$bankdate '
  BEGIN {rowno=0;totalamt=0;}
  {
  			bankcardno=sprintf("%c%s%c",39,$3,39);
        banksno=sprintf("%c%s%c",39,$5,39);
        localsno=sprintf("%c%s%s%c",39,bankdate,$4,39);
        stuempno=sprintf("%c%s%c",39,$2,39);
        transamt=$6/100.0;
		transdate=$7;
        if($8>0) next;
        totalamt+=transamt;
        rowno++;
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
