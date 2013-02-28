#!/usr/bin/python
# -*- coding: cp936 -*-
# vim: tabstop=4: expandtab

import os,sys,shutil,zipfile
from datetime import datetime
import cx_Oracle

class BusPOSResult:
    ''' 生成反馈文件 '''

    def __init__(self):
        os.environ["NLS_LANG"] = "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
        self.dbname=''
        self.dbuser=''
        self.dbpwd=''
        self.connect = None
        self.__getDBCfg()
        self.cursor = self.connect.cursor()
        self.pkgid = 0
        self.pkgfileName=''
        self.pkgNo=''
        self.basedir=''
        self.recordFiles=[]
        self.recordResults=[]

    def __getDBCfg(self):
        self.dbname=os.environ['YKT_DBNAME']
        self.dbuser=os.environ['YKT_USER']
        self.dbpwd=os.environ['YKT_PWD']
        try:
            self.connect = cx_Oracle.Connection(self.dbuser + "/" + self.dbpwd + "@" + self.dbname)
        except cx_Oracle.DatabaseError, exc:
            print "连接数据库失败 :" , self.__parseOraExpt(exc)
            raise exc


    def __parseOraExpt(self,exception):
        error, = exception.args
        return "[ORA-%d][%s]" % (error.code,error.message.strip())
    
    def __execSQL(self,sql):
        try:
            self.cursor.execute(sql)
        except cx_Oracle.DatabaseError, exc:
            print "执行语句失败 :", self.__parseOraExpt(exc)
            return False
        return True 

    def __querySQL(self,sql):
        rows = None
        try:
            rows = self.cursor.execute(sql)
        except cx_Oracle.DatabaseError, exc:
            print "查询数据库失败 :", self.__parseOraExpt(exc)
            return None
        return rows 

    def __genPkgFileName(self):
        sql = 'select pkgfilename from t_pkg where pkgid=%d' % self.pkgid
        rows = self.__querySQL(sql)
        r = rows.fetchone()
        if not r :
            print "pkgid[%d] not exists" % self.pkgid
            return False

        fname = r[0]
        ext = os.path.splitext(fname)[1]
        if ext.lower() != '.zip':
            print "pkg file name is not zip"
            return False
        self.pkgfileName = fname
        self.pkgNo=os.path.splitext(fname)[0] + '.pkg'
        return True

    def __checkTempDir(self,tmpdir):
        if os.path.exists(tmpdir):
            if os.path.isdir(tmpdir):
                self.__clearTemp(tmpdir)
            else:
                print "Temp[%s] is not directory" % tmpdir
                return False
        r = os.mkdir(tmpdir)
        if not r:
            return True
        print "Create temp[%s] error" % tmpdir
        return False

    def __clearTemp(self,tmpdir):
        if os.path.exists(tmpdir):
            #print "remove temp directory"
            shutil.rmtree(tmpdir)


    def __genPkgFile(self,tmpdir):
        pkgNoFile=os.path.join(tmpdir,self.pkgNo)
        #print "pkg no [%s]" % pkgNoFile
        current = datetime.now().strftime('%Y%m%d%H%M%S')
        handle = open(pkgNoFile,'w+b')
        line = '%s,%s,%d\n' % (self.pkgNo,current,len(self.recordFiles))
        handle.write(line)
        for x in self.recordResults:
            line = '%s,%d,%d,%d,%d\n' % (x[0],x[1],x[2],x[3],x[4])
            handle.write(line)
        handle.flush()
        handle.close()
        return True

    def __genResultFiles(self,tmpdir):
        sql = 'select fileid,filename,totalnum from t_pkgfile where pkgid=%d' % self.pkgid
        pkgfiles=[]
        rows = self.__querySQL(sql)
        while True:
            r = rows.fetchone()
            if not r:
                break
            pkgfiles.append(r)

        for f in pkgfiles:
            if not self.__genFile(f,tmpdir):
                print "Gen File error,[%s]" % f[1]
                return False

        return True 


    def __genDataLine(self,fld):
        line=''
        for f in fld:
            if isinstance(f,int):
                line += '%d,' % f  
            elif isinstance(f,str):
                if f == 'None':
                    line += ','
                else:
                    line += '%s,' % f
            elif isinstance(f,float):
                line += '%f,' % f
            else:
                print "Error Data Type , " , f
                return ""
        if len(line)>0:
            line += '\n'
        return line

    def __genFileData(self,filedef,handle):
        successcnt=0
        successmoney=0
        faildcnt=0
        faildmoney=0
        sql = "select posno,'None','None',samno,samseqno,cardasno,termdate,lpad(to_char(termtime),6,'0'),'None','None',\
                amount,cardcnt,befcardbal,lockflag,0,tac,cardtype,errcode \
                from t_posdtl where fileid=%d" % filedef[0]
        rows = self.__querySQL(sql)
        while True:
            r = rows.fetchone()
            if not r:
                break
            line = self.__genDataLine(r)
            if len(line)>0:
                handle.write(line)
                errcode=r[17]
                if errcode == 0:
                    successcnt += 1
                    successmoney += r[10]
                else:
                    faildcnt += 1
                    faildmoney += r[10]
        handle.flush()
        return True,(filedef[1],successcnt,successmoney,faildcnt,faildmoney)

    def __genFile(self,filedef,tmpdir):
        #print "gen file [%s]" % filedef[1]
        filefullname=os.path.join(tmpdir,filedef[1])
        if os.path.exists(filefullname):
            if not os.unlink(filefullname):
                print "file [%s] exists,cannot been deleted" % filedef[1]
                return False
        handle = open(filefullname,'w+b')
        r,f = self.__genFileData(filedef,handle)
        if not r:
            return False
        handle.close()
        self.recordFiles.append(filefullname)
        self.recordResults.append(f)
        return True

    def __makeZip(self,tmpdir):
        zipfilename = os.path.join(self.basedir,self.pkgfileName)
        if os.path.exists(zipfilename):
            os.unlink(zipfilename)
        zip = zipfile.ZipFile(zipfilename,mode='w',compression=zipfile.ZIP_DEFLATED)
        #print "write zip file " , zipfilename
        os.chdir(tmpdir)
        for f in self.recordFiles:
            fn = os.path.basename(f)
            zip.write(fn)
        
        zip.write(self.pkgNo)
        zip.close()
        os.chdir('..')
        return True
        
    def genResult(self,pkgid):
        if isinstance(pkgid,str):
            self.pkgid = int(pkgid)
        else:
            self.pkgid = pkgid

        if not self.__genPkgFileName():
            return False
        
        tmpdir = os.path.join(self.basedir,'dtltemp%d' % self.pkgid)
        if not self.__checkTempDir(tmpdir):
            return False 
        
        r = self.__genResultFiles(tmpdir)
        if r:
            r = self.__genPkgFile(tmpdir)
            if r:
                r = self.__makeZip(tmpdir)
        
        self.__clearTemp(tmpdir)
        if r:
            print "Success generate [%s]" % self.pkgfileName 
        else:
            print "Failed generate ",self.pkgfileName
        return r


if __name__ == "__main__":
    pos = BusPOSResult()
    pos.basedir = os.path.dirname(sys.argv[0])
    pkgid = ""
    if len(sys.argv) < 2:
        pkgid = raw_input("please enter pkg id :")
        if len(pkgid) == 0:
            print "error input"
            sys.exit(1)
    
    else:
        pkgid = sys.argv[1]
    pos.genResult(pkgid)

