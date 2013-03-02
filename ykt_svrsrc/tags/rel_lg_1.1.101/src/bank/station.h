/******************************************************************************
 *
 * programName:    station.h
 * function:       station config information
 * built:          2001-07-15
 * updateRecord:
 *
 ******************************************************************************
 */

 #ifndef		__STATION_H__
 #define		__STATION_H__

 //配置文件名
 #define		STN_CONFIG_FILE		"stn.cfg"

 //define match string
 #define		STN_CONFIG_BANK		"BANK_N"
 #define		STN_CONFIG_COMPANY	"COMPANY"
 #define		STN_CONFIG_HEADLINE	"HEADLINE"
 #define		STN_CONFIG_TAILLINE     "TAILLINE"
 #define		STN_CONFIG_LOCATION	"LOCATION"
 #define		STN_CONFIG_VERSION	"VERSION"
 #define		STN_CONFIG_LOCAL_ID	"LOCAL_ID"
 #define		STN_CONFIG_SERVER_ID	"SERVER_ID"
 #define		STN_CONFIG_SERVER_PORT	"SERVER_PORT"
 #define		STN_CONFIG_HOST_NAME	"HOST_NAME"
 #define		STN_CONFIG_HOST_IP	"HOST_IP"
 #define		STN_CONFIG_SERV_NAME	"SERV_NAME"
 #define		STN_CONFIG_SERV_IP	"SERV_IP"
 #define		STN_CONFIG_MAGPORT	"MAGPORT"
 #define		STN_CONFIG_PRNPORT	"PRNPORT"
 #define		STN_CONFIG_SPEED	"SPEED"
 #define		STN_CONFIG_TIMEOUT	"TIMEOUT"
  
 ///////////////////////////////////////////////////////////////////
 //参数文件
 ///////////////////////////////////////////////////////////////////
 typedef struct {

	char	bankN[50];	//银行名
	char	company[50];	//公司名
	char	headLine[50];	//打印标题
	char	tailLine[50];	//打印结束串
	char	location[50];	//使用地点
	int		version;		//版本号
	long	stnNo;		//本机站点号
	long	serNo;		//服务机站点号
	long	serPort;	//服务方TCP端口号
	char	servName[40];	//服务方机器名
	char	servIp[20];	//服务方IP地址
	char	hostName[40];	//本机名
	char	hostIp[20];	//本机IP地址
	int	magPort;	//磁卡器端口
	int	prnPort;	//打印机端口
	int	speed;		//外设速度
	int	timeout;	//最大超时时间
 }STN_CONFIG;


 #endif
