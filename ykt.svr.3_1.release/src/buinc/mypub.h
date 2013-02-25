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


//在Windows下，重新定义MAX和MIN宏
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


    /* 去除左右空格   */
    BUPUB_API char *mytrim(char *s);


// 函数名: *Strncpy
// 编程  : 陈永华 2004-2-21 13:39:08
// 描述  : 从source中最多复制count字符到dest，但是在dest[count-1]被赋值为'\0'字符串结束符
// 返回  : char
// 参数  : char *dest
// 参数  : char *source
// 参数  : size_t count
    BUPUB_API char *Strncpy(char *dest,char *source,unsigned int count);

// 函数名: *Strncpy_t
// 编程  : 陈永华 2004-2-21 13:39:12
// 描述  : 从source中最多复制count字符到dest，但是在dest[count-1]被赋值为'\0'字符串结束符
//        同时去除左右空格
// 返回  : char
// 参数  : char *dest
// 参数  : char *source
// 参数  : size_t count
    BUPUB_API char *Strncpy_t(char *dest,char *source,unsigned int count);

// 函数名: mytrim_r
// 编程  : 陈永华 2004-2-21 13:45:29
// 描述  : 清除字符串右边的' '和'\t'
// 返回  : char *
// 参数  : char *dest
    BUPUB_API char *mytrim_r(char *dest);

// 函数名: Strncpy_rt
// 编程  : 陈永华 2004-2-21 13:46:22
// 描述  : 复制并清除dest右边的' '和'\t'
// 返回  : char * 就是dest的指针
// 参数  : char *dest
// 参数  : char *source
// 参数  : size_t count
    BUPUB_API char *Strncpy_rt(char *dest,char *source,unsigned int count);


// 函数名: percolate
// 编程  : 陈永华 2003-9-24 13:38:37
// 描述  : 从字符串中将非法字符过滤掉，同时将以//作为后续为注释描述也同//一起过滤掉
// 返回  : int 结束串的长度
// 参数  : char *str In、Out
    BUPUB_API int percolate(char *str);

// 函数名: *getfmttime
// 编程  : 陈永华 2003-10-14 11:23:47
// 描述  : 将tm的时间转换为本地时间的格式化字符串，本子系统中non-thread-safe
// 返回  : char * 格式化的字符串指针, NULL 则使用内部静态空间存放格式化的字符串，
// 参数  : time_t *ptm ：需要转换的时间 ==NULL 则为转换时时间点
// 参数  : int fmttype
    /*
                0 : hh:mm:ss
                1 : MM/DD-hh:mm:ss
                2 : YYYY/MM/DD-hh:mm:ss
                3 : YYYYMMDD
                4 : hhmmss
                其他 : YYYYMMDDhhmmss
    */
// 参数  : char *outstr 输出字符串的缓存，=NULL则使用内部的静态缓存，其长度需要视fmttype而定
    BUPUB_API char *getfmttime(void *ptm,int fmttype,char *outstr);


// 函数名: mysleep
// 编程  : 陈永华 2004-2-11 12:35:51
// 描述  : 本线程进入睡眠状态milliseconds毫秒
// 返回  : void
// 参数  : unsigned int milliseconds
    BUPUB_API void mysleep(unsigned int milliseconds);

#ifndef WIN32
// 函数名: GetTickCount
// 编程  : 陈永华 2004-2-11 20:55:11
// 描述  : 为了和WINDOWS平台兼容，获取当前的时间点
// 返回  : unsigned int
    BUPUB_API unsigned int GetTickCount();
#endif


// 函数名: tc2_tc1
// 编程  : 陈永华 2004-2-11 21:06:59
// 描述  : 以GetTickCount()得到的毫秒时间点的差，（毫秒计） t2-t1 ，对于非WINDOWS，时间差实际不能超过1天
// 返回  : unsigned int   tc2-tc1
// 参数  : unsigned int tc2
// 参数  : unsigned int tc1
    BUPUB_API unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1);



