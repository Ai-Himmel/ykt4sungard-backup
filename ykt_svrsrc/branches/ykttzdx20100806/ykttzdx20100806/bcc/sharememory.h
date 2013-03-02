// ShareMemory.h: interface for the CShareMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREMEMORY_H__19AB4B9E_8F4A_4992_81DC_48A1F9514E65__INCLUDED_)
#define AFX_SHAREMEMORY_H__19AB4B9E_8F4A_4992_81DC_48A1F9514E65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define SHM_SHARE_MMU 0

class CShareMemory  
{
public:
	void setshname(char *shmname);
	key_t myftok(char *path,int ID);
	int gethandle(char *memoryname);
	int closeshare(const void *shmaddr);
	void showinfo(char *memoryname=NULL);
	void deleteshare(char *memoryname=NULL);
	void *openshare(char *memoryname,int buffersize,void * shmaddr,int flag=SHM_SHARE_MMU);
	CShareMemory();
	virtual ~CShareMemory();
private:
	char m_memoryname[80];
	int  m_shmid;
};

#endif // !defined(AFX_SHAREMEMORY_H__19AB4B9E_8F4A_4992_81DC_48A1F9514E65__INCLUDED_)
