/* --------------------------------------------
* ��������: F847600.cpp
* ��������: 2007-5-11
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: �����Ž�����ͬ��
* --------------------------------------------
* �޸�����:
* �޸���Ա:
* �޸�����:
* �汾��Ϣ:
* ��ע��Ϣ:
* --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
//#include "ComFunNetCharge.h"
#include <sstream>
#include <iostream>
#include "DllFun.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	<card-info>
	<card>
	<phy-id>������ID</phy-id>
	<cardid>���׿���</cardid>
	<stuempno>ѧ����</stuempno>
	<blk-version>�汾��</blk-version>
	<flag>��־ 0:���,1:��ʧ,2ע��,3:����,4:����,9:����</flag>
	<exp-date>��Ч��</exp-date>
	</card>
	</card-info>
	*/
int F847600(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	std::stringstream data_str;
	ksf_server_conf server_cfg;
	ksf_xml_data *xml_data = NULL;
	ksf_card_result res;

	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_LVOL10, 0);

	//memset(xml_data,0,sizeof xml_data);
	data_str<<"<phy-id>"
		<<in_pack->sname<<"</phy-id><cardid>"
		<<in_pack->lvol2<<"</cardid><stuempno>"
		<<in_pack->sname2<<"</stuempno><blk-version>"
		<<in_pack->sholder_ac_no<<"</blk-version><exp-date>"
		<<in_pack->spager<<"</exp-date><flag>"
		<<in_pack->lvol1<<"</flag>";

	if(g_global_module.module_receive)
	{
		memset(&res,0,sizeof res);
		memset(&server_cfg,0,sizeof server_cfg);
		memset(&xml_data,0,sizeof xml_data);
		int len = sizeof(ksf_xml_data) - sizeof(char[1]) + data_str.str().length();
		xml_data = (ksf_xml_data *)malloc(len+1);
		xml_data->length = data_str.str().length();
		xml_data->func_no = 400000;
		xml_data->count = 1;
		memcpy(xml_data->data,data_str.str().c_str(),xml_data->length);
		xml_data->data[xml_data->length]='\0';
		ret = g_global_module.module_receive(&server_cfg,xml_data,&res);
	}
	if(xml_data)
	{
		free(xml_data);
		xml_data = NULL;
	}
	if(res.ret == RET_OK)
	{
		std::cout<<"�������ݳɹ�["<<g_global_module.module_name<< std::endl;
		out_pack->lvol10 = 10;
	}

	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif