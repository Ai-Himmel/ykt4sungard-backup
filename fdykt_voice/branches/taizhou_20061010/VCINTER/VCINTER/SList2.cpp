// SList.cpp: implementation of the CSList class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

char *ltrim(char *str)
{ 	char *p=str;
	if (strlen(str)==0) return str;
	while (*p==' '||*p=='\t'||*p=='\r'||*p=='\n') p++;
	strcpy(str,p);
	return str;
}

char *rtrim(char *str)
{ 	char *p=&str[strlen(str)-1];
	if (strlen(str)==0) return str;
	int i;
	for (i=strlen(str)-1;i>=0;i--)
	if (str[i]!=' ' && str[i]!='\t' && str[i]!='\r' && str[i]!='\n') break;
	str[i+1]=0;
	return str;
}

char *trim(char* in)
{
	return rtrim(ltrim(in));
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSList::CSList()
{
	Clear();
}

CSList::~CSList()
{
	Clear();
}

bool CSList::Add(char *buffer)
{
	string str=buffer;
	m_lst.push_back(str);
	m_count++;
	return true;
}

char * CSList::GetAt(int nIndex)
{
	if(nIndex<0 || nIndex>=m_count) return (char*)" "; 
	STRINGLIST::iterator plist;
	plist=m_lst.begin();
	for(int i=0;i<nIndex;i++) plist++;
	return (char*)plist->c_str();
}

void CSList::SetAt(char *buffer,int nIndex)
{
	if(nIndex<0 || nIndex>=m_count) return;
	STRINGLIST::iterator plist;
	plist=m_lst.begin();
	for(int i=0;i<nIndex;i++) plist++;
	string str=buffer;
	m_lst.insert(plist,str);
	m_lst.erase(plist);
}

int CSList::GetCount()
{
	return m_count;
}

void CSList::Clear()
{
	m_count=0;
	m_lst.clear();
}

int CSList::GetBuff(char *buffer,bool trimflag)
{
	int ii=0;
	try
	{
		if(buffer!=NULL) *(buffer)=0;
		else return 0;
		STRINGLIST::iterator plist;
		for(plist=m_lst.begin();plist!=m_lst.end();plist++)
		{
			if(trimflag)
			{
				char buf[MAXCOLUMN];
				memset(buf,0,sizeof(buf));
				strcpy(buf,(char*)plist->c_str());
				trim(buf);
				if (buf[0])
					strcat(buffer,trim(buf));
				else
					strcat(buffer," ");
			}
			else strcat(buffer,plist->c_str());
			strcat(buffer,"|");
		}
		ii=strlen(buffer);
		*(buffer+ii-1)='\0';//将末尾的'|'去除
	}catch(...)
	{
		strcpy(buffer,"R| | |N|CSList 类GetBuff 系统异常");
	}
	return ii;
}

bool CSList::FillStrings(const char *mainstring)
{
	int i,j,k;
	char strTemp[MAXCOLUMN];
	int strLen=strlen(mainstring);
	
	j=0;Clear();
	for(i=0;i<strLen;i++)
	{
		if(*(mainstring+i)=='|')
		{
			k=i-j;
			if(k>0)
			{
				if (k>MAXCOLUMN-1) k=MAXCOLUMN-1;
				memset(strTemp,0,sizeof(strTemp));
				memcpy(strTemp,mainstring+j,k);
			}
			else strcpy(strTemp," ");
		   
			j=i+1;
			if(!Add(strTemp)) return false;
		}
	}

	k=i-j;
	if(k>0)
	{
		if (k>MAXCOLUMN-1) k=MAXCOLUMN-1;
		memset(strTemp,0,sizeof(strTemp));
		memcpy(strTemp,mainstring+j,k);
		if(!Add(strTemp)) return false;
	}
	else if(k==0)
	{
		strcpy(strTemp," ");
		if(!Add(strTemp)) return false;
	}
   
	return true;
}
