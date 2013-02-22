#ifndef MYSTRING_H
#define MYSTRING_H

#ifndef __cplusplus
#define __cplusplus
#endif


#include <time.h>
#include <string>
#include <vector>

using std::string;
//ȥ�����еĿո�
string& trimall(string &str,string::size_type pos = 0);
//ȥ�����˵Ŀո��ַ�
string& trim(string &str);
void string_replace(string & strBig, const string & strsrc, const string &strdst);
string ltos(long l);
string ltohex(long l);
string dtos(double l);
string lpad(string& str,int padlen,unsigned char padchar);
char* lpad(char *str,int padlen,unsigned char padchar); 
//basename
void dirname(char *path,char *dir);
char *basename(char *path);
//���<nodename>nodeval</nodename>��nodevalֵ
bool getNodeValByNodeName(string buf,string nodename,string& nodeval);
void appendNewXmlNode(string& xmlbuf,string nodename,string nodeval);
void appendNewXmlChildNodeLine(string& xmlbuf,string nodename,string nodeval);
void appendNewXmlParentNodeLine(string& xmlbuf,string nodename,string nodeval);

#endif