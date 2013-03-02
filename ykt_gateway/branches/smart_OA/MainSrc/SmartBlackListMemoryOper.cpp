#include "stdafx.h"
#include "SmartBlackListMemoryOper.h"

CSmartBlackMemoryOper::CSmartBlackMemoryOper()
{

}
CSmartBlackMemoryOper::~CSmartBlackMemoryOper()
{
	
}

/*=================================================================
* Function ID :  SMT_CheckBlackCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示黑名单  false表示白名单
* Description :  
* Notice	   : 
*=================================================================*/
bool CSmartBlackMemoryOper::SMT_CheckBlackCard(int nCardNo)
{
	int nPostion,nMod=0;

	if( nCardNo>SAVEBLACKLISTTOTAL )	return true; //卡号大于SAVEBLACKLISTTOTAL(1百万)
	if( nCardNo<=0 )					return true; //卡号小于等于0
	
	nPostion=nCardNo/8;								//得到该卡在黑名单数组中位置的哪个字节
	nMod    =nCardNo%8;								//在该字节的位图
	
	if( nPostion==0 )
	{
		if( (g_SaveBlackList[nPostion]>>(8-nMod))&0x01 )
		{
			return true;
		}
	}
	else
	{
		if( nMod==0 )
		{
			nPostion--;
			if( g_SaveBlackList[nPostion]&0x01 )
			{
				return true;
			}
		}
		else
		{
			if( (g_SaveBlackList[nPostion]>>(8-nMod))&0x01 )
			{
				return true;
			}
		}
	}
	return false;
}

/*=================================================================
* Function ID :  SMT_InsertBlackCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示插入成功  false表示插入失败
* Description :  
* Notice	   :  
*=================================================================*/
bool CSmartBlackMemoryOper::SMT_InsertBlackCard(int nCardNo)
{
	int nPostion,nMod=0;

	if( nCardNo>SAVEBLACKLISTTOTAL )	return false; //卡号大于SAVEBLACKLISTTOTAL(1百万)
	if( nCardNo<=0 )					return false; //卡号小于等于0
	
	nPostion=nCardNo/8;					//得到该卡在黑名单数组中位置的哪个字节
	nMod    =nCardNo%8;					//在该字节的位图

	g_CriticalSectionLock.Lock();
	if( nPostion&&nMod==0 )
	{
		nPostion--;
		g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x01;
	}
	else
	{
		if( nMod==1 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x80;
		}
		else if( nMod==2 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x40;
		}
		else if( nMod==3 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x20;
		}
		else if( nMod==4 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x10;
		}
		else if( nMod==5 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x08;
		}
		else if( nMod==6 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x04;
		}
		else if( nMod==7 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x02;
		}
		else if( nMod==8 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]|0x01;
		}
	}
	g_CriticalSectionLock.Unlock();
	return true;
}

/*=================================================================
* Function ID :  SMT_DeleteBlackCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示删除成功  false表示删除失败
* Description :  
* Notice	   :  
*=================================================================*/
bool CSmartBlackMemoryOper::SMT_DeleteBlackCard(int nCardNo)
{
	int nPostion,nMod=0;

	if( nCardNo>SAVEBLACKLISTTOTAL )	return false; //卡号大于SAVEBLACKLISTTOTAL(1百万)
	if( nCardNo<=0 )					return false; //卡号小于等于0
	
	nPostion=nCardNo/8;			//得到该卡在黑名单数组中位置的哪个字节
	nMod    =nCardNo%8;			//在该字节的位图

	g_CriticalSectionLock.Lock();
	if( nPostion&&nMod==0 )
	{
		nPostion--;
		g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xFE;
	}
	else
	{
		if( nMod==1 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0x7F;
		}
		else if( nMod==2 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xBF;
		}
		else if( nMod==3 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xDF;
		}
		else if( nMod==4 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xEF;
		}
		else if( nMod==5 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xF7;
		}
		else if( nMod==6 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xFB;
		}
		else if( nMod==7 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xFD;
		}
		else if( nMod==8 )
		{
			g_SaveBlackList[nPostion]=g_SaveBlackList[nPostion]&0xFE;
		}
	}
	g_CriticalSectionLock.Unlock();
	return true;
}
