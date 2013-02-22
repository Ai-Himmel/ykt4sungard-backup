// ListCtrlMap.cpp: implementation of the CListCtrlMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListCtrlMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PLISTCTRLMAP CListCtrlMap::m_pMap = NULL;

CListCtrlMap::CListCtrlMap()
{
}

CListCtrlMap::~CListCtrlMap()
{

}
//////////////////////////////////////////////////////////////////////
//插入
void CListCtrlMap::Insert(CListCtrl *pCtrl, CWnd *pWnd, int nIndex)
//////////////////////////////////////////////////////////////////////
{
	PLISTCTRLMAP pMap;
	pMap = GetCtrlMap(pCtrl);
	if(pMap == NULL)//新增
	{
 	  pMap = new LISTCTRLMAP;
	  if(pMap == NULL) return ;
      ZeroMemory(pMap,sizeof(LISTCTRLMAP));
	  InsertWnd(pMap, pWnd, nIndex);
	  pMap->pCtrl = pCtrl;
	  pMap->pNext = m_pMap;
	  m_pMap = pMap;
	}
	else //修改
	{
	  InsertWnd(pMap, pWnd, nIndex);
	}
}
//////////////////////////////////////////////////////////////////////
//删除
void CListCtrlMap::Delete(CListCtrl *pCtrl, CWnd *pWnd, int nIndex)
//////////////////////////////////////////////////////////////////////
{
	PLISTCTRLMAP pMap, pDel;
// 循环查找待删除节点的上一个节点
	if (m_pMap == NULL) return ;
//第1节
	if (m_pMap->pCtrl == pCtrl)
	{
  	  if (pWnd == NULL)
	  {
		  delete m_pMap;
	      m_pMap = NULL;
	  }
	  else
	  {
         DeleteWnd(m_pMap, nIndex);
	  }
	  return ;
	}
	for (pMap = m_pMap; pMap != NULL; pMap = pMap->pNext)
	{
		pDel = pMap->pNext;
		if  (pDel != NULL && pDel->pCtrl == pCtrl)
		{
			pMap->pNext = pDel->pNext;
			if (pWnd == NULL)
			{
			  delete pDel;
			}
			else
			{
			  DeleteWnd(pDel, nIndex);
			}
			break;
		}
	}
}
void CListCtrlMap::DeleteWnd(PLISTCTRLMAP pMap, int nIndex)
{
	if(pMap == NULL) return;
    if(nIndex >= 0 && nIndex < IT_MAX)
 	{
       pMap->szWnd[nIndex] = NULL;
 	}
}
void CListCtrlMap::InsertWnd(PLISTCTRLMAP pMap, CWnd *pWnd, int nIndex)
 {
	if(pMap == NULL) return;
    if(nIndex >= 0 && nIndex < IT_MAX)
 	{
       pMap->szWnd[nIndex] = pWnd;
 	}
 }

CWnd *CListCtrlMap::GetSubWnd(CListCtrl *pCtrl, int nSubItem)
{
	PLISTCTRLMAP pMap;
    if(nSubItem >= 0 && nSubItem < IT_MAX)
	{
      if(pCtrl == NULL) return NULL;
      pMap = GetCtrlMap(pCtrl);
	  if(pMap == NULL) return NULL;
	  return pMap->szWnd[nSubItem];
	}
	return NULL;
}

PLISTCTRLMAP CListCtrlMap::GetCtrlMap(CListCtrl *pCtrl)
{
   PLISTCTRLMAP pMap;
   if (pCtrl == NULL) return NULL;
//第1节
   for (pMap = m_pMap; pMap != NULL; pMap = pMap->pNext)
	{
		if  (pMap->pCtrl == pCtrl)
			return pMap;
	}
   return NULL;
}
