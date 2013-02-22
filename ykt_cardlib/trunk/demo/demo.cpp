#include "carddll_def.h"


static int Login_Collect_Card(int sector)
{
	unsigned char ucSerialNo[5], ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	//1 --- 计算KEYA
	GenerateKeyA(ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(sector,ucKeyA,0);                       
	if(ret != 0)
	{
		return -2;//卡片登陆失败
	}
	return 0;
}

int main(int argc,char **argv)
{
	
}