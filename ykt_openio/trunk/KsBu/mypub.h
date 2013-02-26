/********************************************************************
	created:	2004/02/11
	created:	11:2:2004   23:39
	filename: 	E:\proj\goldmem\public\mypub.h
	file path:	E:\proj\goldmem\public
	file base:	mypub
	file ext:	h
	author:		CHENYH
	
	purpose:	
*********************************************************************/
#ifndef __MYPUB_H_
#define __MYPUB_H_

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif


#ifndef BYTE
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
#endif
#ifndef INT4
typedef char			INT1;
typedef short			INT2;
typedef int				INT4;
#endif
#ifndef REAL4
typedef float			REAL4;
typedef double			REAL8;
#endif


//��Windows�£����¶���MAX��MIN��
#ifdef WIN32
#define MAX(a,b) _MAX(a,b)
#define MIN(a,b) _MIN(a,b)
#endif

#ifndef ASSERT
#ifdef _DEBUG
#define ASSERT(booleanExpression )					\
	if(!(booleanExpression)){						\
		RAISE_DESIGN_ERROR(#booleanExpression);		\
	}

#define DebugMessageDisplay(msg)   printf("%s:%d <%s>\n",__FILE__,__LINE__,msg)

#else
#define ASSERT(booleanExpression)
#define DebugMessageDisplay(msg)
#endif
#endif

#include <fcntl.h>
#include <sys/stat.h>
#ifdef WIN32
#include <share.h>
#define sh_fopen(a,b,c) _fsopen(a,b,c)
#include <io.h>
#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#else
#define SH_DENYNO    0x40
#define SH_DENYWR    0x20
#define sh_fopen(a,b,c) fopen(a,b)
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif


/* ȥ�����ҿո�   */
BUPUB_API char *mytrim(char *s);


// ������: *Strncpy
// ���  : ������ 2004-2-21 13:39:08
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
BUPUB_API char *Strncpy(char *dest,char *source,unsigned int count);

// ������: *Strncpy_t
// ���  : ������ 2004-2-21 13:39:12
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
//        ͬʱȥ�����ҿո�
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
BUPUB_API char *Strncpy_t(char *dest,char *source,unsigned int count);

// ������: mytrim_r
// ���  : ������ 2004-2-21 13:45:29
// ����  : ����ַ����ұߵ�' '��'\t'
// ����  : char *
// ����  : char *dest
BUPUB_API char *mytrim_r(char *dest);

// ������: Strncpy_rt
// ���  : ������ 2004-2-21 13:46:22
// ����  : ���Ʋ����dest�ұߵ�' '��'\t'
// ����  : char * ����dest��ָ��
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
BUPUB_API char *Strncpy_rt(char *dest,char *source,unsigned int count);

// ����  : ���÷ָ��separator�ָ�Ĵ��ַ���pc�У���ȡ��pid�����ַ�����para��
// ����  : int ��true(!=0)-Ϊ�ɹ���false(0)��Ϊʧ��
// ����  : const char *pc [IN]: ���ַ��� �� "000,1,22, 333,4444"
// ����  : char separator [IN]: �ָ�� ��','
// ����  : int pid [IN]: Ҫ��ȡ�����ַ�������ţ���0��ʼ
// ����  : char *para [OUT]: ����ȡ���������ַ�������������pid=3�����ַ�������Ϊ" 333"
// ����  : int psize [IN]: para����ĳ��ȣ����ֽ�����ʾ
// ����  : char *rtnmsg [OUT]: ���ش�����Ϣ 
int GetSubString(const char *pc, char separator ,int pid, char *para, int psize, char *rtnmsg);

// ������: percolate
// ���  : ������ 2003-9-24 13:38:37
// ����  : ���ַ����н��Ƿ��ַ����˵���ͬʱ����//��Ϊ����Ϊע������Ҳͬ//һ����˵�
// ����  : int �������ĳ���
// ����  : char *str In��Out
BUPUB_API int percolate(char *str);

// ������: *getfmttime
// ���  : ������ 2003-10-14 11:23:47
// ����  : ��tm��ʱ��ת��Ϊ����ʱ��ĸ�ʽ���ַ���������ϵͳ��non-thread-safe
// ����  : char * ��ʽ�����ַ���ָ��, NULL ��ʹ���ڲ���̬�ռ��Ÿ�ʽ�����ַ�����
// ����  : time_t *ptm ����Ҫת����ʱ�� ==NULL ��Ϊת��ʱʱ���
// ����  : int fmttype 
/*
            0 : hh:mm:ss
            1 : MM/DD-hh:mm:ss
            2 : YYYY/MM/DD-hh:mm:ss
            3 : YYYYMMDD
            4 : hhmmss
            ���� : YYYYMMDDhhmmss
*/
// ����  : char *outstr ����ַ����Ļ��棬=NULL��ʹ���ڲ��ľ�̬���棬�䳤����Ҫ��fmttype����
BUPUB_API char *getfmttime(void *ptm,int fmttype,char *outstr);


// ������: mysleep
// ���  : ������ 2004-2-11 12:35:51
// ����  : ���߳̽���˯��״̬milliseconds����
// ����  : void 
// ����  : unsigned int milliseconds
BUPUB_API void mysleep(unsigned int milliseconds);

#ifndef WIN32
// ������: GetTickCount
// ���  : ������ 2004-2-11 20:55:11
// ����  : Ϊ�˺�WINDOWSƽ̨���ݣ���ȡ��ǰ��ʱ���
// ����  : unsigned int 
BUPUB_API unsigned int GetTickCount();
#endif


// ������: tc2_tc1
// ���  : ������ 2004-2-11 21:06:59
// ����  : ��GetTickCount()�õ��ĺ���ʱ���Ĳ������ƣ� t2-t1 �����ڷ�WINDOWS��ʱ���ʵ�ʲ��ܳ���1��
// ����  : unsigned int   tc2-tc1 
// ����  : unsigned int tc2
// ����  : unsigned int tc1
BUPUB_API unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1);



