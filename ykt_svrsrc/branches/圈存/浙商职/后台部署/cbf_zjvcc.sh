#!/bin/bash
bankid=$1
bankdate=$2
dzfile=$3
outfile=$4
sed -e 's/ //g' $dzfile|sed -e 's/\t//g'|awk -F[\|] -v bankid=$bankid -v bankdate=$bankdate '
    BEGIN {rowno=0;bankcnt=0;bankamt=0;}
    {	
	if($0~/00/)
	{
		bankcnt ++;
		stuempno= sprintf("%c%s%c",39,$1,39);
		custname=sprintf("%c%s%c",39,$3,39);
		acctno=sprintf("%c%s%c",39,$4,39);
		amount=$5;
		bankamt += amount;
		site= sprintf("%c%s%c",39,$6,39);
		teller= sprintf("%c%s%c",39,$7,39);
		bankorder=sprintf("%c%s%c",39,$8,39);
		localsno =sprintf("%c%s%s%c",39,bankdate,$9,39);
		transdate =bankdate;
		printf("INS:(bankid,bankdate,recordno,amount,transdate,banksno,localsno,bankcardno,stuempno) ");
		print "values (",bankid,",",bankdate,",",bankcnt,",",amount,",",transdate,",",bankorder,",",localsno,",",acctno,",",stuempno,")";
	} 
    }
   	END {printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",bankcnt,bankamt,bankid,bankdate);} 
	' >$outfile

if [ $? == 0 ];then
	echo "success"
else
	echo "failed"
fi 

