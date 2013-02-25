/********************************************************
	处理以字符分割数据的类函数实现文件
	文件名: slist.cpp
	说明: 包含处理以字符分割数据的类函数实现。
	创建:
	修改: 吴卫文 2001-04-03
	修改原因: 规范编码
**********************************************************/
#include "slist.h"

CSList::CSList() {
    m_count=0;
    strcpy(m_separator,"\0");
}

CSList::~CSList() {
    m_lst.clear();
}

bool CSList::Add(char *buffer) {
    string str=buffer;
    m_lst.push_back(str);
    m_count++;
    return true;
}

char * CSList::GetAt(int nIndex) { // Index start 0
    if(nIndex<0 || nIndex>=m_count) return (char*)" ";
    STRINGLIST::iterator plist;
    plist=m_lst.begin();
    for(int i=0; i<nIndex; i++) plist++;
    return (char*)plist->c_str();
}

void CSList::SetAt(char *buffer,int nIndex) {
    if(nIndex<0 || nIndex>=m_count) return;
    STRINGLIST::iterator plist;
    plist=m_lst.begin();
    for(int i=0; i<nIndex; i++)
        plist++;
    string str=buffer;
    m_lst.insert(plist,str);
    m_lst.erase(plist);
}

int CSList::GetCount() {
    return m_count;
}

void CSList::Clear() {
    m_count=0;
    m_lst.clear();
}

int CSList::GetBuff(char *buffer,bool trimflag) {
    int ii=0;
    try {
        if(buffer!=NULL) *(buffer)=0;
        else return 0;
        STRINGLIST::iterator plist;
        for(plist=m_lst.begin(); plist!=m_lst.end(); plist++) {
            if(trimflag) {
                char buf[4096];
                memset(buf,0,sizeof(buf));
                strcpy(buf,(char*)plist->c_str());
                strcat(buffer,trim(buf));
            } else strcat(buffer,plist->c_str());
            strcat(buffer,m_separator);
        }
        ii=strlen(buffer);
        *(buffer+ii-1)='\0';
    } catch(...) {
        strcpy(buffer,"R|||N|CSList 类GetBuff 系统异常");
    }
    return ii;
}

bool CSList::FillStrings(char *mainstring,char separator) {
    int i,j;
    char strTemp[MAXCOLUMN];
    memset(strTemp,0,sizeof(strTemp));
    int strLen=strlen(mainstring);
    j=0;
    Clear();
    m_separator[0]=separator;
    m_separator[1]='\0';

    for(i=0; i<strLen; i++) {
        if(*(mainstring+i)==separator) {
            if((i-j)>0) {
                memset(strTemp,0,sizeof(strTemp));
                /* ****** Updated by CHENYH at 2006-7-5 11:29:07 ******
                   memcpy(strTemp,mainstring+j,(i-j));
                   strTemp[i-j]='\0';
                *******************************************************/
                memcpy(strTemp,mainstring+j,(i-j)>=sizeof(strTemp)?sizeof(strTemp)-1:(i-j));
            } else strcpy(strTemp," ");
            j=i+1;
            /* ****** Updated by CHENYH at 2006-7-5 16:37:43 ******
              if(strlen(strTemp)>MAXCOLUMN)
            {
               strTemp[MAXCOLUMN]='\0';
            }
            *******************************************************/
            if(!Add(strTemp)) return false;
        }
    }
    if(i>j) {
        memcpy(strTemp,mainstring+j,(i-j));
        strTemp[i-j]='\0';
        j=i+1;
        if(!Add(strTemp)) return false;
    } else if(i==j) {
        strcpy(strTemp," ");
        if(!Add(strTemp)) return false;
    }
    return true;
}

char * CSList::trim(char *s) {
    int i,len;
    if(s==NULL) return s;
    len=strlen(s);
    for (i=len-1; i>=0; i--) {
        if ((s[i] != ' ') && (s[i] != '\t'))
            break;
        else
            s[i]=0;
    }
    for (i=0; i<len; i++) {
        if ((s[i] != ' ') && (s[i] != '\t'))
            break;
    }
    if (i != 0) {
        strncpy(s,s+i,len-i);
        s[len-i]=0;
    }
    return s;
}

