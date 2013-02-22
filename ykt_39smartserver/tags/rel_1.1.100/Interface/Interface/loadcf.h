/* ------------------------------------------------------------------------- */
/*
LOADCF.H

创建日期：	2001/5/15
作者：		史光伟
版本信息：	V1.0.1
功能： 
			后台基础模块之读取配置文件头文件

注意：		本头文件须和类型定义头文件"mytypes.h"共同使用

   ------------------------------------------------------------------------- 

修改日期：	2001/5/15
修改人：	
修改描述：	

修改日期： 
修改人：
修改描述： 


备注：

*/
/* ------------------------------------------------------------------------- */

#ifndef __LOADCF_H
#define __LOADCF_H
#include "mytypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/*
	内部使用的函数
*/
int		CF_GetLine(char *pReadBuffer);
void	CF_FilterChar(char *pInBuffer,char *pOutBuffer,char cSkip);
int		CF_InString(char *pBuffer,char *pShortBuffer);
long	CF_GetCurPos(char *pReadBuffer);
int		CF_LocateGroupName(char *pReadBuffer,char *pGroupName);
void	CF_ShowError(char *pReadBuffer,char *pCommandString);
void	CF_AddConfig(char *filename,char *str,long pos);
void	CF_AddConfigGroup(char *filename,char *str);
int		CF_CopyFile(char *src,char *dst);

#ifdef __RS6000__
int		unlink(char *filename);
#endif

/* ------------------------------------------------------------------------- */
/*
	给外部使用的函数
*/
double	CF_GetConfigDouble(char *pReadBuffer,char *pGroupName,char *pCommandString,char *notice);
int		CF_GetConfigDigit(char *pReadBuffer,char *pGroupName,char *pCommandString,char *notice);
char *	CF_GetConfigString(char *pReadBuffer,char *pGroupName,char *pCommandString,char *notice);
BOOL	CF_SetQuietMode(BOOL bNewMode);
BOOL	CF_OpenConfig(char *filename);
BOOL	CF_CloseConfig(void);
void	trim(char *s);
/* ------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif
