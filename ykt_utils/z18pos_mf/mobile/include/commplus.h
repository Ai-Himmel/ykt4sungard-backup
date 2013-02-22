
  /* CommPlus(TM) function heading files */

  #define _CP_BIOS_INT  0xe8

  #define _GET_MODE     0x81
  #define _SET_MODE     0x82
  #define _GET_SNO      0x83
  #define _SET_SNO      0x84

  #define _ENA_RX       0x85
  #define _DIS_RX       0x86

  #define _PUT_PAK      0x87
  #define _GET_PAK      0x88

  #define _PUT_AUX      0x89
  #define _PRE_GET_AUX  0x8a
  #define _GET_AUX      0x8b
  #define _IMD_GET_AUX  0x8c
  #define _SELECT_PORT  0x8d

  #define _BlkGetAux    0x8e;
  #define _BlkPutAux    0x8f;
  #define _GetNinthBit  0x90;
  #define _PutNinthBit  0x91;


  #define _CP_OS_INT    0x0e7

  #define _SET_WAIT_MD  0x80
  #define _OPEN_EXF     0x81
  #define _READ_EXF     0x82
  #define _WRT_EXF      0x83
  #define _CLOS_EXF     0x84

  #define _COMT_REQ     0x85
  #define _GET_REQ      0x86
  #define _REP_REQ      0x87

  #define _TX_FILE      0x88
  #define _RX_FILE      0x89
  #define _EXF_SERV     0x8a
  #define _EXF_PUT      0x8b
  #define _EXF_GET      0x8c


  #define _WRT_REQ      1
  #define _READ_REQ     2
  #define _LST_REQ      3
  #define _DEL_REQ      4
  #define _SNO_REQ      5
  #define _SPC_REQ      6
  #define _MDIR_REQ     7  (�� HT2800����Ч��
  #define _RDIR_REQ     8  (�� HT2800����Ч��
  #define _LSTN_REQ     9  (�� HT2800����Ч��
  #define _STM_REQ      10 (�� HT2800����Ч��

  #define _REJECTED      -2
  #define _READ         0
  #define _WRITE        1

  #define _PAK_MODE     2
  #define _AUX_MODE     3

  #define _par_EVEN     0x80
  #define _par_ODD      0
  #define _mod_STD      0
  #define _mod_7D1P     0x10
  #define _mod_8D1P     0x30
  #define _mod_7D       0x40

  #define _NOT_SLNT     1
  #define _SLNT         0
  #define _IN_CHI       0
  #define _IN_ENG       2

  typedef struct {
    unsigned char ReqDescLen;
    char ReqDescStr[257];
  } REQ_DESC;

  typedef struct {
    unsigned char ShowInfor;
    unsigned char Language;
    char far *Buffer;
    unsigned int BufferSize;
    char far *Localf;
    char far *Remotef;
    unsigned int ValidSNO;
  } FCOM_PARA;

  #ifndef __COMMPLUS

  extern far int  pascal InstallComPls(unsigned char CommPort);
  /*
   1    ��װͨ���ں�
  */

  extern far int  pascal UninstComPls(void);
  /*
   2    ж��ͨ���ں�
  */

  extern int  ComPlsInstalled(void);
  /*
   3 ����ͨѶ�ں��Ƿ�װ
       ������     ��
       ���ز����� ��
       ����ֵ��   0         δ��װ
                  ��0    �Ѱ�װ
  */

  extern void GetCommMode(unsigned char far *WorkMode,
                          unsigned char far *CommPort,
	                  unsigned int far *BaudRate);
  /*
   4 ȡ�õ�ǰͨ�ſڡ�����ģʽ�Ͳ����ʡ�
��   �������� 
              WorkMode
              CommPort
	       BaudRate
     ���ز����� 
               WorkMode     ����ģʽ
                 _PAK_MODE  ���ݰ�����/���շ�ʽ
                 _AUX_MODE  �ַ�������/���շ�ʽ
               CommPort     ��ǰͨ�ſ�
                 0          ���пڣ���COM1��
                 1          ���пڣ���COM2��
               BaudRate     ��ǰ������
                 150        150bps 
                 300        300bps
                 600        600bps
                 1200       1200bps
                 2400       2400bps
       		 4800       4800bps
                 9600       9600bps
                 19200      19200bps
                 38400      38400bps
                 57600      57600bps
                 0fff0h     115200bps  ���� HT2800����Ч��
     ����ֵ��        �� 
  */

  extern int  SetCommMode(unsigned char WorkMode,
                          unsigned char CommPort,
                          unsigned int BaudRate);
  /*  
   5 ����ͨ�ſڡ�����ģʽ�Ͳ����ʡ�
  �� ����������
        WorkMode    ����ģʽ
          _PAK_MODE                         2     ���ݰ�����/���շ�ʽ
          _AUX_MODE                         3     �ַ�������/���շ�ʽ 8N1
          _AUX_MODE+_mod_8D1P+_par_ODD      51    �ַ�������/���շ�ʽ 8O1
          _AUX_MODE+_mod_8D1P+_par_EVEN     179   �ַ�������/���շ�ʽ 8E1
          _AUX_MODE+_mod_7D1P+_par_ODD      19    �ַ�������/���շ�ʽ 7O1
          _AUX_MODE+_mod_7D1P+_par_EVEN     147   �ַ�������/���շ�ʽ 7E1
          _AUX_MODE+_mod+7D                 67    �ַ�������/���շ�ʽ 7N1
          _AUX_MODE+_mod_8D1P+_mod_7D       115   �ַ�������/���շ�ʽ 9N1

          ��9N1 ��������HT1820���� HT2800����Ч ����

        CommPort     ��ǰͨ�ſ�
          0          ���пڣ���COM1)
          1          ���пڣ���COM2)
        BaudRate     ��ǰ������
          150        150bps
          300        300bps
          600        600bps
          1200       1200bps
          2400       2400bps
          4800       4800bps
          9600       9600bps
          19200      19200bps
          38400      38400bps
          57600      57600bps
          0fff0h     115200bps   ���� HT2800����Ч��
    ���ز�����
               ��
    ����ֵ���� 
	       0��          ���óɹ�
               4��          �Ƿ�ģʽ
               5��          �Ƿ�������
  */

  extern unsigned int GetSerialNo(void);
  /*   
   6 ȡ�û���ϵ�кš�
  �� ������     
               �ޡ�
     ���ز���: 
               ��
     ����ֵ��
	  �� ������ϵ�к�
  */ 

  extern void SetSerialNo(unsigned int SerialNo);
  /*
   7 ���û���ϵ�кš�
  �� ����������
  ��           SerialNo��  ����ϵ�к�
                 ����ϵ�кŵķ�Χ�� 0 �� 65535 ֮��
     ���ز���:
               ��
     ����ֵ��
               ��
  */ 

  extern void EnableRx(unsigned int RxSerialNo);
  /*
   8 �����пڽ��վ�ָ��ϵ�кŵĻ��������������ݡ�
  �� ����������
  ��           SerialNo��  ����ϵ�к�
               ����ϵ�кŵķ�Χ�� 0 �� 65535 ֮��
     ���ز���:
               ��
     ����ֵ��
               ��
    ��ע�͡�  ����ϵ�к�Ϊ�������������κλ��������������ݡ�
              �ַ���������ʽ�»���ϵ�к������塣
              ���˵��ý�������ݰ����ַ����������ڵ��������ݡ�
  */ 

  extern void DisableRx(void);
  /*   
   9 ��ֹ���пڽ����κ����ݡ�
  �� ������     
               �ޡ�
     ���ز���: 
               ��
     ����ֵ��
               ��
  */ 

  extern int  RxPackage(unsigned char far *Buffer);
  /* 
   10 ���ݰ�����/���շ�ʽ�½�������
  ��  ������     
	       Buffer       ���ݰ�������ָ�롡
      ���ز���: 
               ��
      ����ֵ��
          ��   0            û�н��յ��κ����ݰ�
               ���� 0       ���ݰ����ȣ��ֽڣ�
               С�� 0       ���յ��������ݰ����������෴����
  */ 

  extern int  TxPackage(unsigned char far *Buffer, unsigned int BufLength);
  /* 
   11 ���ݰ�����/���շ�ʽ�·������ݰ���
  ��  ������     
               Buffer       ���ݰ�������ָ�롡
	       BufLength    ���ݰ�����
      ���ز���: 
               ��
      ����ֵ��
          ��   0            ���ͳɹ�
               1            ͨ�ų�ʱ
               2            ��·����
               3            ���ݰ�����
               4            �Ƿ�����ģʽ����ǰ����ģʽ�������ݰ���ʽ��
      ��ע�͡�  ��������ݰ�����Ϊ 512 ���ֽڡ�
  */ 

  extern int  PutAuxByte(unsigned char AuxByte);
  /* 
   12 �ַ�������/���շ�ʽ�·����ַ���
    ��������
               AuxByte     �����͵��ַ�
      ���ز���: 
               ��
      ����ֵ��
          ��   0           ���ͳɹ�
               ��0         ��ǰ������ʽ�����ַ�������/���շ�ʽ
  */ 

  extern int  AuxByteExist(unsigned char far *AuxByte,
                           unsigned char far *Status);
  /*
   13 �ַ�������/���շ�ʽ��ȡ���ַ�����״̬��
  ��  ������     
               AuxByte      �����ַ�
               Status       ����״̬
      ���ز���: 
    	       AuxByte      �����ַ�
               Status       ����״̬
      ����ֵ��
          ��   0            δ���յ��κ��ַ�
               ��0          �ѽ��յ��ַ�
     ��ע�͡�  ���ַ���δ���ַ����������ж�ȡ������
  */ 

  extern int  GetAuxByte(unsigned char far *AuxByte,
	                 unsigned char far *Status);
  /*
   14 �ַ�������/���շ�ʽ�¶�ȡ�ַ���
  ��  ������     
               AuxByte      �����ַ�
               Status       ����״̬
      ���ز���:
	       AuxByte      �����ַ�
	       Status       ����״̬
      ����ֵ��
	   ��  0           ���յ��ַ�
	       ��0         ��ǰ������ʽ�����ַ�������/���շ�ʽ
		           ����ESC(ON)���ж��˳�
   ��ע�͡�  ���ַ��Ѵ��ַ����������ж�ȡ������
  */

  extern int  ExistAuxBGot(unsigned char far *AuxByte,
	      	           unsigned char far *Status);
  /*
   15 ȡ���ַ�����״̬����ȡ�ѽ��յ����ַ�
  ��  ������
	       AuxByte      �����ַ�
	       Status       ����״̬
      ���ز���:
	       AuxByte      �����ַ�
	       Status       ����״̬
      ����ֵ��
	   ��  0           δ���յ��κ��ַ�
	       ��0         �ѽ��յ��ַ�
     ��ע�͡�  ���ַ��Ѵ��ַ����������ж�ȡ������
  */

  extern unsigned int GetAuxBlock(char _far *buffer, unsigned int buffsize,
             			  unsigned int waitsec);
  /*
   16 
  */

  extern unsigned int PutAuxBlock(char _far *buffer, unsigned int buffsize);
  /*
   17 
  */

  extern unsigned char GetAuxNinthBit(void);
  /*
   18 
     ��ע�͡�  �˺�����HT-2800����Ч��
  */

  extern void PutAuxNinthBit(unsigned char NinthBit);
  /*
   19 
     ��ע�͡�  �˺�����HT-2800����Ч��
  */

  extern void DisableTimeOut(void);
  /*
   20 �ļ�ͨ�Ź����йرճ�ʱ��⿪�ء�
  ��  ������
	       ��
      ���ز���:
	       ��
      ����ֵ��
	       ��
     ��ע�͡����򿪳�ʱ��⿪��ʱ, һ�����ݰ������������ܴ��������ʮ���
             ��δ����ļ�ͨ���Զ��жϲ����س�ʱ����
   �������������ļ�ͨ�Ź��������ޱ���ĳ�ʱ�����󣬽���򿪳�ʱ��⿪���Ա�
 ��  ��������������·���ϵ��µ����ȡ�
  */ 

  extern void EnableTimeOut(void);
  /*
   21 �ļ�ͨ�Ź����д򿪳�ʱ��⿪�ء�
  ��  ������     
               ��
      ���ز���: 
               ��
      ����ֵ��
	       ��
     ��ע�͡����򿪳�ʱ��⿪��ʱ, һ�����ݰ������������ܴ��������ʮ���
             ��δ����ļ�ͨ���Զ��жϲ����س�ʱ����
   �������������ļ�ͨ�Ź��������ޱ���ĳ�ʱ�����󣬽���򿪳�ʱ��⿪���Ա�
  �� ��������������·���ϵ��µ����ȡ�
  */ 

  extern int  ExfOpen(unsigned char OpenMode, unsigned int ValidSNo,
                      char far *FileName,
                      unsigned char far *ExfAttr,
                      unsigned long far *ExfSize,
                      unsigned long far *ExfStamp,
                      unsigned int far *theOthSNo);
  /*
   22 ���ݰ�ͨ�ŷ�ʽ�°���/д������ⲿ�ļ���
  ��  ��������
               OpenMode      �򿪷�ʽ
                             _READ  ���ⲿ�ļ�
                             _WRITE д�ⲿ�ļ�
               ValidSNo      �Է�����ϵ�к�
               FileName      �ļ����ַ���
               ExfAttr       �ļ�����
               ExfSize       �ļ���С
               ExfStamp      �ļ�ʱ��(��MS-DOS�ļ�ʱ���ʽ���)
               theOthSNo     �Է�ʵ��ϵ�к�
     ��ע�͡�����������ⲿ�ļ�ʱ
 ���������� ��  �������Ϊ��
 ������������   �Է�����ϵ�кš�����ָ��ͨ�ŶԷ���������еĻ���ϵ�кţ�
 ������������������������������ Ϊ��ʱ��ʾ�������������ͨ�š�
 �������������� �ļ����ַ���    ���ַ�*��ʼ���ַ���������ȡ�����ļ�������
   ���������������������������� �Է��������ļ����������ָ���ִ���ͬ�����֡�
             ������ֵΪ��
                 �ļ����ַ��������Է��������ļ���
                 �ļ�����        �Է��������ļ�����
                 �ļ�ʱ��        �Է��������ļ�ʱ��
                 �ļ���С        �Է��������ļ���С
                 �Է�ʵ��ϵ�к�  �Է�ʵ�ʾ��е�ϵ�к�
                ��ע�⡿������Է�δ�����ļ����ԡ�ʱ����С���򷵻صĿ��������ֵ
            ��д������ⲿ�ļ�ʱ ��
�����������������������Ϊ��
��������������   �Է�����ϵ�кš�����ָ��ͨ�ŶԷ���������еĻ���ϵ�к�
�������������������������������� Ϊ��ʱ��ʾ�������������ͨ�š�
���������������� �ļ����ַ���    ָ���ⲿ�ļ����õ��ļ���, �Է�����ָ����ͬ���ļ�����ָ��*�ַ���
                 �ļ�����        �ļ�����
                 �ļ�ʱ��        �ļ�ʱ��
                 �ļ���С        �ļ���С
            ����ֵΪ��
                 �Է�ʵ��ϵ�к�  �Է�ʵ�ʾ��е�ϵ�к�

    ����ֵ��  0   �򿪳ɹ�
              1   ͨ�ų�ʱ
              2   ��·����
              6   ͨ�ű�ȡ��
              7   �ļ�����ƥ��
              8   �Ƿ���ʽ
              10  �ⲿ�ļ��Ѿ�����
              11  �Ƿ��ļ���
  */

  extern int  ExfRead(char far *RdBuff, unsigned int RdCount,
                      unsigned int far *ActRdCnt);
  /*
   23 ���ݰ�ͨ�ŷ�ʽ�¶��ⲿ�ļ���
 ��   ��������
              RdBuff       ���뻺������ַ
��  ��������  RdCount      ���볤�ȣ��ֽڣ�
              ActRdCnt     ʵ�ʶ��볤�ȣ��ֽڣ�
      ���ز�����
              ActRdCnt     ʵ�ʶ��볤�ȣ��ֽڣ�
      ����ֵ��
              0            �ɹ�
              ��0          ʧ��
              �������
                   1   ͨ�ų�ʱ
                   2   ��·����
                   6   ͨ�ű�ȡ��
                   8   �Ƿ���ʽ���ⲿ�ļ�δ������ʽ�򿪣�
     ��ע�͡�   ��ʵ�ʶ��볤��С��ָ�����볤��ʱ����ʾ�ⲿ�ļ��ѽ�����
  */

  extern int  ExfWrite(char far *WrtBuff, unsigned int WrtCount,
                       unsigned int far *ActWrtCnt);
  /*
   24 ���ݰ�ͨ�ŷ�ʽ��д�ⲿ�ļ���
  ��  ����������
               WrtBuff       д����������ַ
 �� ��������   WrtCount      д�����ȣ��ֽڣ�
               ActWrtCnt     ʵ��д�����ȣ��ֽڣ�
      ���ز�����
               ActWrtCnt     ʵ��д�����ȣ��ֽڣ�
      ����ֵ��
               0             �ɹ�
               ��0           ʧ��
               �������
                   1   ͨ�ų�ʱ
                   2   ��·����
                   6   ͨ�ű�ȡ��
                   8   �Ƿ���ʽ���ⲿ�ļ�δ��д��ʽ�򿪣�
                   9   �ļ����ضϣ�ͨ�ŶԷ�δ��������д���ֽڱ�ر����ļ���
  */

  extern void ExfClose(void);
  /*
   25 ���ݰ�ͨ�ŷ�ʽ�¹ر��ⲿ�ļ���
  ��  ����������
               ��
      ���ز�����
	       ��
      ����ֵ��
	       ��
  */

  extern int  SendClientReq(unsigned char ReqType, unsigned int ServerID,
	            	    char *DescString, unsigned int *AcceptComment);
  /* 
   26 ��ͨ�ŷ������ύ�ͻ�����(Ҫ��ͨ�ŶԷ�����ͨ�ŷ�����)��
  ��  ������   ReqType    �������ͣ�0..255��'a'..'z'��'A'..'Z' ���⣩
			    _DEL_REQ  ɾ���ļ�����
			    _SNO_REQ  ��ȡϵ�к�����
 ��   ������   ServerID   ������ϵ�кţ�Ϊ����������κ����з���������Ļ���ͨ�ţ�
	       DescString ����������
			    _DEL_REQ ʱ�����ļ���
	       AcceptComment ���ܱ�ע
      ���ز�����
               AcceptComment ���ܱ�ע
			   _SNO_REQ ������ʱ����ȡ�õ�ϵ�к�
      ����ֵ:  0   ���󱻽���
	       1   ͨ�ų�ʱ
	       2   ��·����
	       ����ֵ ���󱻾ܾ�ʱ��ԭ����
  �� ��ע�͡�������������Ϊ���ⳤ�Ȳ�����255���ֽڵ��ַ���
  */

  extern int  ClientReqExist(unsigned char far *ReqType,
 		             REQ_DESC far *ReqDesc);
  /* 
   27  CommPlus ���� 
  */

  extern int  AcceptReq();
  /*
   28 CommPlus ���� 
  */

  extern int  RejectReq(unsigned int RejectReason);
  /*
   29 CommPlus ���� 
  */

  extern int  SendFileOut(char far *LocalfName, unsigned char ShowInfor,
                          unsigned char Language, unsigned int ReaderSNO,
                          char far *WrtBuff, unsigned int BuffSize);
  /*
   30 �����ļ�(Ҫ��ͨ�ŶԷ����н����ļ�)��
      ����������
               LocalfName   ���ط����ļ���
               ShowInfor    ��ʾ��Ϣѡ��
                            _NOT_SLNT   ��ʾͨ����Ϣ
                            _SLNT       ����ʾͨ����Ϣ
               Language     ��ʾ��Ϣ������(Ӣ,��)ѡ��
                            _IN_CHI     ʹ������
                            _IN_ENG     ʹ��Ӣ��
               ReaderSNO    ͨ�ŶԷ��Ļ���ϵ�к�
               Wrtbuff      ���ͻ�������ַ
               Buffsize     ����������
      ���ز�����
               ��
      ����ֵ��   
               0             �ɹ�
               ��0           ʧ�ܴ�����
                             ����������������б�
  */

  extern int  CopyFileIn(char far *LocalfName, char far *RemotefName,
                         unsigned char ShowInfor,
                         unsigned char Language, unsigned int WriterSNO,
                         char far *RdBuff, unsigned int BuffSize);
  /*
   31 �����ļ�(Ҫ��ͨ�ŶԷ����з����ļ�)��
      ����������
               LocalfName   �����ļ��ı���(Ŀ��)��
               RemotefName  �����ļ���Զ��(Դ)��
               ShowInfor    ��ʾ��Ϣѡ��
                            _NOT_SLNT   ��ʾͨ����Ϣ
                            _SLNT       ����ʾͨ����Ϣ
               Language     ��ʾ��Ϣ������(Ӣ,��)ѡ��
                            _IN_CHI     ʹ������
                            _IN_ENG     ʹ��Ӣ��
               WriterSNO    ͨ�ŶԷ��Ļ���ϵ�к�
               Rdbuff       ���ջ�������ַ 
               Buffsize     ����������
      ���ز�����
               ��
      ����ֵ��   
               0             �ɹ�
               ��0           ʧ�ܴ�����
                             ����������������б�
  */

  extern void fServer(unsigned char CommPort, unsigned int BaudRate,
                      unsigned char Silent, unsigned char LangSelect,
                      unsigned int BufferSize, char far *Buffer);
  /*
   32 ͨ�ŷ�������
      ����:
               CommPort     ���пں�
               BaudRate     ������
               Silent       ��ʾ��Ϣѡ��
                            _NOT_SLNT   ��ʾͨ����Ϣ
                            _SLNT       ����ʾͨ����Ϣ
               LangSelect   ��ʾ��Ϣ������(Ӣ,��)ѡ��
                            _IN_CHI     ʹ������
                            _IN_ENG     ʹ��Ӣ��?
               buffer       ͨ�Ż�������ַ
               BufferSize   ����������
      ���ز�����
               ��
      ����ֵ��   
               ��
  */

  extern int  ExfPut(char far *LocalfName, char far *RemotefName,
                     unsigned char ShowInfor,
                     unsigned char Language,
                     unsigned int ReaderSNO,
                     char far *WrtBuff, unsigned int BuffSize);
  /*
   33 ����ͨ�ŷ����������ļ�(Ҫ��ͨ�ŶԷ�����ͨ�ŷ�����)��
      ����������
               LocalfName   �ļ��ı���(Դ)��
               RemotefName  �ļ���Զ��(Ŀ��)��
               ShowInfor    ��ʾ��Ϣѡ��
                            _NOT_SLNT   ��ʾͨ����Ϣ
                            _SLNT       ����ʾͨ����Ϣ
               Language     ��ʾ��Ϣ������(Ӣ,��)ѡ��
                            _IN_CHI     ʹ������
                            _IN_ENG     ʹ��Ӣ��
               ReaderSNO    ͨ�ŶԷ��Ļ���ϵ�к�
               Wrtbuff      ���ͻ�������ַ 
               Buffsize     ����������
      ���ز�����
               ��
      ����ֵ��   
               0             �ɹ�
               ��0           ʧ��
               ��0           ʧ�ܴ�����
                             ����������������б�
  */

  extern int  ExfGet(char far *LocalfName, char far *RemotefName,
	             unsigned char ShowInfor,
		     unsigned char Language,
		     unsigned int WriterSNO,
		     char far *RdBuff, unsigned int BuffSize);
  /*
   34 ����ͨ�ŷ�����ȡ���ļ�(Ҫ��ͨ�ŶԷ�����ͨ�ŷ�����)��
      ����������
               LocalfName   �ļ��ı���(Ŀ��)��
               RemotefName  �ļ���Զ��(Դ)��
               ShowInfor    ��ʾ��Ϣѡ��
                            _NOT_SLNT   ��ʾͨ����Ϣ
                            _SLNT       ����ʾͨ����Ϣ
               Language     ��ʾ��Ϣ������(Ӣ,��)ѡ��
                            _IN_CHI     ʹ������
                            _IN_ENG     ʹ��Ӣ��
               WriterSNO    ͨ�ŶԷ��Ļ���ϵ�к�
               Rdbuff       ���ܻ�������ַ 
               Buffsize     ����������
      ���ز�����
               ��
      ����ֵ��   
               0             �ɹ�
               ��0           ʧ�ܴ�����
			     ����������������б�
  */

  extern void SelectPort(unsigned char port);
  /*
 ��35 ѡ��ͨ�ſڡ�
      ������
	       port   ͨ�ſ�
                      0     ���п�1��COM1��
                      1     ���п�2��COM2��
      ���ز���:
               ��
      ����ֵ��
               ��
     ��ע�͡�HT-2800ֻ��һ��COM�ڣ����Բ���port��ֵ�Ƕ��٣����Ǵ��п�1��COM1����
  */

  #endif


