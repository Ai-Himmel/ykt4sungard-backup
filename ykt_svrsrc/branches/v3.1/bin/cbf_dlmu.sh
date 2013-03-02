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
	   amount=$6/100.0;
	   bankcnt ++;
	   bankamt += amount;
	   banksno = sprintf("%c%s%c",39,$5,39);
	   transdate =substr($5,1,8);
           bankdate=transdate;
	   bankcardno=sprintf("%c%s%c",39,$4,39);
	   printf("INS:(bankid,bankdate,recordno,amount,transdate,banksno,bankcardno) ");
	   print "values (",bankid,",",bankdate,",",bankcnt,",",amount,",",transdate,",",banksno,",",bankcardno,")";
	} 
    }
   	END {printf("UPD:set bankcnt=%d,bankamt=%.2lf where bankid=%d and bankdate=%d",bankcnt,bankamt,bankid,bankdate);} 
	' >$outfile
