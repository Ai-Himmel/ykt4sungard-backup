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

#ifdef WIN32
#include <share.h>
#define sh_fopen(a,b,c) _fsopen(a,b,c)
#else
#define SH_DENYNO    0x40
#define SH_DENYWR    0x20
#define sh_fopen(a,b,c) fopen(a,b)
#endif


/* ȥ�����ҿո�   */
char *mytrim(char *s);


// ������: *Strncpy
// ���  : ������ 2004-2-21 13:39:08
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy(char *dest,char *source,unsigned int count);

// ������: *Strncpy_t
// ���  : ������ 2004-2-21 13:39:12
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
//        ͬʱȥ�����ҿո�
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy_t(char *dest,char *source,unsigned int count);

// ������: mytrim_r
// ���  : ������ 2004-2-21 13:45:29
// ����  : ����ַ����ұߵ�' '��'\t'
// ����  : char *
// ����  : char *dest
char *mytrim_r(char *dest);

// ������: Strncpy_rt
// ���  : ������ 2004-2-21 13:46:22
// ����  : ���Ʋ����dest�ұߵ�' '��'\t'
// ����  : char * ����dest��ָ��
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy_rt(char *dest,char *source,unsigned int count);


// ������: percolate
// ���  : ������ 2003-9-24 13:38:37
// ����  : ���ַ����н��Ƿ��ַ����˵���ͬʱ����//��Ϊ����Ϊע������Ҳͬ//һ����˵�
// ����  : int �������ĳ���
// ����  : char *str In��Out
int percolate(char *str);

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
char *getfmttime(void *ptm,int fmttype,char *outstr);


// ������: mysleep
// ���  : ������ 2004-2-11 12:35:51
// ����  : ���߳̽���˯��״̬milliseconds����
// ����  : void 
// ����  : unsigned int milliseconds
void mysleep(unsigned int milliseconds);

#ifndef WIN32
// ������: GetTickCount
// ���  : ������ 2004-2-11 20:55:11
// ����  : Ϊ�˺�WINDOWSƽ̨���ݣ���ȡ��ǰ��ʱ���
// ����  : unsigned int 
unsigned int GetTickCount();
#endif


// ������: tc2_tc1
// ���  : ������ 2004-2-11 21:06:59
// ����  : ��GetTickCount()�õ��ĺ���ʱ���Ĳ������ƣ� t2-t1 �����ڷ�WINDOWS��ʱ���ʵ�ʲ��ܳ���1��
// ����  : unsigned int   tc2-tc1 
// ����  : unsigned int tc2
// ����  : unsigned int tc1
unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1);

// ������: OutErrorFile
// ���  : ������ 2004-2-7 15:14:33
// ����  : ��������Ϣ��¼�������¼�ļ���
// ����  : void 
// ����  : char *efilename
// ����  : char *msg
// ����  : char *sourcefile
// ����  : int lineno
void OutErrorFile(char *efilename,char *msg,char *sourcefile,int lineno);


// ������: DebugFileOut
// ���  : ������ 2004-2-11 14:37:14
// ����  : ����Ϣ��¼�����ٵ����ļ��У��Է�����Ժ�����Ĳ�ѯ
// ����  : void 
// ����  : char *dfilename ���ٵ����ļ������ļ���
// ����  : char *msg ���ٵ�����Ϣ
// ����  : char *sourcefile Դ�ļ�����
// ����  : int lineno Դ�ļ����к�
void DebugFileOut(char *dfilename,char *msg,char *sourcefile,int lineno);

// ������: RemoveOverdueFile
// ���  : ������ 2004-4-6 9:52:41
// ����  : �����ָ����Ŀ¼path_mark�µ��޸���������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
int RemoveOverdueFile(char *path_mark,char *ext,int overdue);


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
#define DEBUG_RUNTIME_MSGOUT(msg) { g_LogFile.WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }

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

#endif

