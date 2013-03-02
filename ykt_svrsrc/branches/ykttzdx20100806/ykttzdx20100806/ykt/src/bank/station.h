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

 //�����ļ���
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
 //�����ļ�
 ///////////////////////////////////////////////////////////////////
 typedef struct {

	char	bankN[50];	//������
	char	company[50];	//��˾��
	char	headLine[50];	//��ӡ����
	char	tailLine[50];	//��ӡ������
	char	location[50];	//ʹ�õص�
	int		version;		//�汾��
	long	stnNo;		//����վ���
	long	serNo;		//�����վ���
	long	serPort;	//����TCP�˿ں�
	char	servName[40];	//���񷽻�����
	char	servIp[20];	//����IP��ַ
	char	hostName[40];	//������
	char	hostIp[20];	//����IP��ַ
	int	magPort;	//�ſ����˿�
	int	prnPort;	//��ӡ���˿�
	int	speed;		//�����ٶ�
	int	timeout;	//���ʱʱ��
 }STN_CONFIG;


 #endif
