////////////////////////////��Ӧͷ����///////////////////////////
///////////////////////////ģʽ��ʱ��ι���//////////////////////
///////////////////////////��½������Ϣ��ѯ//////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"



////////////////////////////��Ӧͷ����///////////////////////////
#define   CMD_SEARCHSENSOR		0x96	//������Ӧͷ
#define   CMD_GETSENSORINFO		0x97	//�ϴ���Ӧͷ��Ϣ
#define   CMD_SETSENSORADDRESS	0x98	//���ø�Ӧͷ����
/// ���ܣ�������Ӧͷ
/// Ver1.0 ------ 20040303 Auth:Lina
int _stdcall MakeBuf_SearchSensor(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SEARCHSENSOR;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// ���ܣ��ϴ���Ӧͷ��Ϣ
/// Ver1.0 ----- 20040303 Auth:Lina
int _stdcall MakeBuf_GetSensorInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETSENSORINFO;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// ���ܣ����ø�Ӧͷ����
/// ������
///     No----��Ӧͷ����
///     Buffer----n*5�ֽ� 
int _stdcall MakeBuf_SetSensorAddress(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETSENSORADDRESS;
	addr          = pDevice->nAddr;
	len           = 5+5*No;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,5*No);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

////////////////////////////�����������/////////////////////////////////
#define CMD_SETFIRESTATE	0x9B	//����Ϊ����״̬
#define CMD_SETTHEFTSTATE   0x9C    //����Ϊ����״̬
#define CMD_SETNORMALSTATE  0x9D    //�ָ�Ϊ����״̬

/// ���ܣ�����Ϊ����״̬
/// Ver1.0 ------ 20040303 Auth:Lina
int _stdcall MakeBuf_SetFireState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETFIRESTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// ���ܣ�����Ϊ����״̬
/// Ver1.0 ------ 20040303 Auth:Lina
int _stdcall MakeBuf_SetTheftState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETTHEFTSTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// ���ܣ��ָ�Ϊ����״̬
/// Ver1.0 ------ 20040303 Auth:Lina 
int _stdcall MakeBuf_SetNormalState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETNORMALSTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

//////////////////////////////ģʽ��ʱ��ι���/////////////////////////
#define CMD_SETMODE3HOLIDAYINFO		0xB2	//����ģʽ���ڼ�����Ϣ
#define CMD_SETMODE3TIMEPHASEINFO	0xB3	//����ģʽ��ʱ�����Ϣ
#define CMD_GETMODE3HOLIDAYINFO     0xB4	//��ȡģʽ���ڼ�����Ϣ
#define CMD_GETMODE3TIMEPHASEINFO	0xB5	//��ȡģʽ��ʱ�����Ϣ


//////////////////////////////ģʽ��ʱ��ι���/////////////////////////
#define CMD_SETMODE4HOLIDAYINFO		0xCB	//����ģʽ�Ľڼ�����Ϣ
#define CMD_SETMODE4TIMEPHASEINFO	0xCD	//����ģʽ��ʱ�����Ϣ
#define CMD_GETMODE4HOLIDAYINFO     0xB4	//��ȡģʽ�Ľڼ�����Ϣ
#define CMD_GETMODE4TIMEPHASEINFO	0xB5	//��ȡģʽ��ʱ�����Ϣ


/// ���ܣ�����ģʽ���ڼ�����Ϣ
/// ������
///    No:�ڼ���������
///    Buffer:�ڼ�����Ϣ
/// Ver1.0 ------ 20040304 Auth:Lina
int _stdcall MakeBuf_SetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE3HOLIDAYINFO;
	addr          = pDevice->nAddr;
	len           = 5+2*No;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,2*No);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// ���ܣ�����ģʽ��ʱ�����Ϣ
/// ����:
///    WeekInfo:������Ϣ 1Byte
///    No:ʱ�����       1Byte
///    Buffer:ʱ�����Ϣ No*8 Byte
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo,int No,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE3TIMEPHASEINFO;
	addr          = pDevice->nAddr;
	len           = 6+8*No;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = WeekInfo;
	pBuffer->pBuffer[5] = No;
	memcpy(&pBuffer->pBuffer[6],Buffer,8*No);
	pBuffer->nCmdSize  = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// ���ܣ�����ģʽ��ʱ�����Ϣ
/// ����:
///    Buffer:ʱ�����Ϣ 32 Byte
///
/// Ver1.0 ------ 20040308 Auth:Lina
/*      32Byteʱ�����Ϣ��                   */
/*    1��ʱ��κţ�1Byte(0��63)  (����)      */
/*    2����ʼ���ڣ��ꡢ�¡��գ�3Byte(hex)    */
/*    3���������ڣ��ꡢ�¡��գ�3Bye(hex)     */
/*    4����ʼʱ�䣺ʱ���֣�2Byte(hex)	     */	
/*    5������ʱ�䣺ʱ���֣�2Byte(hex)        */
/*    6�����ڼ��ڼ�����Ϣ��1Byte		     */	
/* �ֱ������1(���λ)����7�Լ��ڼ���(���λ)*/
/*��λ��0ʱ��ʾ������Ч����1ʱ��ʾ������Ч   */
/*	  7������ 20Byte 0xff					 */
/* Output:									 */
/*  Return:    		                         */ 
/*    0    ---�ɹ�                           */
/*    -6   ---�ն���1500ms����Ӧ��           */
int _stdcall MakeBuf_SetMode4TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE4TIMEPHASEINFO;
	addr          = pDevice->nAddr;
	len           = 36;

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Buffer,32);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 200;
	pBuffer->nTimeOut1 = 1000;

	return RET_OK;
}


/// ���ܣ�����ģʽ�Ľڼ�����Ϣ
/// ������
///    No:�ڼ���������
///    Buffer:�ڼ�����Ϣ
///      1Byte �ڼ��ձ��(0---63)   
///      3Byte �ڼ�����Ϣ(�ꡢ�¡���)
/// Ver1.0 ------ 20040304 Auth:Lina
int _stdcall MakeBuf_SetMode4Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No, unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE4HOLIDAYINFO;
	addr          = pDevice->nAddr;
	len           = 4+4;

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);

	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Buffer,4);

	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 200;
	pBuffer->nTimeOut1 = 1000;

	return RET_OK;
}

/// ���ܣ���ȡģʽ���ڼ�����Ϣ
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_GetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETMODE3HOLIDAYINFO;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
} 

/// ���ܣ���ȡģʽ��ʱ�����Ϣ
/// ����: 
///   WeekInfo:������Ϣ
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_GetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETMODE3TIMEPHASEINFO;
	addr          = pDevice->nAddr;
	len           = 1;
	pBuffer->pBuffer[0] = WeekInfo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

#define  CMD_LOGINPUBLIC1PASSWORD	0x83
/// ���ܣ��´���½������Ϣ1����Ҫ������
/// ������
///     Password
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetLoginPublic1Password(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Password)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_LOGINPUBLIC1PASSWORD;
	addr          = pDevice->nAddr;
	len           = 14;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Password,10);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}