// 函数名: DataDumpFile
// 编程  : 陈永华 2005-3-24 18:19:51
// 描述  : 将数据转储到文件中
// 返回  : void
// 参数  : char *filename
// 参数  : char *data
// 参数  : int datalen
    BUPUB_API void DataDumpFile(char *filename,char *data,int datalen);

// 函数名: OutErrorFile
// 编程  : 陈永华 2004-2-7 15:14:33
// 描述  : 将错误信息记录到错误记录文件中
// 返回  : void
// 参数  : char *efilename
// 参数  : char *msg
// 参数  : char *sourcefile
// 参数  : int lineno
    BUPUB_API void OutErrorFile(char *efilename,char *msg,char *sourcefile,int lineno);


// 函数名: DebugFileOut
// 编程  : 陈永华 2004-2-11 14:37:14
// 描述  : 将信息记录到跟踪调试文件中，以方便调试和问题的查询
// 返回  : void
// 参数  : char *dfilename 跟踪调试文件生成文件名
// 参数  : char *msg 跟踪调试信息
// 参数  : char *sourcefile 源文件名称
// 参数  : int lineno 源文件的行号
    BUPUB_API void DebugFileOut(char *dfilename,char *msg,char *sourcefile,int lineno);

// 函数名: RemoveOverdueFile
// 编程  : 陈永华 2004-4-6 9:52:41
// 描述  : 清除在指定的目录path_mark下的修改日期早于overdue的天数的文件
// 返回  : int 删除的文件数
// 参数  : char *path_mark 指定的目录（如果需要应该包括目录分隔符，如MS操作系统的'\\' 或其他的'/'）
// 参数  : char *ext 文件扩展名，包括 '.'
// 参数  : int overdue  指定过期的天数
    BUPUB_API int RemoveOverdueFile(char *path_mark,char *ext,int overdue);


//抛出一个CDesignError异常
//@参数	msg	char*	指定的错误信息
//@异常	CDesignError	抛出此异常，错误位置在当前文件当前行
#define RAISE_DESIGN_ERROR(msg) { OutErrorFile("DesignError",msg,__FILE__,__LINE__); exit(-1000);}

//抛出一个CRuntimeError
//@参数	msg	char*	指定的错误信息
//@异常	CRuntimeError	抛出此异常，错误位置在当前文件当前行
#define RAISE_RUNTIME_ERROR(msg) { OutErrorFile("RuntimeError",msg,__FILE__,__LINE__); exit(-1001);}

    extern int iThisProcID;   // 本程序的ID标识，由应用服务架构分配，可以认为在整个系统中唯一，如用OutErrorFile作为文件名记录跟踪数据用
//#define DEBUG_RUNTIME_MSGOUT(msg) { DebugFileOut("runtimedebug",msg,__FILE__,__LINE__);}
#if defined(BUPUB_EXPORTS)||defined(BUPUBLIB)
#define DEBUG_RUNTIME_MSGOUT(msg) { g_pLogFile->WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }
#else
#define DEBUG_RUNTIME_MSGOUT(msg) { g_LogFile.WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }
#endif

#ifdef __cplusplus
}
#endif

// 下面为推送数据的时候，pushmode选用的参数：
#ifndef PM_INACK
#define PM_CLEAR  'X'
#define PM_INACK  '0'  /* 非可靠推送 */
#define PM_ACK    '1'  /* 可靠推送,需要对方接收后必须有接收确认回单 */
#define PM_ANSWER '2'  /* 在特殊情况下使用，作为请求发送给目标点，外部处理结束后应答返回的时候，需要再次提交给原始的BUNIT */
#endif

/* ****** Updated by CHENYH at 2004-3-10 13:02:41 ******
// 设置BCC应答数据处理模式，见CBULinkThread/CSvrLink中的iAnswerMode
*/
#ifndef AM_AUTO
#define AM_AUTO     'A'   // 一旦有数据就打包自动发送给请求客户端
#define AM_CONFIRM  'C'   // 有数据只有在业务处理要求才发送给请求客户端,需要用AnswerData或AnswerDataPart才发送
#endif

#undef BUPUB_API

#endif

