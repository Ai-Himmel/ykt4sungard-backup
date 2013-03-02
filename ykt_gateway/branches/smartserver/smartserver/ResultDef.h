#ifndef __RESULT_DEF_H__
#define __RESULT_DEF_H__

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////
//////���¶����������ķ���ֵ
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RESULT_VALUE_DEFINE_H__
#define __RESULT_VALUE_DEFINE_H__
#define RET_DATAVALUE_ERROR            -1       //-1:���ݳ��Ȳ���ֵ̫�����ڸ�ֵ,
#define RET_RECV_ERROR                 -2       //-2:�������ݴ�����û�д򿪼�ͨѶ��
#define RET_SEND_ERROR                 -3       //-3:�������ݴ�����û�д򿪼�ͨѶ��
#define RET_RECV_TIMEOUT               -4       //-4:�������ݳ�ʱ;
#define RET_ADDR_ERROR                 -5       //-5:���ص�ַ��ƥ��
#define RET_TERME_NOANSWER             -6       //-6:�ն��޷�Ӧ
#define RET_COMMONU_ERROR              -7       //-7:���ڴ�/�رմ�
#define RET_DATALENGTH_ERROR           -8       //-8�������ݳ��ȴ���
#define RET_DATACRC_ERROR              -9       //-9:����У���
#define RET_PARAMETER_ERROR1           -10      //-10:���������
#define RET_OK                          0       //0���ɹ�
#define RET_CARD_INVALID                1       //1:�Ƿ���
#define RET_CLOCK_ERROR                 2       //2:ʱ�Ӵ�
#define RET_MONEY_FORMAT_ERROR          3       //3:Ǯ����ʽ��
#define RET_DATA_FULL                   4       //4:������
#define RET_SEQNUM_ERROR                5       //5:��ˮ�Ŵ�
#define RET_PARAMETER_ERROR2            7       //7:���������
#define RET_COMMAND_ERROR               8       //8:�޴�����������޷���ʱʹ��
#define RET_REMARK_ERROR                9       //9:�ظ�����
#define RET_NO_RECORD                   10      //10:�޼�¼������
#define RET_AUTHNO_ERROR                11      //11:��Ȩ�Ų���
#define RET_REQU_SIGNIN                 13      //13:����ǩ��
#define RET_BLACKLIST_ERROR             14      //14:��������Ч�ڹ���
#define RET_CARD_MONEY_ENOUGH           15      //15:���ڽ���
#define RET_RECORD_NO_COLLECT           17      //17:���м�¼δ�ռ�
#define RET_CARD_DEGREE_ERROR           18      //18:��ʹ�ô�������
#define RET_CARD_EXPECT_ERROR           19      //19:��Ƭ�ѹ���Ч��
#define RET_CARD_MONEY_LARGE            20      //20:��Ƭ���̫��
#define RET_CARD_SEQOVER                22      //22:�ѽ��ʵĽ�����ˮ�ѱ�����(�޷�����)
#define RET_ACCREC_NOTUP                23      //23:���н��˼�¼δ�ϴ�
#define RET_NOT_AUTH                    24      //24:�豸δ��Ȩ�޷�ǩ��

#define NETWORK_PAR_NONE                0       //ֱ��
#define NETWORK_PAR_STAR                1       //����
#define NETWORK_PAR_BUS                 2       //����
#endif //__RESULT_VALUE_DEFINE_H__

//*------------------------------------------------------------------------------------
//*����: TSSmartProtocol
//*����: ͨѶЭ�������
//*------------------------------------------------------------------------------------
struct TSSmartProtocol
{
    unsigned char  PTHead[8];        //����ʼ������(ĿǰΪC2)
    unsigned short PTHeadLen;        //����ʼ������(ĿǰΪ1)
	unsigned char  PTTail[8];        //������������(ĿǰΪC3)
    unsigned short PTTailLen;        //������������(ĿǰΪ1)
	unsigned int   nLenOffset;       //���ݰ�����ƫ��(0..n)
	unsigned short nLenSize;         //�����ֽ���(ĿǰΪ1)
	unsigned int   nMinPKSize;       //����С�ĳ���(0.���޳�)
	unsigned int   nMaxPKSize;       //�����ĳ���(0.���޳�)
};

//*------------------------------------------------------------------------------------
//*����: TSDeviceInfo
//*����: �豸��Ϣ(��������ʱ��)
//*------------------------------------------------------------------------------------
struct TSDeviceInfo
{
	long nAuthID;                   //������Ȩ��
	int  nHardware;                 //Ӳ������
	char sVersion[24];              //Ӳ���汾��
	int  nAddr;                     //��������(0-255) 0��ʾ�㲥ͨѶ
	int  nNetPar;                   //����ṹ: ֱ��, ����, ����
	int  nLevel;					//�ն��豸�����ӵ����ݷ������ļ�����
	unsigned char sLevelArray[32];	//��������
	int  nTotalNo;                  //�ն˻�������
	int  nPort;                     //���͵�ǰͨѶ�˿� ���ߵ�ǰͨѶ��������
	int  nNoReponseTime;            //�ն��޷�Ӧ����
};

//*------------------------------------------------------------------------------------
//*����: TSCmdBuffer
//*����: ���ص����������
//*------------------------------------------------------------------------------------
struct TSCmdBuffer
{
	int nBufferSize;					//����Ļ������ĳ���
	unsigned char *pBuffer;             //����Ļ�����
	int nCmdSize;                       //���ص����������
	long  nTimeOut1;                    //���صĳ�ʱʱ��1
	long  nTimeOut2;                    //���صĳ�ʱʱ��2
};

//����: �õ�999Smart�豸Э��Ĺ���
long GetSmartProtocolRule(TSSmartProtocol *pSmartPT);

///////////////////////////////////////////////////////////////////////////////////////////
/// ��    ��: -- �յ�����һ���ֺ�������У��, ����Ƿ�Ϸ���
/// ��    ��: 
///        pBuffer     --  ҪУ������ݿ�
///        nBufferSize --  ���ݿ鳤��
///
/// �� �� ֵ: 
///        ������ֵ����
///
/// ˵    ��:
///        ֻ����Э�����ȷ��,��������ݳ���, CRC�ȴ���
///////////////////////////////////////////////////////////////////////////////////////////
int VerifyBufferValid(unsigned char *pBuffer, int nBufferSize);

///////////////////////////////////////////////////////////////////////////////////////////
/// ���º�����ɴ������͵�Ӳ�����������ݰ��Ĺ���. ��������Ӳ���豸����������Ľṹ���ͣ�
/// �û�ֻ�贫����صĲ�����ɹ�������ص����ݰ���
/// 
/// ��������: 
///        pDevice --  ���豸��Ϣ������ṹ��Ϣ
///        pBuffer --  Ҫ���ص��������ݰ�
///
/// ��������:
///        ���豸��̬���ĵ�
///////////////////////////////////////////////////////////////////////////////////////////

//����: �����ն��豸ID�ţ����п���ֻ�����һ���ն��豸��
int MakeBufWriteID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//��ȡ�ն��豸ID�ţ����п���ֻ�����һ���ն��豸��
int MakeBufReadID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//����ͨ��ID������ֽڲ�ѯ�ն��豸ID��
int MakeBufSearchId(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//ͨ���ն��豸ID�Ÿ��ն��豸���û���
int MakeBufWriteJh(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id);

//���ն��豸��������
int MakeBufReadType(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//���ն��豸�������ʱ�䣨�ꡢ�¡��ա�ʱ��
int MakeBufReadDate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//����ͨ�Ų�����
int MakeBufChangeBaudRate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int baudrate);

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------ר����������ڼ�ʱ�����շѻ���-----------------------------------------------------

//������Ȩ��
int MakeBufSetCommision(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *newcommision);

//�´�ϵͳ������
int MakeBufDownParam(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char* Buffer);

//�û��ϴ�ϵͳ������(����Ȩ��)
int MakeBufUserUpParam(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char* Buffer);

//�ϴ�ϵͳ������(������Ȩ�ţ���˾�ڲ�ʹ��)
int MakeBufUpParam(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//�´�������
int MakeBufDownBlackCard (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision, ,int *num unsigned char *Buffer);

//ɾ��������
int MakeBufDownDelBlack (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int *num unsigned char *Buffer,unsigned char *buffer);

//ɾ�����к�����
int MakeBufDownDelBAll (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision);

//�ж�һ�ſ��Ƿ��Ǻ�����
int MakeBufIsBlack(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *blackno);

//�㲥��ʽ�´��������汾
int MakeBufBroadcastBlack(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned *blackno,unsigned char* Buffer);

//�´��������汾
int MakeBufDownBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Commision, unsigned char* Buffer);

//�ϴ��������汾
int MakeBufUpBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//��һ����ǰ��¼
int MakeBufUpRecordOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//��һ����¼����
int MakeBufEndUpRecordOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *serialno);

