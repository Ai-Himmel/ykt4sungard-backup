#!/usr/bin/env python
#coding: cp936

import sys,os,datetime,codecs,struct
import fileinput,zipfile
import cx_Oracle
from bccclt import bccclt

BCD=1
HEX=2
STR=3

class BusPOSGen:
    ''' 生成公交数据 '''
    SRC_DBNAME='YKT.DGYD.VMWARE'
    SRC_DBPWD='kingstar'
    SRC_DBUSER='ykt_cur'
    BUSPOSRECLEN=109
    UNITNO=190000101
    
    def __init__(self):
        self.recordFields = [('transtype',HEX,2),('status',BCD,1),('termseqno',HEX,4),('citycode',BCD,2),
            ('cardasno',BCD,12),('cardtype',HEX,1),('prepsamno',BCD,10),('pretransdate',BCD,7),
            ('pretranstype',HEX,1),('preamount',HEX,3),('psamno',BCD,10),('psamseqno',HEX,4),('transdate',BCD,7),
            ('amount',HEX,3),('befbal',HEX,3),('paycnt',HEX,2),('jf',HEX,3),('opercardno',BCD,10),
            ('rfu1',BCD,2),('termno',BCD,8),('lineno',BCD,3),('lockflag',HEX,1),('rfu2',STR,6),('tac',STR,4)]
            
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
        
    def getRecordName(self):
        current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        r = '015700000000000000%s%s0001%05d' % (current,self.samno,self.recordcnt)
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
                if t == HEX:
                    data += self.int2Data(v,l)
                elif t == BCD:
                    if len(v) != l*2:
                        print "fields[%s]length must be[%d] but is[%s]" % (n,l*2,v)
                        return False,''
                    data += codecs.decode(v,'hex')
                elif t == STR:
                    if len(v) != l:
                        print "fields[%s]length must be[%d] but is[%s]" % (n,l,v)
                        return False,''
                    data += v
            except:
                print n, " : value error :", t
                print record
                return False,''
                
        if len(data) != BusPOSGen.BUSPOSRECLEN:
            print "gen data len must be[%d] but is [%d]" % (BusPOSGen.BUSPOSRECLEN,len(data))
            return False,''
        return True,data
        
    
    def saveRecord(self,record):
        current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        record['transtype'] = 2
        record['status'] = '00'
        record['termseqno'] = self.termseqno
        record['citycode'] = '0000'
        record['cardtype'] = 0
        record['prepsamno'] = '00000000000000000000'
        record['pretransdate'] = '00000000000000'
        record['pretranstype'] = 2
        record['preamount'] = 0
        record['psamno'] = self.samno
        record['psamseqno'] = self.samseqno
        record['transdate'] = current
        record['amount'] = 10
        record['jf'] = 0
        record['opercardno'] = '00000000000000000000'
        record['rfu1'] = '0000'
        record['termno'] = self.termno
        record['lineno'] = '000000'
        record['lockflag'] = 0
        record['rfu2'] = '000000'
        record['tac'] = '\xAB\x3F\x28\x4F'
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
            record['befbal']=row[1]
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
        filestat = os.stat(f)
        if filestat[6] != BusPOSGen.BUSPOSRECLEN * self.recordcnt:
            print "check file size error,real[%d] desire[%d]" % (filestat[6],BusPOSGen.BUSPOSRECLEN * self.recordcnt)
            return '',0
        return f,self.recordcnt


def doWriteRecord(result):
    current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    datedir = current[:8]
    n = '%012d%s.pkg' % (BusPOSGen.UNITNO,current)
    n = os.path.join(datedir,n)
    handle = None
    try:
        handle = open(n,'w+')
        handle.write("%s,%d\n" % (current,len(result)))
        for a,b in result:
            handle.write("%s,%d\n" % (os.path.basename(a),b))
    except:
        print "gen pkg file error!"
        return
    handle.close()
    
    zipname = os.path.join(datedir,'%s.zip' % datedir)
    zip = zipfile.ZipFile(zipname,mode='w',compression=zipfile.ZIP_DEFLATED)
    zip.write(n)
    for f,c in result:
        dst = f
        print "zip file %s ..." % f
        zip.write(dst)
        os.unlink(dst)
    zip.close()
    os.unlink(n)
    #os.rename(zipname,os.path.join(datedir,zipname))
    
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
        n,c = gen.gendata()
        if len(n) == 0:
            return
        result.append((n,c))
        a += 1
    
    print "generate pkg file..."
    doWriteRecord(result)
        
    
if __name__ == "__main__":
    doGenSomeRecord()
    