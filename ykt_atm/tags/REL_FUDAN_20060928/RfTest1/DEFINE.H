//出错代码：
//1.Com口：
#define _COM_NOT_AVAILABLE		-0x10
#define _COM_SETUP_FAILED			-0x11
#define _COM_READ_TIMEOUT			-0x12
#define _COM_READ_LEN_FAILED		-0x13
#define _COM_READ_ENDCODE_FAILED	-0x14
#define _COM_WRITE_FAILED			-0x15
#define _COM_WRITE_TIMEOUT			-0x16

//ic卡错误码

#define riSelectError		-3000	//卡选择错误
#define riUnknowCmd			-3001    //未知命令
#define riParaErr				-3002	//参数错误
#define riOperStopped		-3003	//操作已停止
#define riTCKErr				-3004	//TCk错误或者奇偶错误
#define riNotPowerup			-3005	//ic卡未上电
#define riParaNumErr			-3006	//参数数目错误
#define riInvalidateCard	-3007	//无效ic卡
#define riCardBeTaken		-3008	//ic卡被拿走
#define riTimeOut				-3009	//超时
#define riRWErr				-3010	//读写错误
#define riComCloseErr    	-3011   //串口关闭错
#define riChecksumErr       -3012    //BCC error

//#define	riSelectError				-3100	//选择卡错误
//系统响应码
#define	rsSuccess					1	//成功
#define	rsTimeOut					-1	//命令超时
#define	rsUnknowCmd					-2	//未知命令
#define	rsTransErr					-3	//传输错误
#define	rsUnknowResp				-4	//未知响应
#define rsEscExit					-5  //ESC中断

/*rf card*/
#define rrERR_FORMAT       -4001
#define rrERR_DATAFORMAT   -4002
#define rrERR_LENGTH       -4003
#define rrERR_READ         -4004
#define rrERR_WRITE        -4005
#define rrERR_LESS         -4006
#define rrERR_BCC          -4007
#define	rrERR_CardData     -4008  // "卡数据错",
#define	rrERR_OpenCom      -4009  // "打开串口错",

