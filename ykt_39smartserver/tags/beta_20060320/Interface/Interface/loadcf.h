/* ------------------------------------------------------------------------- */
/*
LOADCF.H

�������ڣ�	2001/5/15
���ߣ�		ʷ��ΰ
�汾��Ϣ��	V1.0.1
���ܣ� 
			��̨����ģ��֮��ȡ�����ļ�ͷ�ļ�

ע�⣺		��ͷ�ļ�������Ͷ���ͷ�ļ�"mytypes.h"��ͬʹ��

   ------------------------------------------------------------------------- 

�޸����ڣ�	2001/5/15
�޸��ˣ�	
�޸�������	

�޸����ڣ� 
�޸��ˣ�
�޸������� 


��ע��

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
	�ڲ�ʹ�õĺ���
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
	���ⲿʹ�õĺ���
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