//�ϴ�һ����ʷ��¼
int MakeBufUpHisBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *serialno,  unsigned char *buffer);

//�´�һ����ʷ��¼(�����ڲ�ʹ��)
int	MakeBufDownHisBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,  unsigned char *serialno, unsigned char *buffer);

//���Flash������ʼ��)
int MakeBufEmptyFlash(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//�´�ϵͳԱ���루3�ֽ�6λBCD��
int MakeBufDownSysPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Commision, unsigned char *buffer);

//�����ϴ�FLASH��Ϣ��
int MakeBufUpFlash(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int blocknum,unsigned char *buffer);

//�ϴ��ն˻�״̬
int MakeBufUpStatus(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//�´�����ʱ��
int MakeBufDownClock (TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char* Buffer);

//�ϴ�ʱ��
int MakeBufUpClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//��Ȩ��Ϣ�㷨
void MakeBufSmartEncrypt(unsigned char E_number,unsigned char *ID, unsigned char *Plain);

//������Կ�´�
int MakeBufDownAuthinfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *Plain,unsigned char E_number);


//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------�շ���Posר������-----------------------------------------------------

//�´�ʱ���
int MakeBufDownSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int num,int daycount,unsigned char* Buffer);

//�ϴ�ʱ���
int MakeBufUpSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *num,unsigned char *Buffer);

//�´���ݼ����
int MakeBufDownQuickBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,int num,unsigned char *Buffer);

//�ϴ���ݱ��
int MakeBufUpQuickBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *num,unsigned char *Buffer);

//�´����ѱ��
int MakeBufDownXFBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char flag,int num,unsigned char *Buffer);

//ɾ�����ѱ��
int MakeBufDownDelXFBH(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *id,int *num,unsigned char* Buffer);

//�´����ѱ�Ű汾
int MakeBufDownXFBHVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//�ϴ����ѱ�Ű汾
int MakeBufUpXFBHVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//�´��������������޶�
int MakeBufDownLimitPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//�ϴ��������������޶�
int MakeBufUpLimitPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//����ͳ�ƺ���������
int MakeBufCaculateBlack(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* commision);

//�ϴ�����������
int MakeBufUpBlackNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,int *num);

//�´���������Ч��
int MakeBufDownBlackExpire(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *date);

//�ϴ���������Ч��
int MakeBufUpBlackExpire(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,unsigned char *date);

//��������
int MakeBufCount(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision);

//�ϴ�һ�����ʼ�¼
int MakeBufUpCountOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,unsigned char *data);

//ȷ���ϴ�һ�����ʼ�¼
int MakeBufEndUpCountOne(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,unsigned char *ser);

//����ˮ���ϴ�һ�����ʼ�¼
int MakeBufUpCountBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision, unsigned char *ser,unsigned char *data);

//����ˮ�´�һ�����ʼ�¼(�����ڲ�ʹ��)
int MakeBufDownCountBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Id,unsigned char *data);

//�ϴ��κν��׼�¼(�����ڲ�ʹ��)
int MakeBufUpBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *serialno,   unsigned char *buffer);

//�´��κν��׼�¼(�����ڲ�ʹ��)
int MakeBufDownBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *serialno,unsigned char *buffer);

//����ǩ��ȷ��
int MakeBufStartUse(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int flag);

//�´���Ƭ��λ���루2�ֽ�HEX����λ��ǰ,V10ר�ã�
int MakeBufDownCompanyPWD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int password);

