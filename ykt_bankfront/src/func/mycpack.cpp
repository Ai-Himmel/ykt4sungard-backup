#include "mycpack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpack.h"
#include "XPack.h"

void printCpackFieldValue(ST_CPACK *cpack)
{
	int iLastFidx;
	char sFieldValue[512];

	CXPack *pXPack=(CXPack *)GetDefaultXPack();
	const ST_PDATALIST *PDataList;
	PDataList=pXPack->GetPackDef(iLastFidx);
	for(int i=0;i<iLastFidx;i++)
	{
		if(pXPack->IsValidField(&(cpack->head),i))
		{
			pXPack->GetFieldValue(&(cpack->pack),i,sFieldValue);
			printf("%-16s[%s]\n",PDataList[i].szName,sFieldValue);
		}
	}
}

int getCpackFieldValue(ST_CPACK *cpack,const char* fieldName,char *fieldVal)
{
#define GetStr(a)	{ strcpy(fieldVal,(char*)cpack->pack.a);return 0;}//CHAR[]
#define GetInt(a)	{ sprintf(fieldVal,"%d",cpack->pack.a);return 0;}//INT
#define GetFolat(a)	{ sprintf(fieldVal,"%lf",cpack->pack.a);return 0;}//DOUBLR
	if(!strcmp(fieldName,"scust_no"))				GetStr(scust_no)
	if(!strcmp(fieldName,"scust_no2"))				GetStr(scust_no2)
	if(!strcmp(fieldName,"sholder_ac_no"))				GetStr(sholder_ac_no)
	if(!strcmp(fieldName,"sholder_ac_no2"))				GetStr(sholder_ac_no2)
	if(!strcmp(fieldName,"sholder_type"))				GetStr(sholder_type)
	if(!strcmp(fieldName,"sholder_type2"))				GetStr(sholder_type2)
	if(!strcmp(fieldName,"sname"))				GetStr(sname)
	if(!strcmp(fieldName,"sname2"))				GetStr(sname2)
	if(!strcmp(fieldName,"sall_name"))				GetStr(sall_name)
	if(!strcmp(fieldName,"smarket_code"))				GetStr(smarket_code)
	if(!strcmp(fieldName,"smarket_code2"))				GetStr(smarket_code2)
	if(!strcmp(fieldName,"sdate0"))				GetStr(sdate0)
	if(!strcmp(fieldName,"sdate1"))				GetStr(sdate1)
	if(!strcmp(fieldName,"sdate2"))				GetStr(sdate2)
	if(!strcmp(fieldName,"sdate3"))				GetStr(sdate3)
	if(!strcmp(fieldName,"stime0"))				GetStr(stime0)
	if(!strcmp(fieldName,"stime1"))				GetStr(stime1)
	if(!strcmp(fieldName,"stime2"))				GetStr(stime2)
	if(!strcmp(fieldName,"stime3"))				GetStr(stime3)
	if(!strcmp(fieldName,"lvol0"))				GetInt(lvol0)
	if(!strcmp(fieldName,"lvol1"))				GetInt(lvol1)
	if(!strcmp(fieldName,"lvol2"))				GetInt(lvol2)
	if(!strcmp(fieldName,"lvol3"))				GetInt(lvol3)
	if(!strcmp(fieldName,"lvol4"))				GetInt(lvol4)
	if(!strcmp(fieldName,"lvol5"))				GetInt(lvol5)
	if(!strcmp(fieldName,"lvol6"))				GetInt(lvol6)
	if(!strcmp(fieldName,"lvol7"))				GetInt(lvol7)
	if(!strcmp(fieldName,"lvol8"))				GetInt(lvol8)
	if(!strcmp(fieldName,"lvol9"))				GetInt(lvol9)
	if(!strcmp(fieldName,"lvol10"))				GetInt(lvol10)
	if(!strcmp(fieldName,"lvol11"))				GetInt(lvol11)
	if(!strcmp(fieldName,"lvol12"))				GetInt(lvol12)
	if(!strcmp(fieldName,"damt0"))				GetFolat(damt0)
	if(!strcmp(fieldName,"damt1"))				GetFolat(damt1)
	if(!strcmp(fieldName,"damt2"))				GetFolat(damt2)
	if(!strcmp(fieldName,"damt3"))				GetFolat(damt3)
	if(!strcmp(fieldName,"damt4"))				GetFolat(damt4)
	if(!strcmp(fieldName,"damt5"))				GetFolat(damt5)
	if(!strcmp(fieldName,"damt6"))				GetFolat(damt6)
	if(!strcmp(fieldName,"damt7"))				GetFolat(damt7)
	if(!strcmp(fieldName,"damt8"))				GetFolat(damt8)
	if(!strcmp(fieldName,"damt9"))				GetFolat(damt9)
	if(!strcmp(fieldName,"damt10"))				GetFolat(damt10)
	if(!strcmp(fieldName,"damt11"))				GetFolat(damt11)
	if(!strcmp(fieldName,"damt12"))				GetFolat(damt12)
	if(!strcmp(fieldName,"damt13"))				GetFolat(damt13)
	if(!strcmp(fieldName,"damt14"))				GetFolat(damt14)
	if(!strcmp(fieldName,"damt15"))				GetFolat(damt15)
	if(!strcmp(fieldName,"damt16"))				GetFolat(damt16)
	if(!strcmp(fieldName,"damt17"))				GetFolat(damt17)
	if(!strcmp(fieldName,"damt18"))				GetFolat(damt18)
	if(!strcmp(fieldName,"damt19"))				GetFolat(damt19)
	if(!strcmp(fieldName,"damt20"))				GetFolat(damt20)
	if(!strcmp(fieldName,"damt21"))				GetFolat(damt21)
	if(!strcmp(fieldName,"damt22"))				GetFolat(damt22)
	if(!strcmp(fieldName,"damt23"))				GetFolat(damt23)
	if(!strcmp(fieldName,"damt24"))				GetFolat(damt24)
	if(!strcmp(fieldName,"damt25"))				GetFolat(damt25)
	if(!strcmp(fieldName,"damt26"))				GetFolat(damt26)
	if(!strcmp(fieldName,"damt27"))				GetFolat(damt27)
	if(!strcmp(fieldName,"damt28"))				GetFolat(damt28)
	if(!strcmp(fieldName,"damt29"))				GetFolat(damt29)
	if(!strcmp(fieldName,"damt30"))				GetFolat(damt30)
	if(!strcmp(fieldName,"damt31"))				GetFolat(damt31)
	if(!strcmp(fieldName,"damt32"))				GetFolat(damt32)
	if(!strcmp(fieldName,"damt33"))				GetFolat(damt33)
	if(!strcmp(fieldName,"sstock_code"))				GetStr(sstock_code)
	if(!strcmp(fieldName,"sstock_code2"))				GetStr(sstock_code2)
	if(!strcmp(fieldName,"scust_type"))				GetStr(scust_type)
	if(!strcmp(fieldName,"scust_type2"))				GetStr(scust_type2)
	if(!strcmp(fieldName,"sstat_type"))				GetStr(sstat_type)
	if(!strcmp(fieldName,"sstat_type2"))				GetStr(sstat_type2)
	if(!strcmp(fieldName,"sroom_no"))				GetStr(sroom_no)
	if(!strcmp(fieldName,"sroom_no2"))				GetStr(sroom_no2)
	if(!strcmp(fieldName,"sopen_emp"))				GetStr(sopen_emp)
	if(!strcmp(fieldName,"sclose_emp"))				GetStr(sclose_emp)
	if(!strcmp(fieldName,"schange_emp"))				GetStr(schange_emp)
	if(!strcmp(fieldName,"scheck_emp"))				GetStr(scheck_emp)
	if(!strcmp(fieldName,"semp"))				GetStr(semp)
	if(!strcmp(fieldName,"snation_code"))				GetStr(snation_code)
	if(!strcmp(fieldName,"lcert_code"))				GetInt(lcert_code)
	if(!strcmp(fieldName,"stx_pwd"))				GetStr(stx_pwd)
	if(!strcmp(fieldName,"stx_pwd2"))				GetStr(stx_pwd2)
	if(!strcmp(fieldName,"swithdraw_pwd"))				GetStr(swithdraw_pwd)
	if(!strcmp(fieldName,"swithdraw_pwd2"))				GetStr(swithdraw_pwd2)
	if(!strcmp(fieldName,"semp_pwd"))				GetStr(semp_pwd)
	if(!strcmp(fieldName,"semp_pwd2"))				GetStr(semp_pwd2)
	if(!strcmp(fieldName,"sbank_pwd"))				GetStr(sbank_pwd)
	if(!strcmp(fieldName,"sbank_pwd2"))				GetStr(sbank_pwd2)
	if(!strcmp(fieldName,"scust_auth"))				GetStr(scust_auth)
	if(!strcmp(fieldName,"scust_auth2"))				GetStr(scust_auth2)
	if(!strcmp(fieldName,"scust_limit"))				GetStr(scust_limit)
	if(!strcmp(fieldName,"scust_limit2"))				GetStr(scust_limit2)
	if(!strcmp(fieldName,"lsafe_level"))				GetInt(lsafe_level)
	if(!strcmp(fieldName,"lsafe_level2"))				GetInt(lsafe_level2)
	if(!strcmp(fieldName,"spost_code"))				GetStr(spost_code)
	if(!strcmp(fieldName,"spost_code2"))				GetStr(spost_code2)
	if(!strcmp(fieldName,"sphone"))				GetStr(sphone)
	if(!strcmp(fieldName,"sphone2"))				GetStr(sphone2)
	if(!strcmp(fieldName,"sphone3"))				GetStr(sphone3)
	if(!strcmp(fieldName,"spager"))				GetStr(spager)
	if(!strcmp(fieldName,"semail"))				GetStr(semail)
	if(!strcmp(fieldName,"semail2"))				GetStr(semail2)
	if(!strcmp(fieldName,"snote"))				GetStr(snote)
	if(!strcmp(fieldName,"snote2"))				GetStr(snote2)
	if(!strcmp(fieldName,"scert_no"))				GetStr(scert_no)
	if(!strcmp(fieldName,"scert_no2"))				GetStr(scert_no2)
	if(!strcmp(fieldName,"scert_addr"))				GetStr(scert_addr)
	if(!strcmp(fieldName,"sstatus0"))				GetStr(sstatus0)
	if(!strcmp(fieldName,"sstatus1"))				GetStr(sstatus1)
	if(!strcmp(fieldName,"sstatus2"))				GetStr(sstatus2)
	if(!strcmp(fieldName,"sstatus3"))				GetStr(sstatus3)
	if(!strcmp(fieldName,"sstatus4"))				GetStr(sstatus4)
	if(!strcmp(fieldName,"lwithdraw_flag"))				GetInt(lwithdraw_flag)
	if(!strcmp(fieldName,"saddr"))				GetStr(saddr)
	if(!strcmp(fieldName,"saddr2"))				GetStr(saddr2)
	if(!strcmp(fieldName,"sserial0"))				GetStr(sserial0)
	if(!strcmp(fieldName,"sserial1"))				GetStr(sserial1)
	if(!strcmp(fieldName,"sserial2"))				GetStr(sserial2)
	if(!strcmp(fieldName,"sserial3"))				GetStr(sserial3)
	if(!strcmp(fieldName,"sserial4"))				GetStr(sserial4)
	if(!strcmp(fieldName,"scurrency_type"))				GetStr(scurrency_type)
	if(!strcmp(fieldName,"scurrency_type2"))				GetStr(scurrency_type2)
	if(!strcmp(fieldName,"sbranch_code0"))				GetStr(sbranch_code0)
	if(!strcmp(fieldName,"sbranch_code1"))				GetStr(sbranch_code1)
	if(!strcmp(fieldName,"sbranch_code2"))				GetStr(sbranch_code2)
	if(!strcmp(fieldName,"usset0"))				GetStr(usset0)
	if(!strcmp(fieldName,"usset1"))				GetStr(usset1)
	if(!strcmp(fieldName,"usset2"))				GetStr(usset2)
	if(!strcmp(fieldName,"usset3"))				GetStr(usset3)
	if(!strcmp(fieldName,"usset4"))				GetStr(usset4)
	if(!strcmp(fieldName,"usset5"))				GetStr(usset5)
	if(!strcmp(fieldName,"usset6"))				GetStr(usset6)
	if(!strcmp(fieldName,"sstation0"))				GetStr(sstation0)
	if(!strcmp(fieldName,"sstation1"))				GetStr(sstation1)
	if(!strcmp(fieldName,"sbank_acc"))				GetStr(sbank_acc)
	if(!strcmp(fieldName,"sbank_acc2"))				GetStr(sbank_acc2)
	if(!strcmp(fieldName,"lbank_acc_type"))				GetInt(lbank_acc_type)
	if(!strcmp(fieldName,"lbank_acc_type2"))				GetInt(lbank_acc_type2)
	if(!strcmp(fieldName,"smain_flag"))				GetStr(smain_flag)
	if(!strcmp(fieldName,"smain_flag2"))				GetStr(smain_flag2)
	if(!strcmp(fieldName,"sbank_code"))				GetStr(sbank_code)
	if(!strcmp(fieldName,"sbank_code2"))				GetStr(sbank_code2)
	if(!strcmp(fieldName,"semp_no"))				GetStr(semp_no)
	if(!strcmp(fieldName,"semp_no2"))				GetStr(semp_no2)
	if(!strcmp(fieldName,"drate0"))				GetFolat(drate0)
	if(!strcmp(fieldName,"drate1"))				GetFolat(drate1)
	if(!strcmp(fieldName,"lserial0"))				GetInt(lserial0)
	if(!strcmp(fieldName,"lserial1"))				GetInt(lserial1)
	if(!strcmp(fieldName,"sbankname"))				GetStr(sbankname)
	if(!strcmp(fieldName,"sbankname2"))				GetStr(sbankname2)
	if(!strcmp(fieldName,"scard0"))				GetStr(scard0)
	if(!strcmp(fieldName,"scard1"))				GetStr(scard1)
	if(!strcmp(fieldName,"sorder0"))				GetStr(sorder0)
	if(!strcmp(fieldName,"sorder1"))				GetStr(sorder1)
	if(!strcmp(fieldName,"sorder2"))				GetStr(sorder2)
	if(!strcmp(fieldName,"scusttypes"))				GetStr(scusttypes)
	if(!strcmp(fieldName,"ssectypes"))				GetStr(ssectypes)
	if(!strcmp(fieldName,"vsmess"))				GetStr(vsmess)
	if(!strcmp(fieldName,"vsvarstr0"))				GetStr(vsvarstr0)
	if(!strcmp(fieldName,"vsvarstr1"))				GetStr(vsvarstr1)
	if(!strcmp(fieldName,"vsvarstr2"))				GetStr(vsvarstr2)
	if(!strcmp(fieldName,"vsvarstr3"))				GetStr(vsvarstr3)
	else { return -1;}
	return 0;
}

