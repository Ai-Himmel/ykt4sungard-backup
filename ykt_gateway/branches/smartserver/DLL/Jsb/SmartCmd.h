#ifndef __SMART_CMD_H__
#define __SMART_CMD_H__


//******************************************************************************
//*名称: TSSmartMacCmd
//*功能: 机器相关的命令设置
//******************************************************************************
struct TSSmartMacCmd
{
	char  szMacCode[8];
	char  szCommand[8];
	char  szFormat[32];
	int   nLen;
};

//******************************************************************************
//*名称: TSSmartCmdUnit
//*功能: 命令设置
//******************************************************************************
struct TSSmartCmdUnit
{
	long  nCmdIndex;				//命令索引
	char  szInFormat[32];           //参数输入格式
	char  szOutFormat[32];          //结果输出格式
	char  szCommand[8];             //通用的命令字
	char  szFormat[32];             //通用的命令格式
	int   nLen;						//命令体长度

	long  nMacCount;				//机型数量
	TSSmartMacCmd *pMacCmd;			//机型命令数量
};


#endif //__SMART_CMD_H__