//�ϴ�V10��Ǯ������(v10ר��)  
int MakeBufUpSectorNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int *sectornum);

//�´�V10��Ǯ������(v10ר��) 
int MakeBufDownSectorNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,int sectornum);

//��������ˮ�Ÿ��˽���(������)
int MakeBufDownCountAgain(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *ser);

//����ˮ�ϴ����˽��ʼ�¼(������)
int MakeBufUpCountAgain(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *ser,unsigned char *data);

//�ϴ���ʱ����ʱ���(������)
int MakeBufUpCountTime(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *buffer);

//�´���ʱ����ʱ���(������)
int MakeBufDownCountTime(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *buffer);

//��¼��CRC���㲢�´�(11��11����)
int MakeBufDownHisRecord(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *buffer);

//�㲥��ʽ�´���ɾ���������汾
int MakeBufDownOrDelBlackAndVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *blackno, unsigned char* version, bool flag);

//�������ֹ����
int MakeBufBuZhuSwitch(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, BOOL _switch);


//�жϲ�������״̬
int MakeBufIsBuZhuSwitch(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *nswitch);


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//------------------------------------��ʱPosר������
 
//�´�������(ģʽ2,3)
int MakeBufDownWhiteCard(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int *num,unsigned char *Buffer);

//ɾ��������(ģʽ2,3)
int MakeBufDownDelWhite(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * commision,int *num unsigned char *Buffer,unsigned char *buffer);

//ɾ�����а�����(ģʽ2,3)
int MakeBufDownDelWAll(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//�ж�һ�ſ��Ƿ��ǰ�����(ģʽ2,3)
int MakeBufIsWhite(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *blackno);

//�㲥��ʽ�´�һ��������+�汾(ģʽ2,3)
int MakeBufBroadcastWhite(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned *blackno,unsigned char* Buffer);

//�´��������汾(ģʽ2,3)
int MakeBufDownWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char* Buffer);

//�ϴ��������汾(ģʽ2,3)
int MakeBufUpWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char* Buffer);

//�´���ʱ��ʱ���(ģʽ3)
int MakeBufDownJSBSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int day,int num, unsigned char* Buffer);

//�ϴ���ʱ��ʱ���(ģʽ3)
int MakeBufUpJSBSJD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int date,unsigned char *Buffer);

//�´���ʱ���ڼ��� (ģʽ3)
int MakeBufDownHoliday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int num, unsigned char* Buffer);

//�ϴ���ʱ���ڼ���(ģʽ3)
int MakeBufUpHoliday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);


//�´�ģʽ4�汾��
int MakeBufDownMode4Ver(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//�ϴ�ģʽ4�汾��
int MakeBufUpMode4Ver(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//�´�ģʽ4������һ��
int MakeBufDownMode4OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *Buffer);

//�ϴ�ģʽ4������һ��
int MakeBufUpMode4OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//�´�ģʽ4�ڼ���
int MakeBufDownMode4Holiday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *Buffer);

