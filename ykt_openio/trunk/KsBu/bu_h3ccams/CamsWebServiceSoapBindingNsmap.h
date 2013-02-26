
#include "soapH.h"
#ifndef   __NAMESPACE_SOAP
#define   __NAMESPACE_SOAP
#pragma once
SOAP_NMAC struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns2", "urn:PayParam", NULL, NULL},
	{"ns3", "urn:RetDelUserInfo", NULL, NULL},
	{"ns4", "urn:LanAccessDetailInfo", NULL, NULL},
	{"ns5", "urn:LanAccessDetailList", NULL, NULL},
	{"ns6", "urn:RandomInfo", NULL, NULL},
	{"ns7", "urn:MultiResult", NULL, NULL},
	{"ns8", "urn:RetUserInfo", NULL, NULL},
	{"ns9", "urn:AcctBasicInfo", NULL, NULL},
	{"ns10", "urn:RetAccountList", NULL, NULL},
	{"ns11", "urn:RetPassword", NULL, NULL},
	{"ns12", "urn:AcctServiceInfo", NULL, NULL},
	{"ns13", "urn:RetAcctServiceInfo", NULL, NULL},
	{"ns14", "urn:UserAppendInfo", NULL, NULL},
	{"ns15", "urn:RetUserAppendInfo", NULL, NULL},
	{"ns16", "urn:BlackListInfo", NULL, NULL},
	{"ns17", "urn:BlackList", NULL, NULL},
	{"ns18", "urn:LanServiceInfo", NULL, NULL},
	{"ns19", "urn:LanServiceList", NULL, NULL},
	{"ns20", "urn:SingleResult", NULL, NULL},
	{"ns21", "urn:UserBalance", NULL, NULL},
	{"ns22", "urn:ResultBase", NULL, NULL},
	{"ns23", "urn:OperatorInfo", NULL, NULL},
	{"ns24", "urn:QueryActionInfo", NULL, NULL},
	{"ns25", "urn:ApplyServiceInfo", NULL, NULL},
	{"ns26", "urn:AddAcctParam", NULL, NULL},
	{"ns27", "urn:ModifyAcctParam", NULL, NULL},
	{"ns28", "urn:DelAcctParam", NULL, NULL},
	{"ns29", "urn:ChgAcctPassParam", NULL, NULL},
	{"ns30", "urn:ApplyServiceParam", NULL, NULL},
	{"ns31", "urn:DelUserServiceParam", NULL, NULL},
	{"ns32", "urn:BlackListQueryInfo", NULL, NULL},
	{"ns33", "urn:LanQryCondition", NULL, NULL},
	{"ns34", "urn:LanAccessDetailQueryInfo", NULL, NULL},
	{"ns35", "urn:AccountListQueryInfo", NULL, NULL},
	{"ns36", "urn:BindParam", NULL, NULL},
	{"ns37", "http://csi.huawei.com", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
#endif