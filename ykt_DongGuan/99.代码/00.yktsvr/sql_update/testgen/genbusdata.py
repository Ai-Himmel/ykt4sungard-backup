#!/usr/bin/env python
#coding: cp936

import sys,os,datetime,codecs,struct
import fileinput,zipfile
import cx_Oracle
from bccclt import bccclt
import hashlib

BCD=1
INT=2
STR=3

class BusPOSGen:
    ''' 生成公交数据 '''
    SRC_DBNAME='YKT.DGYD.250'
    SRC_DBPWD='kingstar'
    SRC_DBUSER='ykt_cur'
    BUSPOSRECLEN=109
    UNITNO=190000101
    
    def __init__(self):
        self.recordFields = [('termno',STR,16),('termseqno',INT,0),('samno',STR,12),('samseqno',INT,0),
            ('cardasno',STR,16),('termdate',STR,8),('termtime',STR,6),('accreceivable',INT,0),('price',INT,0),
            ('amount',INT,0),('paycnt',INT,0),('cardbefbal',INT,0),('lockflag',INT,0),('grayflag',INT,0),
            ('tac',STR,8),('cardtype',INT,0)]
            
        self.connect=None
        self.cursor=None
        self.samno='00000000000000000033'
        os.environ["NLS_LANG"] = "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
        self.connect = cx_Oracle.Connection(BusPOSGen.SRC_DBUSER + "/" + BusPOSGen.SRC_DBPWD + "@" + BusPOSGen.SRC_DBNAME)
        self.cursor = self.connect.cursor()
        self.termseqno = 0
        self.samseqno = 0
        self.termno = '00000000130012AB'
        self.filehandle = None
        self.recordcnt=0
        self.paycntoffset=0
        self.currentdir=''
        self.merchantno='101000123'
        self.index = 1
        
    def getRecordName(self):
        current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        r = '%s%s%06d%06d' % (self.merchantno,current[:8],self.index,self.recordcnt)
        return r
        
    def execSQL(self,sql):
        try:
            self.cursor.execute(sql)
        except cx_Oracle.DatabaseError, exc:
            error, = exc.args
            print "写入数据库失败[ORA-%d][%s]" % (error.code,error.message)
            return False
        return True
        
    def querySQL(self,sql):
        rows=None
        try:
            rows = self.cursor.execute(sql)
        except cx_Oracle.DatabaseError, exc:
            error, = exc.args
            print "查询数据库失败[ORA-%d][%s]" % (error.code,error.message)
            return None
        return rows
    
    def int2Data(self,v,l):
        d = ''
        if l == 1:
            d = struct.pack('<I',v)[0]
        elif l == 2:
            d = struct.pack('<H',v)
        elif l == 3:
            d = struct.pack('<I',v)[:3]
        elif l == 4:
            d = struct.pack('<I',v)
        else:
            raise ValueError
        return d
    
    def record2Data(self,record):
        data=''
        
        for n,t,l in self.recordFields:
            v = record[n]
            try:
                if t == INT:
                    data += "%d," % v
                elif t == STR:
                    data += v + ","
            except:
                print n, " : value error :", t
                print record
                return False,''
                
        return True,data+'\n'
        
    
    def saveRecord(self,record):
        current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        record['termseqno'] = self.termseqno
        record['termno'] = self.termno
        record['cardtype'] = 0
        record['samno'] = self.samno
        record['samseqno'] = self.samseqno
        record['termdate'] = current[:8]
        record['termtime'] = current[8:]
        record['accreceivable'] = 0
        record['price'] = 0
        record['amount'] = 10
        record['lockflag'] = 0
        record['grayflag'] = 0
        record['tac'] = 'AB3F284F'
        r,data = self.record2Data(record)
        if not r:
            return False
        try:
            self.filehandle.write(data)
            self.filehandle.flush()
        except:
            print "write data file error"
            return False
            
        self.samseqno += 1
        self.termseqno += 1
        return True
        
    def doQueryCardInfo(self):
        sql = "select cardasno,cardbal,paycnt from t_card"
        print "查询卡数据..."
        rows = self.querySQL(sql)
        if not rows:
            return False
        print "开始生成数据..."
        self.recordcnt=0
        for row in rows:
            record={}
            record['cardasno']='00000000' + row[0]
            record['cardbefbal']=row[1]
            record['paycnt']=row[2]+self.paycntoffset
            if not self.saveRecord(record):
                return False
            self.recordcnt+=1
        print "success gen row[%d]" % self.recordcnt
        return True
        
    def doCheckDateDir(self,datedir):
        if os.path.exists(datedir):
            if not os.path.isdir(datedir):
                print "error!"
                return
        else:
            os.mkdir(datedir)
            
    def gendata(self):
        current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        self.currentdir=current[:8]
        self.doCheckDateDir(self.currentdir)
        tmpname='aabbccddeeff'
        try:
            self.filehandle = open(tmpname,'wb+')
        except:
            print "创建流水文件错误"
            return '',0
        self.doQueryCardInfo()
        self.filehandle.close()
        self.filehandle=None
        
        realname=self.getRecordName()
        print "record file[%s]" % realname
        f = os.path.join(self.currentdir,realname)
        os.rename(tmpname,f)
        return f,self.recordcnt

def calcZipMd5(zipname,md5file):
    md5 = hashlib.md5()
    ziphandle = open(zipname,'rb')
    while True:
        data = ziphandle.read(1024)
        if len(data) > 0:
            md5.update(data)
        
        if len(data) < 1024:
            break
    
    ziphandle.close()
    digest = md5.hexdigest()
    
    md5handle = open(md5file,'w+')
    md5handle.write(digest)
    md5handle.close()
    

def doWriteRecord(result):
    current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    datedir = current[:8]
    pkgname = '%012d%s' % (BusPOSGen.UNITNO,current)
    n = os.path.join(datedir,pkgname) + '.pkg'
    handle = None
    try:
        handle = open(n,'wb+')
        handle.write("%s,%d\n" % (current,len(result)))
        for a,b in result:
            handle.write("%s,%d\n" % (os.path.basename(a),b))
    except:
        print "gen pkg file error!"
        return
    handle.close()
    
    zipname = '%s.zip' % pkgname
    md5file = '%s.md5' % pkgname
    if os.path.exists(zipname):
        os.unlink(zipname)
    zip = zipfile.ZipFile(zipname,mode='w',compression=zipfile.ZIP_DEFLATED)
    os.chdir(datedir)
    n = os.path.basename(n)
    zip.write(n)
    for f,c in result:
        dst = os.path.basename(f)
        print "zip file %s ..." % dst
        zip.write(dst)
        os.unlink(dst)
    zip.close()
    os.unlink(n)
    os.chdir("..")
    calcZipMd5(zipname,md5file)
    
    
def doGenSomeRecord():
    gen = BusPOSGen()
    samnolist=['00000000000000000033','00000000000000000035','00000000000000000038']
    result=[]
    a = 0
    for sam in samnolist:
        gen.samno=sam
        gen.termseqno = 0
        gen.samseqno = 0
        gen.filehandle = None
        gen.recordcnt=0
        gen.paycntoffset=a
        gen.index = a + 1
        n,c = gen.gendata()
        if len(n) == 0:
            return
        result.append((n,c))
        a += 1
    
    print "generate pkg file..."
    doWriteRecord(result)
        
    
if __name__ == "__main__":
    doGenSomeRecord()
    