//�ϴ�ģʽ�Ľڼ���
int MakeBufUpMode4Holiday(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//�´�ģʽ4ʱ���
int MakeBufDownMode4TimeSegment(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *Buffer);

//�ϴ�ģʽ4ʱ���
int MakeBufUpMode4TimeSegment(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//�´�ID������4�ֽ�M1�����к�һ��(ģʽ1,2,3)
int MakeBufIDDownList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//ɾ��һ��ID������4�ֽ�M1�����к�(ģʽ1,2,3)
int MakeBufIDDelList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//�ж�һ��ID������4�ֽ�M1�����к�(ģʽ1,2,3)
int MakeBufIDJudgeList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//�㲥�´�ID����һ����4�ֽ�M1�����к�(ģʽ1,2,3)
int MakeBufIDBoardcastDownList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//�㲥ɾ��ID����һ����4�ֽ�M1�����к�(ģʽ1,2,3)
int MakeBufIDBoardcastDelList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//������Ӧͷ
int MakeBufSearchReaderInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//�ϴ���Ӧͷ��Ϣ
int MakeBufUpReaderInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//���ø�Ӧͷ����
int MakeBufSetReaderMacNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,unsigned char *Buffer);

//����
int MakeBufAntiFire(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//����
int MakeBufAntiThief(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//�ָ���������
int MakeBufResumeNormal(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//�´�ģʽ5������һ��
int MakeBufDownMode5OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//ɾ��ģʽ5������һ��
int MakeBufDelMode5OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//��ѯģʽ5������һ��
int MakeBufQueryMode5OneWhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//���ģʽ5���а�����
int MakeBufDelAllMode5WhiteList(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//�´�ģʽ5��������豸��һ��
int MakeBufDownMode5OneRoomNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);

//ɾ��ģʽ5�����һ��
int MakeBufDelMode5OneRoomNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char *buffer);


// ���ģʽ5���з���ź��豸��
int MakeBufDelAllMode5RoomNumAndEquipNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision);

//��ѯģʽ5һ���豸��״̬
int MakeBufQueryMode5OneEquipStatus(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, unsigned char * buffer);

// �ϴ���ǰ���Կ�׵�����
int MakeBufUpMode5LoanKeyAmount(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision, int *num);

////////////////////////////////////////////////////////////////////////
///////////////////��ʧ��ר������///////////////////////////////////////

//���ͱȶԽ�� 
int MakeBufConfirmLost(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char * Commision,unsigned char *serialno);

////////////////////////////////////////////////////////////////////////
///////////////////��Ʊ��ר������///////////////////////////////////////

//����Ʊ��
int MakeBufSetTicket(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *commision,int ticketnum);

//��ȡƱ��
int MakeBufGetTicket(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int *ticketnum);

////////////////////////////////////////////////////////////////////////
///////////////////�ϻ�������ר������///////////////////////////////////////

//������Ϣ
int MakeBufReadCard(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *CardNum,unsigned char *CardNum1,
	unsigned char *Password, unsigned char *CardID,unsigned char *Name,int *Money);

//�ۿ����
int MakeBufDecCard(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *CardNum,int DecMoney);

//�Ƚϸ�������
int MakeBufCheckPassword(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Password,unsigned char *CardID,unsigned char *PWD);

//��ʾ�ַ���
int MakeBufDisplay(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *XSbuffer,int DelayTime);

//�û���ʾ���
int MakeBufDisplayMoney(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int Money);

//������Ϣ��������ʾˢ��
int MakeBufReadCardBeep(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, 
				      unsigned char *CardNum,
					  unsigned char *CardNum1,
					  unsigned char *Password,
					  unsigned char *CardID,
					  unsigned char *Name,
					  int *Money);

//��������ϸ��Ϣ
int MakeBufReadPersonalInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Name,unsigned char *buffer);

//������ϸ��Ϣ
int MakeBufReadCardInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *CardNum,unsigned char *CardNum1,
	unsigned char *CardID,int *CardType,unsigned char *ExpireDay);

//����������Ϣ(�����֤��)
int MakeBufReadLiberyNum(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *ThirdInfo);

//��ʼ�����ݷ�����
int MakeBufIni_Fwq(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *BautRateBuffer, unsigned char port);

//��������������
int MakeBufSearch_FwqPort(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char port);

//�ϴ����ն˲���
int MakeBufFwq_State(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//ͨ�����ݷ�������ѯ�˿ڼ�¼���(������ʽ�ռ�¼)
 int MakeBufQueryFwqPortStat(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *Buffer);

//���߸��˿ڵ�ǰ��¼(������ʽ�ռ�¼)
int MakeBufUpByFwqZD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//���߶˿ڼ�¼����(����,������ʽ�ռ�¼)
int MakeBufEndUpByFwqZD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//����˿���Ȩ��
int MakeBufResetCommision(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *buffer);

//�´�����������������
int MakeBufDownBZ(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//�´����������汾��
int MakeBufDownFWQBZVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//�ϴ����������汾��
int MakeBufUpFWQBZVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//��ȡһ�ʲ�������
int MakeBufUpBZMD(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);

//����ˮ�ϴ�������¼
int MakeBufUpBZBySerial(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, BYTE *buffer);
