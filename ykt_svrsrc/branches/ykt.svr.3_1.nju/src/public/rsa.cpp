#include "rsa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbfunc.h"
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "errdef.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "pubfunc.h"

int IsPrime(long n)
{
	long i;
	for(i=2;i<n;i++)
		if(n%i==0)
			break;
	if(i<n)
		return 0;
	else
		return 1;
}

long NextPrime(long n)
{
while(IsPrime(n)==0)
n++;
return n;
}

long gcd(long m,long n)
{
long r;
while((r=m%n)!=0)
{
m=n;
n=r;
}
return n;
}

long husu(long n)
{
long i=n-1;
while(gcd(n,i)!=1)
i--;
return i;
}

long modone(long m,long n)
{
long i=0;
while((i*m)%n!=1)
i++;
return i;
}

void rsacreate(long p,long q,long *n,long *e,long *d)
{
*n=p*q;
*e=husu((p-1)*(q-1));
*d=modone(*e,(p-1)*(q-1));
}

long rsa(long m,long d,long n)
{
long s=1;
long i;
for(i=1;i<=d;i++)
{
s*=m;
s=s%n;
}
return s%n;
}

int encryrsa(char *oridata,char *outdata){
	long n,d;
	int ret =0;
	 int idn=2100;
	 int idd=2101;
	 char bufn[20]="";
	 char bufd[20]="";
	 char temporidata[33]="";
	 char tempoutdata[201]="";
	ret = GetSysParaVal(idn, bufn);
	if(ret){
		return E_DB_TRADESERIALERROR_R;
	}
	ret = GetSysParaVal(idd, bufd);
	if(ret){
		return E_DB_TRADESERIALERROR_R;
	}
	strcpy(temporidata,oridata);
	n=atol(bufn);
	d=atol(bufd);
	int i=0;
	//writelog(LOG_ERR,"N=[%ld],d=[%ld],temporidata=[%s],size of temporidata=[%d]\n",n,d,temporidata,sizeof(temporidata));
	char templ[sizeof(long)*8+1]="";
	char c[2] = "";
	long t = 0;
	long cyl = 0;
	for(i=0;i<32;i++){
		c[0] = temporidata[i];
		//writelog(LOG_ERR,"c=[%s]\n",c);
		t = atol(c);
		//long t = (long)oridata[i] - '0' ;
		//writelog(LOG_ERR,"t=[%ld]\n",t);
		t = t+10;
		//writelog(LOG_ERR,"t=[%ld]\n",t);
		cyl =rsa(t,d,n);
		//ltoa(cyl,templ,10);
		sprintf(templ,"%ld",cyl);
		if(i!=31){
			strcat(tempoutdata,templ);
			strcat(tempoutdata,",");
		}else{
			strcat(tempoutdata,templ);
		}
		//writelog(LOG_ERR,"cyl=[%ld],templ=[%s]\n",cyl,templ);
	}
	for(int j=strlen(tempoutdata);j<sizeof(tempoutdata)-1;j++){
		tempoutdata[j]  = '0';
	}
	strcpy(outdata,tempoutdata);
	//writelog(LOG_ERR,"outdata=[%s]\n",outdata);
	return 0;
}


int decryrsa(char *oridata,char *outdata){
	long n,e;
	int ret =0;
	 int idn=2100;
	 int ide=2102;
	 char bufn[20]="";
	 char bufe[20]="";
	ret = GetSysParaVal(idn, bufn);
	if(ret){
		return E_DB_TRADESERIALERROR_R;
	}
	ret = GetSysParaVal(ide, bufe);
	if(ret){
		return E_DB_TRADESERIALERROR_R;
	}
	n=atol(bufn);
	e=atol(bufe);
	
	int i=0;
	char templ[sizeof(long)*8+1]="";
	
	for(i=0;i<sizeof(oridata);i++){
		long t = (long)oridata[i];
		t = t+10;
		long cyl =rsa(t,e,n);
		//ltoa(cyl,templ,10);
		sprintf(templ,"%ld",cyl);
		strcat(outdata,templ);
		
	
	}
	
	return 0;
}