int setCpackFieldValue(ST_CPACK *cpack,const char* fieldName,const char* fieldVal)
{
#define setStr(a)	{ strncpy((char *)cpack->pack.a,fieldVal,sizeof(cpack->pack.a)-1);cpack->pack.a[sizeof(cpack->pack.a)-1]=0;}//CHAR[]
#define setInt(a)	{ cpack->pack.a=atol(fieldVal);}//INT
#define setFloat(a)	{ cpack->pack.a=atof(fieldVal);}//LONG
	if(!strcmp(fieldName,"scust_no"))
	{
		SetParmBit(&(cpack->head),F_SCUST_NO);
		setStr(scust_no);
		return 0;
	}
	if(!strcmp(fieldName,"scust_no2"))
	{
		SetParmBit(&(cpack->head),F_SCUST_NO2);
		setStr(scust_no2);
		return 0;
	}
	if(!strcmp(fieldName,"sholder_ac_no"))
	{
		SetParmBit(&(cpack->head),F_SHOLDER_AC_NO);
		setStr(sholder_ac_no);
		return 0;
	}
	if(!strcmp(fieldName,"sholder_ac_no2"))
	{
		SetParmBit(&(cpack->head),F_SHOLDER_AC_NO2);
		setStr(sholder_ac_no2);
		return 0;
	}
	if(!strcmp(fieldName,"sholder_type"))
	{
		SetParmBit(&(cpack->head),F_SHOLDER_TYPE);
		setStr(sholder_type);
		return 0;
	}
	if(!strcmp(fieldName,"sholder_type2"))
	{
		SetParmBit(&(cpack->head),F_SHOLDER_TYPE2);
		setStr(sholder_type2);
		return 0;
	}
	if(!strcmp(fieldName,"sname"))
	{
		SetParmBit(&(cpack->head),F_SNAME);
		setStr(sname);
		return 0;
	}
	if(!strcmp(fieldName,"sname2"))
	{
		SetParmBit(&(cpack->head),F_SNAME2);
		setStr(sname2);
		return 0;
	}
	if(!strcmp(fieldName,"sall_name"))
	{
		SetParmBit(&(cpack->head),F_SALL_NAME);
		setStr(sall_name);
		return 0;
	}
	if(!strcmp(fieldName,"smarket_code"))
	{
		SetParmBit(&(cpack->head),F_SMARKET_CODE);
		setStr(smarket_code);
		return 0;
	}
	if(!strcmp(fieldName,"smarket_code2"))
	{
		SetParmBit(&(cpack->head),F_SMARKET_CODE2);
		setStr(smarket_code2);
		return 0;
	}
	if(!strcmp(fieldName,"sdate0"))
	{
		SetParmBit(&(cpack->head),F_SDATE0);
		setStr(sdate0);
		return 0;
	}
	if(!strcmp(fieldName,"sdate1"))
	{
		SetParmBit(&(cpack->head),F_SDATE1);
		setStr(sdate1);
		return 0;
	}
	if(!strcmp(fieldName,"sdate2"))
	{
		SetParmBit(&(cpack->head),F_SDATE2);
		setStr(sdate2);
		return 0;
	}
	if(!strcmp(fieldName,"sdate3"))
	{
		SetParmBit(&(cpack->head),F_SDATE3);
		setStr(sdate3);
		return 0;
	}
	if(!strcmp(fieldName,"stime0"))
	{
		SetParmBit(&(cpack->head),F_STIME0);
		setStr(stime0);
		return 0;
	}
	if(!strcmp(fieldName,"stime1"))
	{
		SetParmBit(&(cpack->head),F_STIME1);
		setStr(stime1);
		return 0;
	}
	if(!strcmp(fieldName,"stime2"))
	{
		SetParmBit(&(cpack->head),F_STIME2);
		setStr(stime2);
		return 0;
	}
	if(!strcmp(fieldName,"stime3"))
	{
		SetParmBit(&(cpack->head),F_STIME3);
		setStr(stime3);
		return 0;
	}
	if(!strcmp(fieldName,"lvol0"))
	{
		SetParmBit(&(cpack->head),F_LVOL0);
		setInt(lvol0);
		return 0;
	}
	if(!strcmp(fieldName,"lvol1"))
	{
		SetParmBit(&(cpack->head),F_LVOL1);
		setInt(lvol1);
		return 0;
	}
	if(!strcmp(fieldName,"lvol2"))
	{
		SetParmBit(&(cpack->head),F_LVOL2);
		setInt(lvol2);
		return 0;
	}
	if(!strcmp(fieldName,"lvol3"))
	{
		SetParmBit(&(cpack->head),F_LVOL3);
		setInt(lvol3);
		return 0;
	}
	if(!strcmp(fieldName,"lvol4"))
	{
		SetParmBit(&(cpack->head),F_LVOL4);
		setInt(lvol4);
		return 0;
	}
	if(!strcmp(fieldName,"lvol5"))
	{
		SetParmBit(&(cpack->head),F_LVOL5);
		setInt(lvol5);
		return 0;
	}
	if(!strcmp(fieldName,"lvol6"))
	{
		SetParmBit(&(cpack->head),F_LVOL6);
		setInt(lvol6);
		return 0;
	}
	if(!strcmp(fieldName,"lvol7"))
	{
		SetParmBit(&(cpack->head),F_LVOL7);
		setInt(lvol7);
		return 0;
	}
	if(!strcmp(fieldName,"lvol8"))
	{
		SetParmBit(&(cpack->head),F_LVOL8);
		setInt(lvol8);
		return 0;
	}
	if(!strcmp(fieldName,"lvol9"))
	{
		SetParmBit(&(cpack->head),F_LVOL9);
		setInt(lvol9);
		return 0;
	}
	if(!strcmp(fieldName,"lvol10"))
	{
		SetParmBit(&(cpack->head),F_LVOL10);
		setInt(lvol10);
		return 0;
	}
	if(!strcmp(fieldName,"lvol11"))
	{
		SetParmBit(&(cpack->head),F_LVOL11);
		setInt(lvol11);
		return 0;
	}
	if(!strcmp(fieldName,"lvol12"))
	{
		SetParmBit(&(cpack->head),F_LVOL12);
		setInt(lvol12);
		return 0;
	}
	if(!strcmp(fieldName,"damt0"))
	{
		SetParmBit(&(cpack->head),F_DAMT0);
		setFloat(damt0);
		return 0;
	}
	if(!strcmp(fieldName,"damt1"))
	{
		SetParmBit(&(cpack->head),F_DAMT1);
		setFloat(damt1);
		return 0;
	}
	if(!strcmp(fieldName,"damt2"))
	{
		SetParmBit(&(cpack->head),F_DAMT2);
		setFloat(damt2);
		return 0;
	}
	if(!strcmp(fieldName,"damt3"))
	{
		SetParmBit(&(cpack->head),F_DAMT3);
		setFloat(damt3);
		return 0;
	}
	if(!strcmp(fieldName,"damt4"))
	{
		SetParmBit(&(cpack->head),F_DAMT4);
		setFloat(damt4);
		return 0;
	}
	if(!strcmp(fieldName,"damt5"))
	{
		SetParmBit(&(cpack->head),F_DAMT5);
		setFloat(damt5);
		return 0;
	}
	if(!strcmp(fieldName,"damt6"))
	{
		SetParmBit(&(cpack->head),F_DAMT6);
		setFloat(damt6);
		return 0;
	}
	if(!strcmp(fieldName,"damt7"))
	{
		SetParmBit(&(cpack->head),F_DAMT7);
		setFloat(damt7);
		return 0;
	}
	if(!strcmp(fieldName,"damt8"))
	{
		SetParmBit(&(cpack->head),F_DAMT8);
		setFloat(damt8);
		return 0;
	}
	if(!strcmp(fieldName,"damt9"))
	{
		SetParmBit(&(cpack->head),F_DAMT9);
		setFloat(damt9);
		return 0;
	}
	if(!strcmp(fieldName,"damt10"))
	{
		SetParmBit(&(cpack->head),F_DAMT10);
		setFloat(damt10);
		return 0;
	}
	if(!strcmp(fieldName,"damt11"))
	{
		SetParmBit(&(cpack->head),F_DAMT11);
		setFloat(damt11);
		return 0;
	}
	if(!strcmp(fieldName,"damt12"))
	{
		SetParmBit(&(cpack->head),F_DAMT12);
		setFloat(damt12);
		return 0;
	}
	if(!strcmp(fieldName,"damt13"))
	{
		SetParmBit(&(cpack->head),F_DAMT13);
		setFloat(damt13);
		return 0;
	}
	if(!strcmp(fieldName,"damt14"))
	{
		SetParmBit(&(cpack->head),F_DAMT14);
		setFloat(damt14);
		return 0;
	}
	if(!strcmp(fieldName,"damt15"))
	{
		SetParmBit(&(cpack->head),F_DAMT15);
		setFloat(damt15);
		return 0;
	}
	if(!strcmp(fieldName,"damt16"))
	{
		SetParmBit(&(cpack->head),F_DAMT16);
		setFloat(damt16);
		return 0;
	}
	if(!strcmp(fieldName,"damt17"))
	{
		SetParmBit(&(cpack->head),F_DAMT17);
		setFloat(damt17);
		return 0;
	}
	if(!strcmp(fieldName,"damt18"))
	{
		SetParmBit(&(cpack->head),F_DAMT18);
		setFloat(damt18);
		return 0;
	}
	if(!strcmp(fieldName,"damt19"))
	{
		SetParmBit(&(cpack->head),F_DAMT19);
		setFloat(damt19);
		return 0;
	}
	if(!strcmp(fieldName,"damt20"))
	{
		SetParmBit(&(cpack->head),F_DAMT20);
		setFloat(damt20);
		return 0;
	}
	if(!strcmp(fieldName,"damt21"))
	{
		SetParmBit(&(cpack->head),F_DAMT21);
		setFloat(damt21);
		return 0;
	}
	if(!strcmp(fieldName,"damt22"))
	{
		SetParmBit(&(cpack->head),F_DAMT22);
		setFloat(damt22);
		return 0;
	}
	if(!strcmp(fieldName,"damt23"))
	{
		SetParmBit(&(cpack->head),F_DAMT23);
		setFloat(damt23);
		return 0;
	}
	if(!strcmp(fieldName,"damt24"))
	{
		SetParmBit(&(cpack->head),F_DAMT24);
		setFloat(damt24);
		return 0;
	}
	if(!strcmp(fieldName,"damt25"))
	{
		SetParmBit(&(cpack->head),F_DAMT25);
		setFloat(damt25);
		return 0;
	}
	if(!strcmp(fieldName,"damt26"))
	{
		SetParmBit(&(cpack->head),F_DAMT26);
		setFloat(damt26);
		return 0;
	}
	if(!strcmp(fieldName,"damt27"))
	{
		SetParmBit(&(cpack->head),F_DAMT27);
		setFloat(damt27);
		return 0;
	}
	if(!strcmp(fieldName,"damt28"))
	{
		SetParmBit(&(cpack->head),F_DAMT28);
		setFloat(damt28);
		return 0;
	}
	if(!strcmp(fieldName,"damt29"))
	{
		SetParmBit(&(cpack->head),F_DAMT29);
		setFloat(damt29);
		return 0;
	}
	if(!strcmp(fieldName,"damt30"))
	{
		SetParmBit(&(cpack->head),F_DAMT30);
		setFloat(damt30);
		return 0;
	}
	if(!strcmp(fieldName,"damt31"))
	{
		SetParmBit(&(cpack->head),F_DAMT31);
		setFloat(damt31);
		return 0;
	}
	if(!strcmp(fieldName,"damt32"))
	{
		SetParmBit(&(cpack->head),F_DAMT32);
		setFloat(damt32);
		return 0;
	}
	if(!strcmp(fieldName,"damt33"))
	{
		SetParmBit(&(cpack->head),F_DAMT33);
		setFloat(damt33);
		return 0;
	}
	if(!strcmp(fieldName,"sstock_code"))
	{
		SetParmBit(&(cpack->head),F_SSTOCK_CODE);
		setStr(sstock_code);
		return 0;
	}
	if(!strcmp(fieldName,"sstock_code2"))
	{
		SetParmBit(&(cpack->head),F_SSTOCK_CODE2);
		setStr(sstock_code2);
		return 0;
	}
	if(!strcmp(fieldName,"scust_type"))
	{
		SetParmBit(&(cpack->head),F_SCUST_TYPE);
		setStr(scust_type);
		return 0;
	}
	if(!strcmp(fieldName,"scust_type2"))
	{
		SetParmBit(&(cpack->head),F_SCUST_TYPE2);
		setStr(scust_type2);
		return 0;
	}
	if(!strcmp(fieldName,"sstat_type"))
	{
		SetParmBit(&(cpack->head),F_SSTAT_TYPE);
		setStr(sstat_type);
		return 0;
	}
	if(!strcmp(fieldName,"sstat_type2"))
	{
		SetParmBit(&(cpack->head),F_SSTAT_TYPE2);
		setStr(sstat_type2);
		return 0;
	}
	if(!strcmp(fieldName,"sroom_no"))
	{
		SetParmBit(&(cpack->head),F_SROOM_NO);
		setStr(sroom_no);
		return 0;
	}
	if(!strcmp(fieldName,"sroom_no2"))
	{
		SetParmBit(&(cpack->head),F_SROOM_NO2);
		setStr(sroom_no2);
		return 0;
	}
	if(!strcmp(fieldName,"sopen_emp"))
	{
		SetParmBit(&(cpack->head),F_SOPEN_EMP);
		setStr(sopen_emp);
		return 0;
	}
	if(!strcmp(fieldName,"sclose_emp"))
	{
		SetParmBit(&(cpack->head),F_SCLOSE_EMP);
		setStr(sclose_emp);
		return 0;
	}
	if(!strcmp(fieldName,"schange_emp"))
	{
		SetParmBit(&(cpack->head),F_SCHANGE_EMP);
		setStr(schange_emp);
		return 0;
	}
	if(!strcmp(fieldName,"scheck_emp"))
	{
		SetParmBit(&(cpack->head),F_SCHECK_EMP);
		setStr(scheck_emp);
		return 0;
	}
	if(!strcmp(fieldName,"semp"))
	{
		SetParmBit(&(cpack->head),F_SEMP);
		setStr(semp);
		return 0;
	}
	if(!strcmp(fieldName,"snation_code"))
	{
		SetParmBit(&(cpack->head),F_SNATION_CODE);
		setStr(snation_code);
		return 0;
	}
	if(!strcmp(fieldName,"lcert_code"))
	{
		SetParmBit(&(cpack->head),F_LCERT_CODE);
		setInt(lcert_code);
		return 0;
	}
	if(!strcmp(fieldName,"stx_pwd"))
	{
		SetParmBit(&(cpack->head),F_STX_PWD);
		setStr(stx_pwd);
		return 0;
	}
	if(!strcmp(fieldName,"stx_pwd2"))
	{
		SetParmBit(&(cpack->head),F_STX_PWD2);
		setStr(stx_pwd2);
		return 0;
	}
	if(!strcmp(fieldName,"swithdraw_pwd"))
	{
		SetParmBit(&(cpack->head),F_SWITHDRAW_PWD);
		setStr(swithdraw_pwd);
		return 0;
	}
	if(!strcmp(fieldName,"swithdraw_pwd2"))
	{
		SetParmBit(&(cpack->head),F_SWITHDRAW_PWD2);
		setStr(swithdraw_pwd2);
		return 0;
	}
	if(!strcmp(fieldName,"semp_pwd"))
	{
		SetParmBit(&(cpack->head),F_SEMP_PWD);
		setStr(semp_pwd);
		return 0;
	}
	if(!strcmp(fieldName,"semp_pwd2"))
	{
		SetParmBit(&(cpack->head),F_SEMP_PWD2);
		setStr(semp_pwd2);
		return 0;
	}
	if(!strcmp(fieldName,"sbank_pwd"))
	{
		SetParmBit(&(cpack->head),F_SBANK_PWD);
		setStr(sbank_pwd);
		return 0;
	}
	if(!strcmp(fieldName,"sbank_pwd2"))
	{
		SetParmBit(&(cpack->head),F_SBANK_PWD2);
		setStr(sbank_pwd2);
		return 0;
	}
	if(!strcmp(fieldName,"scust_auth"))
	{
		SetParmBit(&(cpack->head),F_SCUST_AUTH);
		setStr(scust_auth);
		return 0;
	}
	if(!strcmp(fieldName,"scust_auth2"))
	{
		SetParmBit(&(cpack->head),F_SCUST_AUTH2);
		setStr(scust_auth2);
		return 0;
	}
	if(!strcmp(fieldName,"scust_limit"))
	{
		SetParmBit(&(cpack->head),F_SCUST_LIMIT);
		setStr(scust_limit);
		return 0;
	}
	if(!strcmp(fieldName,"scust_limit2"))
	{
		SetParmBit(&(cpack->head),F_SCUST_LIMIT2);
		setStr(scust_limit2);
		return 0;
	}
	if(!strcmp(fieldName,"lsafe_level"))
	{
		SetParmBit(&(cpack->head),F_LSAFE_LEVEL);
		setInt(lsafe_level);
		return 0;
	}
	if(!strcmp(fieldName,"lsafe_level2"))
	{
		SetParmBit(&(cpack->head),F_LSAFE_LEVEL2);
		setInt(lsafe_level2);
		return 0;
	}
	if(!strcmp(fieldName,"spost_code"))
	{
		SetParmBit(&(cpack->head),F_SPOST_CODE);
		setStr(spost_code);
		return 0;
	}
	if(!strcmp(fieldName,"spost_code2"))
	{
		SetParmBit(&(cpack->head),F_SPOST_CODE2);
		setStr(spost_code2);
		return 0;
	}
	if(!strcmp(fieldName,"sphone"))
	{
		SetParmBit(&(cpack->head),F_SPHONE);
		setStr(sphone);
		return 0;
	}
	if(!strcmp(fieldName,"sphone2"))
	{
		SetParmBit(&(cpack->head),F_SPHONE2);
		setStr(sphone2);
		return 0;
	}
	if(!strcmp(fieldName,"sphone3"))
	{
		SetParmBit(&(cpack->head),F_SPHONE3);
		setStr(sphone3);
		return 0;
	}
	if(!strcmp(fieldName,"spager"))
	{
		SetParmBit(&(cpack->head),F_SPAGER);
		setStr(spager);
		return 0;
	}
	if(!strcmp(fieldName,"semail"))
	{
		SetParmBit(&(cpack->head),F_SEMAIL);
		setStr(semail);
		return 0;
	}
	if(!strcmp(fieldName,"semail2"))
	{
		SetParmBit(&(cpack->head),F_SEMAIL2);
		setStr(semail2);
		return 0;
	}
	if(!strcmp(fieldName,"snote"))
	{
		SetParmBit(&(cpack->head),F_SNOTE);
		setStr(snote);
		return 0;
	}
	if(!strcmp(fieldName,"snote2"))
	{
		SetParmBit(&(cpack->head),F_SNOTE2);
		setStr(snote2);
		return 0;
	}
	if(!strcmp(fieldName,"scert_no"))
	{
		SetParmBit(&(cpack->head),F_SCERT_NO);
		setStr(scert_no);
		return 0;
	}
	if(!strcmp(fieldName,"scert_no2"))
	{
		SetParmBit(&(cpack->head),F_SCERT_NO2);
		setStr(scert_no2);
		return 0;
	}
	if(!strcmp(fieldName,"scert_addr"))
	{
		SetParmBit(&(cpack->head),F_SCERT_ADDR);
		setStr(scert_addr);
		return 0;
	}
	if(!strcmp(fieldName,"sstatus0"))
	{
		SetParmBit(&(cpack->head),F_SSTATUS0);
		setStr(sstatus0);
		return 0;
	}
	if(!strcmp(fieldName,"sstatus1"))
	{
		SetParmBit(&(cpack->head),F_SSTATUS1);
		setStr(sstatus1);
		return 0;
	}
	if(!strcmp(fieldName,"sstatus2"))
	{
		SetParmBit(&(cpack->head),F_SSTATUS2);
		setStr(sstatus2);
		return 0;
	}
	if(!strcmp(fieldName,"sstatus3"))
	{
		SetParmBit(&(cpack->head),F_SSTATUS3);
		setStr(sstatus3);
		return 0;
	}
	if(!strcmp(fieldName,"sstatus4"))
	{
		SetParmBit(&(cpack->head),F_SSTATUS4);
		setStr(sstatus4);
		return 0;
	}
	if(!strcmp(fieldName,"lwithdraw_flag"))
	{
		SetParmBit(&(cpack->head),F_LWITHDRAW_FLAG);
		setInt(lwithdraw_flag);
		return 0;
	}
	if(!strcmp(fieldName,"saddr"))
	{
		SetParmBit(&(cpack->head),F_SADDR);
		setStr(saddr);
		return 0;
	}
	if(!strcmp(fieldName,"saddr2"))
	{
		SetParmBit(&(cpack->head),F_SADDR2);
		setStr(saddr2);
		return 0;
	}
	if(!strcmp(fieldName,"sserial0"))
	{
		SetParmBit(&(cpack->head),F_SSERIAL0);
		setStr(sserial0);
		return 0;
	}
	if(!strcmp(fieldName,"sserial1"))
	{
		SetParmBit(&(cpack->head),F_SSERIAL1);
		setStr(sserial1);
		return 0;
	}
	if(!strcmp(fieldName,"sserial2"))
	{
		SetParmBit(&(cpack->head),F_SSERIAL2);
		setStr(sserial2);
		return 0;
	}
	if(!strcmp(fieldName,"sserial3"))
	{
		SetParmBit(&(cpack->head),F_SSERIAL3);
		setStr(sserial3);
		return 0;
	}
	if(!strcmp(fieldName,"sserial4"))
	{
		SetParmBit(&(cpack->head),F_SSERIAL4);
		setStr(sserial4);
		return 0;
	}
	if(!strcmp(fieldName,"scurrency_type"))
	{
		SetParmBit(&(cpack->head),F_SCURRENCY_TYPE);
		setStr(scurrency_type);
		return 0;
	}
	if(!strcmp(fieldName,"scurrency_type2"))
	{
		SetParmBit(&(cpack->head),F_SCURRENCY_TYPE2);
		setStr(scurrency_type2);
		return 0;
	}
	if(!strcmp(fieldName,"sbranch_code0"))
	{
		SetParmBit(&(cpack->head),F_SBRANCH_CODE0);
		setStr(sbranch_code0);
		return 0;
	}
	if(!strcmp(fieldName,"sbranch_code1"))
	{
		SetParmBit(&(cpack->head),F_SBRANCH_CODE1);
		setStr(sbranch_code1);
		return 0;
	}
	if(!strcmp(fieldName,"sbranch_code2"))
	{
		SetParmBit(&(cpack->head),F_SBRANCH_CODE2);
		setStr(sbranch_code2);
		return 0;
	}
	if(!strcmp(fieldName,"usset0"))
	{
		SetParmBit(&(cpack->head),F_USSET0);
		setStr(usset0);
		return 0;
	}
	if(!strcmp(fieldName,"usset1"))
	{
		SetParmBit(&(cpack->head),F_USSET1);
		setStr(usset1);
		return 0;
	}
	if(!strcmp(fieldName,"usset2"))
	{
		SetParmBit(&(cpack->head),F_USSET2);
		setStr(usset2);
		return 0;
	}
	if(!strcmp(fieldName,"usset3"))
	{
		SetParmBit(&(cpack->head),F_USSET3);
		setStr(usset3);
		return 0;
	}
	if(!strcmp(fieldName,"usset4"))
	{
		SetParmBit(&(cpack->head),F_USSET4);
		setStr(usset4);
		return 0;
	}
	if(!strcmp(fieldName,"usset5"))
	{
		SetParmBit(&(cpack->head),F_USSET5);
		setStr(usset5);
		return 0;
	}
	if(!strcmp(fieldName,"usset6"))
	{
		SetParmBit(&(cpack->head),F_USSET6);
		setStr(usset6);
		return 0;
	}
	if(!strcmp(fieldName,"sstation0"))
	{
		SetParmBit(&(cpack->head),F_SSTATION0);
		setStr(sstation0);
		return 0;
	}
	if(!strcmp(fieldName,"sstation1"))
	{
		SetParmBit(&(cpack->head),F_SSTATION1);
		setStr(sstation1);
		return 0;
	}
	if(!strcmp(fieldName,"sbank_acc"))
	{
		SetParmBit(&(cpack->head),F_SBANK_ACC);
		setStr(sbank_acc);
		return 0;
	}
	if(!strcmp(fieldName,"sbank_acc2"))
	{
		SetParmBit(&(cpack->head),F_SBANK_ACC2);
		setStr(sbank_acc2);
		return 0;
	}
	if(!strcmp(fieldName,"lbank_acc_type"))
	{
		SetParmBit(&(cpack->head),F_LBANK_ACC_TYPE);
		setInt(lbank_acc_type);
		return 0;
	}
	if(!strcmp(fieldName,"lbank_acc_type2"))
	{
		SetParmBit(&(cpack->head),F_LBANK_ACC_TYPE2);
		setInt(lbank_acc_type2);
		return 0;
	}
	if(!strcmp(fieldName,"smain_flag"))
	{
		SetParmBit(&(cpack->head),F_SMAIN_FLAG);
		setStr(smain_flag);
		return 0;
	}
	if(!strcmp(fieldName,"smain_flag2"))
	{
		SetParmBit(&(cpack->head),F_SMAIN_FLAG2);
		setStr(smain_flag2);
		return 0;
	}
	if(!strcmp(fieldName,"sbank_code"))
	{
		SetParmBit(&(cpack->head),F_SBANK_CODE);
		setStr(sbank_code);
		return 0;
	}
	if(!strcmp(fieldName,"sbank_code2"))
	{
		SetParmBit(&(cpack->head),F_SBANK_CODE2);
		setStr(sbank_code2);
		return 0;
	}
	if(!strcmp(fieldName,"semp_no"))
	{
		SetParmBit(&(cpack->head),F_SEMP_NO);
		setStr(semp_no);
		return 0;
	}
	if(!strcmp(fieldName,"semp_no2"))
	{
		SetParmBit(&(cpack->head),F_SEMP_NO2);
		setStr(semp_no2);
		return 0;
	}
	if(!strcmp(fieldName,"drate0"))
	{
		SetParmBit(&(cpack->head),F_DRATE0);
		setFloat(drate0);
		return 0;
	}
	if(!strcmp(fieldName,"drate1"))
	{
		SetParmBit(&(cpack->head),F_DRATE1);
		setFloat(drate1);
		return 0;
	}
	if(!strcmp(fieldName,"lserial0"))
	{
		SetParmBit(&(cpack->head),F_LSERIAL0);
		setInt(lserial0);
		return 0;
	}
	if(!strcmp(fieldName,"lserial1"))
	{
		SetParmBit(&(cpack->head),F_LSERIAL1);
		setInt(lserial1);
		return 0;
	}
	if(!strcmp(fieldName,"sbankname"))
	{
		SetParmBit(&(cpack->head),F_SBANKNAME);
		setStr(sbankname);
		return 0;
	}
	if(!strcmp(fieldName,"sbankname2"))
	{
		SetParmBit(&(cpack->head),F_SBANKNAME2);
		setStr(sbankname2);
		return 0;
	}
	if(!strcmp(fieldName,"scard0"))
	{
		SetParmBit(&(cpack->head),F_SCARD0);
		setStr(scard0);
		return 0;
	}
	if(!strcmp(fieldName,"scard1"))
	{
		SetParmBit(&(cpack->head),F_SCARD1);
		setStr(scard1);
		return 0;
	}
	if(!strcmp(fieldName,"sorder0"))
	{
		SetParmBit(&(cpack->head),F_SORDER0);
		setStr(sorder0);
		return 0;
	}
	if(!strcmp(fieldName,"sorder1"))
	{
		SetParmBit(&(cpack->head),F_SORDER1);
		setStr(sorder1);
		return 0;
	}
	if(!strcmp(fieldName,"sorder2"))
	{
		SetParmBit(&(cpack->head),F_SORDER2);
		setStr(sorder2);
		return 0;
	}
	if(!strcmp(fieldName,"scusttypes"))
	{
		SetParmBit(&(cpack->head),F_SCUSTTYPES);
		setStr(scusttypes);
		return 0;
	}
	if(!strcmp(fieldName,"ssectypes"))
	{
		SetParmBit(&(cpack->head),F_SSECTYPES);
		setStr(ssectypes);
		return 0;
	}
	if(!strcmp(fieldName,"vsmess"))
	{
		SetParmBit(&(cpack->head),F_VSMESS);
		setStr(vsmess);
		return 0;
	}
	if(!strcmp(fieldName,"vsvarstr0"))
	{
		SetParmBit(&(cpack->head),F_VSVARSTR0);
		setStr(vsvarstr0);
		return 0;
	}
	if(!strcmp(fieldName,"vsvarstr1"))
	{
		SetParmBit(&(cpack->head),F_VSVARSTR1);
		setStr(vsvarstr1);
		return 0;
	}
	if(!strcmp(fieldName,"vsvarstr2"))
	{
		SetParmBit(&(cpack->head),F_VSVARSTR2);
		setStr(vsvarstr2);
		return 0;
	}
	if(!strcmp(fieldName,"vsvarstr3"))
	{
		SetParmBit(&(cpack->head),F_VSVARSTR3);
		setStr(vsvarstr3);
		return 0;
	}
	return -1;
}