// ������: DataDumpFile
// ���  : ������ 2005-3-24 18:19:51
// ����  : ������ת�����ļ���
// ����  : void 
// ����  : char *filename
// ����  : char *data
// ����  : int datalen
BUPUB_API void DataDumpFile(char *filename,char *data,int datalen);

// ������: OutErrorFile
// ���  : ������ 2004-2-7 15:14:33
// ����  : ��������Ϣ��¼�������¼�ļ���
// ����  : void 
// ����  : char *efilename
// ����  : char *msg
// ����  : char *sourcefile
// ����  : int lineno
BUPUB_API void OutErrorFile(char *efilename,char *msg,char *sourcefile,int lineno);


// ������: DebugFileOut
// ���  : ������ 2004-2-11 14:37:14
// ����  : ����Ϣ��¼�����ٵ����ļ��У��Է�����Ժ�����Ĳ�ѯ
// ����  : void 
// ����  : char *dfilename ���ٵ����ļ������ļ���
// ����  : char *msg ���ٵ�����Ϣ
// ����  : char *sourcefile Դ�ļ�����
// ����  : int lineno Դ�ļ����к�
BUPUB_API void DebugFileOut(char *dfilename,char *msg,char *sourcefile,int lineno);

// ������: RemoveOverdueFile
// ���  : ������ 2004-4-6 9:52:41
// ����  : �����ָ����Ŀ¼path_mark�µ��޸���������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
BUPUB_API int RemoveOverdueFile(char *path_mark,char *ext,int overdue);

// ������: RemoveOverdueFileInSecond
// ���  : ������ 2008-10-7 13:41:20
// ����  : �����ָ����Ŀ¼path_mark�µ��޸�ʱ������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark  ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
BUPUB_API int RemoveOverdueFileInSecond(char *path_mark,char *ext,int overdue);

//�׳�һ��CDesignError�쳣
//@����	msg	char*	ָ���Ĵ�����Ϣ
//@�쳣	CDesignError	�׳����쳣������λ���ڵ�ǰ�ļ���ǰ��
#define RAISE_DESIGN_ERROR(msg) { OutErrorFile("DesignError",msg,__FILE__,__LINE__); exit(-1000);}

//�׳�һ��CRuntimeError
//@����	msg	char*	ָ���Ĵ�����Ϣ
//@�쳣	CRuntimeError	�׳����쳣������λ���ڵ�ǰ�ļ���ǰ��
#define RAISE_RUNTIME_ERROR(msg) { OutErrorFile("RuntimeError",msg,__FILE__,__LINE__); exit(-1001);}

extern int iThisProcID;   // �������ID��ʶ����Ӧ�÷���ܹ����䣬������Ϊ������ϵͳ��Ψһ������OutErrorFile��Ϊ�ļ�����¼���������� 
//#define DEBUG_RUNTIME_MSGOUT(msg) { DebugFileOut("runtimedebug",msg,__FILE__,__LINE__);}
#if defined(BUPUB_EXPORTS)||defined(BUPUBLIB)
#define DEBUG_RUNTIME_MSGOUT(msg) { g_pLogFile->WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }
#else
#define DEBUG_RUNTIME_MSGOUT(msg) { g_LogFile.WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }
#endif

#ifdef __cplusplus
}
#endif

// ����Ϊ�������ݵ�ʱ��pushmodeѡ�õĲ�����
#ifndef PM_INACK 
   #define PM_CLEAR  'X'
   #define PM_INACK  '0'  /* �ǿɿ����� */
   #define PM_ACK    '1'  /* �ɿ�����,��Ҫ�Է����պ�����н���ȷ�ϻص� */
   #define PM_ANSWER '2'  /* �����������ʹ�ã���Ϊ�����͸�Ŀ��㣬�ⲿ���������Ӧ�𷵻ص�ʱ����Ҫ�ٴ��ύ��ԭʼ��BUNIT */
#endif

/* ****** Updated by CHENYH at 2004-3-10 13:02:41 ****** 
// ����BCCӦ�����ݴ���ģʽ����CBULinkThread/CSvrLink�е�iAnswerMode
*/
#ifndef AM_AUTO
   #define AM_AUTO     'A'   // һ�������ݾʹ���Զ����͸�����ͻ���
   #define AM_CONFIRM  'C'   // ������ֻ����ҵ����Ҫ��ŷ��͸�����ͻ���,��Ҫ��AnswerData��AnswerDataPart�ŷ���
#endif

#undef BUPUB_API

#endif

