#ifndef MYSTRING_H
#define MYSTRING_H

#ifndef __cplusplus
#define __cplusplus
#endif


#include <time.h>
#include <string>
#include <vector>

using std::string;
//去掉所有的空格
string& trimall(string &str,string::size_type pos = 0);
//去除两端的空格字符
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
//获得<nodename>nodeval</nodename>的nodeval值
bool getNodeValByNodeName(string buf,string nodename,string& nodeval);
void appendNewXmlNode(string& xmlbuf,string nodename,string nodeval);
void appendNewXmlChildNodeLine(string& xmlbuf,string nodename,string nodeval);
void appendNewXmlParentNodeLine(string& xmlbuf,string nodename,string nodeval);

#endif