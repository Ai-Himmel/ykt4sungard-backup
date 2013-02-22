
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
  #define _MDIR_REQ     7  (在 HT2800上有效）
  #define _RDIR_REQ     8  (在 HT2800上有效）
  #define _LSTN_REQ     9  (在 HT2800上有效）
  #define _STM_REQ      10 (在 HT2800上有效）

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
   1    安装通信内核
  */

  extern far int  pascal UninstComPls(void);
  /*
   2    卸掉通信内核
  */

  extern int  ComPlsInstalled(void);
  /*
   3 测试通讯内核是否安装
       参数：     无
       返回参数： 无
       函数值：   0         未安装
                  非0    已安装
  */

  extern void GetCommMode(unsigned char far *WorkMode,
                          unsigned char far *CommPort,
	                  unsigned int far *BaudRate);
  /*
   4 取得当前通信口、工作模式和波特率。
　   参数：　 
              WorkMode
              CommPort
	       BaudRate
     返回参数： 
               WorkMode     工作模式
                 _PAK_MODE  数据包传送/接收方式
                 _AUX_MODE  字符流传送/接收方式
               CommPort     当前通信口
                 0          串行口１（COM1）
                 1          串行口２（COM2）
               BaudRate     当前波特率
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
                 0fff0h     115200bps  （在 HT2800上有效）
     函数值：        无 
  */

  extern int  SetCommMode(unsigned char WorkMode,
                          unsigned char CommPort,
                          unsigned int BaudRate);
  /*  
   5 设置通信口、工作模式和波特率。
  　 参数：　　
        WorkMode    工作模式
          _PAK_MODE                         2     数据包传送/接收方式
          _AUX_MODE                         3     字符流传送/接收方式 8N1
          _AUX_MODE+_mod_8D1P+_par_ODD      51    字符流传送/接收方式 8O1
          _AUX_MODE+_mod_8D1P+_par_EVEN     179   字符流传送/接收方式 8E1
          _AUX_MODE+_mod_7D1P+_par_ODD      19    字符流传送/接收方式 7O1
          _AUX_MODE+_mod_7D1P+_par_EVEN     147   字符流传送/接收方式 7E1
          _AUX_MODE+_mod+7D                 67    字符流传送/接收方式 7N1
          _AUX_MODE+_mod_8D1P+_mod_7D       115   字符流传送/接收方式 9N1

          （9N1 仅适用于HT1820，在 HT2800上无效 ！）

        CommPort     当前通信口
          0          串行口１（COM1)
          1          串行口２（COM2)
        BaudRate     当前波特率
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
          0fff0h     115200bps   （在 HT2800上有效）
    返回参数：
               无
    函数值：　 
	       0　          设置成功
               4　          非法模式
               5　          非法波特率
  */

  extern unsigned int GetSerialNo(void);
  /*   
   6 取得机器系列号。
  　 参数：     
               无　
     返回参数: 
               无
     函数值：
	  　 　机器系列号
  */ 

  extern void SetSerialNo(unsigned int SerialNo);
  /*
   7 设置机器系列号。
  　 参数：　　
  　           SerialNo　  机器系列号
                 机器系列号的范围在 0 至 65535 之间
     返回参数:
               无
     函数值：
               无
  */ 

  extern void EnableRx(unsigned int RxSerialNo);
  /*
   8 允许串行口接收具指定系列号的机器发送来的数据。
  　 参数：　　
  　           SerialNo　  机器系列号
               机器系列号的范围在 0 至 65535 之间
     返回参数:
               无
     函数值：
               无
    【注释】  机器系列号为零表明允许接收任何机器发送来的数据。
              字符流工作方式下机器系列号无意义。
              发此调用将清除数据包和字符流缓冲区内的所有数据。
  */ 

  extern void DisableRx(void);
  /*   
   9 禁止串行口接收任何数据。
  　 参数：     
               无　
     返回参数: 
               无
     函数值：
               无
  */ 

  extern int  RxPackage(unsigned char far *Buffer);
  /* 
   10 数据包传送/接收方式下接收数据
  　  参数：     
	       Buffer       数据包缓冲区指针　
      返回参数: 
               无
      函数值：
          　   0            没有接收到任何数据包
               大于 0       数据包长度（字节）
               小于 0       接收到错误数据包个数（的相反数）
  */ 

  extern int  TxPackage(unsigned char far *Buffer, unsigned int BufLength);
  /* 
   11 数据包传送/接收方式下发送数据包。
  　  参数：     
               Buffer       数据包缓冲区指针　
	       BufLength    数据包长度
      返回参数: 
               无
      函数值：
          　   0            发送成功
               1            通信超时
               2            链路错误
               3            数据包过长
               4            非法工作模式（当前工作模式不是数据包方式）
      【注释】  　最大数据包长度为 512 个字节。
  */ 

  extern int  PutAuxByte(unsigned char AuxByte);
  /* 
   12 字符流传送/接收方式下发送字符。
    　参数：
               AuxByte     被发送的字符
      返回参数: 
               无
      函数值：
          　   0           发送成功
               非0         当前工作方式不是字符流传送/接收方式
  */ 

  extern int  AuxByteExist(unsigned char far *AuxByte,
                           unsigned char far *Status);
  /*
   13 字符流传送/接收方式下取得字符接收状态。
  　  参数：     
               AuxByte      接收字符
               Status       接收状态
      返回参数: 
    	       AuxByte      返回字符
               Status       返回状态
      函数值：
          　   0            未接收到任何字符
               非0          已接收到字符
     【注释】  该字符并未由字符流缓冲区中读取出来。
  */ 

  extern int  GetAuxByte(unsigned char far *AuxByte,
	                 unsigned char far *Status);
  /*
   14 字符流传送/接收方式下读取字符。
  　  参数：     
               AuxByte      接收字符
               Status       接收状态
      返回参数:
	       AuxByte      返回字符
	       Status       返回状态
      函数值：
	   　  0           接收到字符
	       非0         当前工作方式不是字符流传送/接收方式
		           或因按ESC(ON)键中断退出
   【注释】  该字符已从字符流缓冲区中读取出来。
  */

  extern int  ExistAuxBGot(unsigned char far *AuxByte,
	      	           unsigned char far *Status);
  /*
   15 取得字符接收状态并读取已接收到的字符
  　  参数：
	       AuxByte      接收字符
	       Status       接收状态
      返回参数:
	       AuxByte      返回字符
	       Status       返回状态
      函数值：
	   　  0           未接收到任何字符
	       非0         已接收到字符
     【注释】  该字符已从字符流缓冲区中读取出来。
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
     【注释】  此函数在HT-2800上无效。
  */

  extern void PutAuxNinthBit(unsigned char NinthBit);
  /*
   19 
     【注释】  此函数在HT-2800上无效。
  */

  extern void DisableTimeOut(void);
  /*
   20 文件通信过程中关闭超时检测开关。
  　  参数：
	       无
      返回参数:
	       无
      函数值：
	       无
     【注释】当打开超时检测开关时, 一旦数据包超过其最大可能传输延误二十秒后
             仍未到达，文件通信自动中断并返回超时错误。
   　　　　　在文件通信过程中如无必需的长时间延误，建议打开超时检测开关以避
 　  　　　　免因链路故障导致的死等。
  */ 

  extern void EnableTimeOut(void);
  /*
   21 文件通信过程中打开超时检测开关。
  　  参数：     
               无
      返回参数: 
               无
      函数值：
	       无
     【注释】当打开超时检测开关时, 一旦数据包超过其最大可能传输延误二十秒后
             仍未到达，文件通信自动中断并返回超时错误。
   　　　　　在文件通信过程中如无必需的长时间延误，建议打开超时检测开关以避
  　 　　　　免因链路故障导致的死等。
  */ 

  extern int  ExfOpen(unsigned char OpenMode, unsigned int ValidSNo,
                      char far *FileName,
                      unsigned char far *ExfAttr,
                      unsigned long far *ExfSize,
                      unsigned long far *ExfStamp,
                      unsigned int far *theOthSNo);
  /*
   22 数据包通信方式下按读/写请求打开外部文件。
  　  参数：　
               OpenMode      打开方式
                             _READ  读外部文件
                             _WRITE 写外部文件
               ValidSNo      对方允许系列号
               FileName      文件名字符串
               ExfAttr       文件属性
               ExfSize       文件大小
               ExfStamp      文件时间(按MS-DOS文件时间格式存放)
               theOthSNo     对方实际系列号
     【注释】依读请求打开外部文件时
 　　　　　 　  输入参数为：
 　　　　　　   对方允许系列号　用来指定通信对方所必须具有的机器系列号，
 　　　　　　　　　　　　　　　 为零时表示可以与任意机器通信。
 　　　　　　　 文件名字符串    以字符*开始的字符串表明读取任意文件，否则
   　　　　　　　　　　　　　　 对方传来的文件必须具有与指定字串相同的名字。
             　返回值为：
                 文件名字符串　　对方传来的文件名
                 文件属性        对方传来的文件属性
                 文件时间        对方传来的文件时间
                 文件大小        对方传来的文件大小
                 对方实际系列号  对方实际具有的系列号
                【注意】：如果对方未设置文件属性、时间或大小，则返回的可能是随机值
            依写请求打开外部文件时 　
　　　　　　　　输入参数为：
　　　　　　　   对方允许系列号　用来指定通信对方所必须具有的机器系列号
　　　　　　　　　　　　　　　　 为零时表示可以与任意机器通信。
　　　　　　　　 文件名字符串    指定外部文件所用的文件名, 对方必须指定相同的文件名或指定*字符串
                 文件属性        文件属性
                 文件时间        文件时间
                 文件大小        文件大小
            返回值为：
                 对方实际系列号  对方实际具有的系列号

    返回值：  0   打开成功
              1   通信超时
              2   链路错误
              6   通信被取消
              7   文件名不匹配
              8   非法方式
              10  外部文件已经被打开
              11  非法文件名
  */

  extern int  ExfRead(char far *RdBuff, unsigned int RdCount,
                      unsigned int far *ActRdCnt);
  /*
   23 数据包通信方式下读外部文件。
 　   参数：　
              RdBuff       读入缓冲区地址
　  　　　　  RdCount      读入长度（字节）
              ActRdCnt     实际读入长度（字节）
      返回参数：
              ActRdCnt     实际读入长度（字节）
      函数值：
              0            成功
              非0          失败
              错误代码
                   1   通信超时
                   2   链路错误
                   6   通信被取消
                   8   非法方式（外部文件未按读方式打开）
     【注释】   当实际读入长度小于指定读入长度时，表示外部文件已结束。
  */

  extern int  ExfWrite(char far *WrtBuff, unsigned int WrtCount,
                       unsigned int far *ActWrtCnt);
  /*
   24 数据包通信方式下写外部文件。
  　  参数：　　
               WrtBuff       写出缓冲区地址
 　 　　　　   WrtCount      写出长度（字节）
               ActWrtCnt     实际写出长度（字节）
      返回参数：
               ActWrtCnt     实际写出长度（字节）
      函数值：
               0             成功
               非0           失败
               错误代码
                   1   通信超时
                   2   链路错误
                   6   通信被取消
                   8   非法方式（外部文件未按写方式打开）
                   9   文件被截断（通信对方未读完所有写出字节便关闭了文件）
  */

  extern void ExfClose(void);
  /*
   25 数据包通信方式下关闭外部文件。
  　  参数：　　
               无
      返回参数：
	       无
      函数值：
	       无
  */

  extern int  SendClientReq(unsigned char ReqType, unsigned int ServerID,
	            	    char *DescString, unsigned int *AcceptComment);
  /* 
   26 向通信服务器提交客户请求(要求通信对方运行通信服务器)。
  　  参数：   ReqType    请求类型（0..255，'a'..'z'和'A'..'Z' 除外）
			    _DEL_REQ  删除文件请求
			    _SNO_REQ  获取系列号请求
 　   　　　   ServerID   服务器系列号（为零表明可与任何运行服务器软件的机器通信）
	       DescString 请求描述串
			    _DEL_REQ 时包含文件名
	       AcceptComment 接受备注
      返回参数：
               AcceptComment 接受备注
			   _SNO_REQ 被接收时返回取得的系列号
      函数值:  0   请求被接受
	       1   通信超时
	       2   链路错误
	       其他值 请求被拒绝时的原因码
  　 【注释】　请求描述串为任意长度不超过255个字节的字符串
  */

  extern int  ClientReqExist(unsigned char far *ReqType,
 		             REQ_DESC far *ReqDesc);
  /* 
   27  CommPlus 保留 
  */

  extern int  AcceptReq();
  /*
   28 CommPlus 保留 
  */

  extern int  RejectReq(unsigned int RejectReason);
  /*
   29 CommPlus 保留 
  */

  extern int  SendFileOut(char far *LocalfName, unsigned char ShowInfor,
                          unsigned char Language, unsigned int ReaderSNO,
                          char far *WrtBuff, unsigned int BuffSize);
  /*
   30 发送文件(要求通信对方运行接收文件)。
      参数：　　
               LocalfName   本地发送文件名
               ShowInfor    显示信息选择
                            _NOT_SLNT   显示通信信息
                            _SLNT       不显示通信信息
               Language     显示信息的语言(英,中)选择
                            _IN_CHI     使用中文
                            _IN_ENG     使用英文
               ReaderSNO    通信对方的机器系列号
               Wrtbuff      发送缓冲区地址
               Buffsize     缓冲区长度
      返回参数：
               无
      函数值：   
               0             成功
               非0           失败错误码
                             错误码详见错误码列表
  */

  extern int  CopyFileIn(char far *LocalfName, char far *RemotefName,
                         unsigned char ShowInfor,
                         unsigned char Language, unsigned int WriterSNO,
                         char far *RdBuff, unsigned int BuffSize);
  /*
   31 接收文件(要求通信对方运行发送文件)。
      参数：　　
               LocalfName   接收文件的本地(目的)名
               RemotefName  接收文件的远地(源)名
               ShowInfor    显示信息选择
                            _NOT_SLNT   显示通信信息
                            _SLNT       不显示通信信息
               Language     显示信息的语言(英,中)选择
                            _IN_CHI     使用中文
                            _IN_ENG     使用英文
               WriterSNO    通信对方的机器系列号
               Rdbuff       接收缓冲区地址 
               Buffsize     缓冲区长度
      返回参数：
               无
      函数值：   
               0             成功
               非0           失败错误码
                             错误码详见错误码列表
  */

  extern void fServer(unsigned char CommPort, unsigned int BaudRate,
                      unsigned char Silent, unsigned char LangSelect,
                      unsigned int BufferSize, char far *Buffer);
  /*
   32 通信服务器。
      参数:
               CommPort     串行口号
               BaudRate     波特率
               Silent       显示信息选择
                            _NOT_SLNT   显示通信信息
                            _SLNT       不显示通信信息
               LangSelect   显示信息的语言(英,中)选择
                            _IN_CHI     使用中文
                            _IN_ENG     使用英文?
               buffer       通信缓冲区地址
               BufferSize   缓冲区长度
      返回参数：
               无
      函数值：   
               无
  */

  extern int  ExfPut(char far *LocalfName, char far *RemotefName,
                     unsigned char ShowInfor,
                     unsigned char Language,
                     unsigned int ReaderSNO,
                     char far *WrtBuff, unsigned int BuffSize);
  /*
   33 面向通信服务器发送文件(要求通信对方运行通信服务器)。
      参数：　　
               LocalfName   文件的本地(源)名
               RemotefName  文件的远地(目的)名
               ShowInfor    显示信息选择
                            _NOT_SLNT   显示通信信息
                            _SLNT       不显示通信信息
               Language     显示信息的语言(英,中)选择
                            _IN_CHI     使用中文
                            _IN_ENG     使用英文
               ReaderSNO    通信对方的机器系列号
               Wrtbuff      发送缓冲区地址 
               Buffsize     缓冲区长度
      返回参数：
               无
      函数值：   
               0             成功
               非0           失败
               非0           失败错误码
                             错误码详见错误码列表
  */

  extern int  ExfGet(char far *LocalfName, char far *RemotefName,
	             unsigned char ShowInfor,
		     unsigned char Language,
		     unsigned int WriterSNO,
		     char far *RdBuff, unsigned int BuffSize);
  /*
   34 面向通信服务器取得文件(要求通信对方运行通信服务器)。
      参数：　　
               LocalfName   文件的本地(目的)名
               RemotefName  文件的远地(源)名
               ShowInfor    显示信息选择
                            _NOT_SLNT   显示通信信息
                            _SLNT       不显示通信信息
               Language     显示信息的语言(英,中)选择
                            _IN_CHI     使用中文
                            _IN_ENG     使用英文
               WriterSNO    通信对方的机器系列号
               Rdbuff       接受缓冲区地址 
               Buffsize     缓冲区长度
      返回参数：
               无
      函数值：   
               0             成功
               非0           失败错误码
			     错误码详见错误码列表
  */

  extern void SelectPort(unsigned char port);
  /*
 　35 选择通信口。
      参数：
	       port   通信口
                      0     串行口1（COM1）
                      1     串行口2（COM2）
      返回参数:
               无
      函数值：
               无
     【注释】HT-2800只有一个COM口，所以不论port的值是多少，都是串行口1（COM1）。
  */

  #endif


