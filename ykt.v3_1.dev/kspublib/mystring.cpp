#include "mystring.h"
#include <stdio.h>
#include <string.h>

using std::string;
//去掉所有的空格
string& trimall(string &str,string::size_type pos) {
    static const string delim = " \t\n"; //删除空格或者tab字符
    pos = str.find_first_of(delim, pos);
    if (pos == string::npos)
        return str;
    return trimall(str.erase(pos, 1));
}
//去除两端的空格字符
string& trim(string &str) {
    const string &delim =" \t\n" ;
    str=str.erase(str.find_last_not_of(delim)+1);
    str=str.erase(0,str.find_first_not_of(delim));
    return str;
}
// inline string ltos(long l)
// {
// 	char a[20];
// 	sprintf(a, "%ld", l);
// 	return string(a);
// }
void string_replace(string & strBig, const string & strsrc, const string &strdst) {
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    while( (pos=strBig.find(strsrc, pos)) != string::npos) {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}
string ltos(long l) {
    char a[20];
    sprintf(a, "%ld", l);
    return string(a);
}
string ltohex(long l) {
    char a[20];
    if(l<256)
        sprintf(a, "%02X", (int)l);
    else
        sprintf(a, "%X", (int)l);
    return string(a);
}
string dtos(double l) {
    char a[32];
    sprintf(a, "%.2lf", l);
    return string(a);
}
string lpad(string& str,int padlen,unsigned char padchar) {
    int iLen = padlen - str.length();
    if(iLen <= 0)
        return str;
    str.insert(0,iLen,padchar);
    return str;
}
char* lpad(char *str,int padlen,unsigned char padchar) {
    int iLen = padlen - strlen(str);
    if(iLen <= 0)
        return str;
    memmove(str+iLen,str,strlen(str));
    memset(str,padchar,iLen);
    return str;
}
//basename
void dirname(char *path,char *dir) {
    char *s1;
    char *s2;
    char *basename;
    s1=strrchr(path, '/');
    s2=strrchr(path, '\\');

    if(s1 && s2) {
        basename = (s1 > s2? s1 : s2)+1;
    } else if(s1)
        basename = s1 + 1;
    else if(s2)
        basename = s2 + 1;
    else {
        strcpy(dir,"");
        return ;
    }
    strncpy(dir,path,basename-path);
    dir[basename-path]=0;
}
char *basename(char *path) {
    char *s1;
    char *s2;

    s1=strrchr(path, '/');
    s2=strrchr(path, '\\');

    if(s1 && s2) {
        path = (s1 > s2? s1 : s2)+1;
    } else if(s1)
        path = s1 + 1;
    else if(s2)
        path = s2 + 1;

    return path;
}
//获得<nodename>nodeval</nodename>的nodeval值
bool getNodeValByNodeName(string buf,string nodename,string& nodeval) {
    string::size_type pos;
    string nodeNameHead,nodeNameTail;
    nodeval="";
    nodeNameHead="<";
    nodeNameHead+=nodename;
    nodeNameHead+=">";

    nodeNameTail="</";
    nodeNameTail+=nodename;
    nodeNameTail+=">";
    pos=buf.find(nodeNameHead);
    if(pos!= string::npos) {
        buf=buf.erase(0,pos+nodeNameHead.size());
    } else
        return false;

    pos=buf.find(nodeNameTail);
    if(pos!= string::npos) {
        nodeval=buf.erase(pos);
    } else
        return false;
    trim(nodeval);
    return  true;
}
void appendNewXmlNode(string& xmlbuf,string nodename,string nodeval) {
    xmlbuf.append("<");
    xmlbuf.append(nodename);
    xmlbuf.append(">");
    xmlbuf.append(nodeval);
    xmlbuf.append("</");
    xmlbuf.append(nodename);
    xmlbuf.append(">");
}
void appendNewXmlChildNodeLine(string& xmlbuf,string nodename,string nodeval) {
    xmlbuf.append("\t");
    appendNewXmlNode(xmlbuf,nodename,nodeval);
    xmlbuf.append("\n");
}
void appendNewXmlParentNodeLine(string& xmlbuf,string nodename,string nodeval) {
    xmlbuf.append("<");
    xmlbuf.append(nodename);
    xmlbuf.append(">");
    xmlbuf.append("\n");
    xmlbuf.append(nodeval);
    xmlbuf.append("</");
    xmlbuf.append(nodename);
    xmlbuf.append(">");
    xmlbuf.append("\n");
}
