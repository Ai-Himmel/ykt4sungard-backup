/****************************************************************************
* 操作步骤
* 1、调用ComOpen打开串口
* 2、打开串口后，调用ReadCardInfo读卡信息
* 3、调用ComClose关闭串口
* 4、调用GetLastErrMsg来取得错误信息
****************************************************************************/
//所有的正常返回值都是0，如果不为0，可以调用GetLastErrMsg来取得错误信息

#ifndef __KSCARDCOM_H__
#define __KSCARDCOM_H__
	
#pragma pack(1)
typedef struct{
	char sStdNo[21];				//学/工号
	char sName[9];					//姓名
	char sDeptNo[11];				//部门号
	char sCutType[5];				//客户类型
	unsigned long ulCardNo;			//卡号
	unsigned long ulEndDate;		//到期日期
	unsigned long ulSerialNo;		//卡序列号
}CARD_INFO;	
#pragma pack()

/****************************************************************************
* 功能 ........初始化发卡设备，返回设备句柄
* 参数.........int iPort：端口号;通讯速率是固定的19200
* 作者 ........闻剑
* 日期 ........2005/08/05
* 公司 ........复旦金仕达计算机系统有限公司
****************************************************************************/
//int com_init(__int16 port,long baud);
/****************************************************************************
* 功能 ........停止操作发卡机
* 参数.........void
* 作者 ........闻剑
* 日期 ........2005/08/05
* 公司 ........复旦金仕达计算机系统有限公司
****************************************************************************/
//int __stdcall ComClose(void);
/****************************************************************************
* 功能 ........控制读头发出一声叫声
* 参数.........void
* 作者 ........闻剑
* 日期 ........2005/08/05
* 公司 ........复旦金仕达计算机系统有限公司
****************************************************************************/
//int __stdcall ComBeep(void);
/****************************************************************************
* 功能 ........控制读头发出一声叫声
* 参数.........void
* 作者 ........闻剑
* 日期 ........2005/08/05
* 公司 ........复旦金仕达计算机系统有限公司
****************************************************************************/
//int __stdcall ReadCardInfo(CARD_INFO* pCI);
/****************************************************************************
* 功能 ........读卡信息
* 参数.........CARD_INFO* pCI：卡信息结构体指针
* 作者 ........闻剑
* 日期 ........2005/08/05
* 公司 ........复旦金仕达计算机系统有限公司
****************************************************************************/
//void __stdcall GetLastErrMsg(char *sMsg);
/****************************************************************************
* 功能 ........取函数操作失败的错误信息
* 参数.........sMsg字符串 输出参数，存放错误信息
* 作者 ........闻剑
* 日期 ........2005/08/05
* 公司 ........复旦金仕达计算机系统有限公司
****************************************************************************/

typedef int (__stdcall* lp_ComOpen)(__int16 port,long baud);
typedef int (__stdcall* lp_ComClose)(void);
typedef int (__stdcall* lp_ComBeep)(void);
typedef int (__stdcall* lp_ReadCardInfo)(CARD_INFO* pCI);
typedef int (__stdcall* lp_GetLastErrMsg)(char *sMsg);
typedef int (__stdcall* lp_ReadCardSNR)(unsigned long * snr);

int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;
extern lp_ComOpen			ComOpen;
extern lp_ComClose			ComClose;
extern lp_ComBeep			ComBeep;
extern lp_ReadCardInfo		ReadCardInfo;
extern lp_GetLastErrMsg	GetLastErrMsg;
extern lp_ReadCardSNR ReadCardSNR;

#endif