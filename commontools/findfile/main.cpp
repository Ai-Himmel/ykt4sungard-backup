#include <windows.h>
#include <stdio.h>
#include <assert.h>
/********************************************************************
*   created:	2004/03/20
*   filename: 	main.cpp
*   author:		cash
*   version:	0.1
*   $Id: main.cpp 17 2004-03-23 19:55:49Z cash $
*
*   purpose:	查找指定路径下的指定文件
*********************************************************************/

#define FILE_FILTER_MAX_LEN 15
#define FILE_FILTER_MAX_COUNT 10

#define TO_UPPER(c) (((c) >= 'a' && (c) <= 'z') ? ((c) - 32): (c))

bool gRecursiveSearch;
bool gUnixFormat;
bool gIgnoreCase;
char gPrintFormat[40];
char FileFilter[FILE_FILTER_MAX_COUNT][FILE_FILTER_MAX_LEN];

void Usage();
void SearchFileInDir(const char * dir);
bool MatchFileName(const char * filename);
bool MatchFileName(const char * filename , const char * filter);

void OutPutFile(const char * filename,WIN32_FIND_DATA * wData);

int main(int argc , char * * argv)
{
    gRecursiveSearch = true;
    char dir[MAX_PATH];
    strcpy(gPrintFormat,"%s\n");
    // default all files
    strcpy(FileFilter[0],"*.*");
    // default windows path format
    gUnixFormat = false;
    // default is case-sensitive
    gIgnoreCase = false;
    if( argc < 3)
    {
        Usage();
        exit(1);
    }
    int i = 1;
    for(;i < argc ; ++i)
    {
        if( strcmp(argv[i],"-u") == 0 )
        {
            gUnixFormat = true;
        }
        else if( strcmp(argv[i],"-w") == 0 )
        {
            gUnixFormat = false;
        }
        else if( strcmp(argv[i],"-i") == 0 )
        {
            gIgnoreCase = true;
        }
        else
        {
            strcpy(dir,argv[i]);
            ++i;    
            for(int j = 0;i < argc;++i,++j)
            {
                strcpy(FileFilter[j],argv[i]);
            }
        }
    }
    SearchFileInDir(dir);
    return 0;
}

void Usage()
{
    printf("Find file utils by Cash Tang 2004\n");
    printf("Usage : \n");
    printf("findfile [options...] dir filter...\n");
    printf("\t-u : output unix path such as /usr/lib\n");
    printf("\t-w : output windows path such as c:\\windows\n");
    printf("\t-i : Ignore case of filter,default is case-sensitive\n");
    printf("Example : findfile -u . *.cpp\n");
}

void SearchFileInDir(const char * dir)
{
    WIN32_FIND_DATA data;
    HANDLE hFile;
    int len = strlen(dir) + 10;
    char * buf = new char[len];
    // 查找目录下的文件
    memset(buf,0,len);
    strcpy(buf,dir);
    strcat(buf,"\\*.*");
    hFile = FindFirstFile(buf,&data);
    bool bSearch = true;
    if( hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    char filename[MAX_PATH + FILENAME_MAX + 1];
    while(bSearch)
    {
        memset(filename,0,MAX_PATH + FILENAME_MAX);
        strcpy(filename,dir);
        strcat(filename,"\\");
        strcat(filename,data.cFileName);
        DWORD Att = GetFileAttributes(filename);
        if( (Att & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            if(gRecursiveSearch &&
                strcmp(data.cFileName,".") != 0 && 
                strcmp(data.cFileName,"..") != 0 )
            {
                SearchFileInDir(filename);
            }
        }
        else if(MatchFileName(data.cFileName))
        {
            OutPutFile(filename,&data);
        }      
        if(!FindNextFile(hFile,&data))
        {
            if( GetLastError() == ERROR_NO_MORE_FILES )
               bSearch = false;
            else
            {
                printf("Error : cannot file in dir[%s]\n",dir);
                break;
            }
        }
    }
    FindClose(hFile);
    delete buf;
}
bool MatchFileName(const char * filename , const char * filter)
{
    int pos = 0;
    char c = filter[pos++];
    const char * f = filename;
    int flag = 0;
    while(c != '\0')
    {
        // upper case character
        char u = TO_UPPER(c);
        switch(c)
        {
        case '*':
            flag = 1;
            break;
        case '?':
            if(*f == '\0')
                return true;
            ++f;
            break;
        default:
            if(flag == 1)
            {
                char t = *f;
                while((*f != c) 
                    && (!gIgnoreCase || *f != u) 
                    && (*f != '\0')) ++f;
                if( *f == '\0')
                    return false;
                ++f;
                flag = 0;
            }
            else
            {
                if(((*f != c) && (!gIgnoreCase || *f != u)) || (*f == '\0'))
                    return false;
                ++f;
            }
            break;
        }
        c = filter[pos++];
    }
    if( flag != 0 || *f == '\0')
        return true;
    return false;
}

bool MatchFileName(const char * filename)
{
    for(int i = 0; i < FILE_FILTER_MAX_COUNT && FileFilter[i][0] != '\0'; ++i)
    {
        if(MatchFileName(filename,FileFilter[i]))
            return true;
    }
    return false;
}

void OutPutFile(const char * filename,WIN32_FIND_DATA * wData)
{
    char tmp[MAX_PATH + FILENAME_MAX + 1];
    assert(wData != NULL);
    if(gUnixFormat)
    {
        int i = 0;
        while(filename[i] != '\0')
        {
            if(filename[i] == '\\')
                tmp[i] = '/';
            else
                tmp[i] = filename[i];
            ++i;
        }
        tmp[i] = '\0';
        fprintf(stdout,gPrintFormat,tmp);
    }
    else
    {
        fprintf(stdout,gPrintFormat,filename);
    }
}