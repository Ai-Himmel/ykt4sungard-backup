#!/usr/bin/env python
# vim: tabstop=4: expandtab
# daming buspos parser
# command busposparse.py pkgfile

import os,sys,codecs
import fileinput,struct
from zipfile import *
from datetime import datetime,timedelta

BCD=1
INT=2
STR=3
BFS_INIT='I'
#UNITNO=190000101

class RecordFileReader20101230:
    def __init__(self):
        self.recordFields=[('termno',STR,16),('termseqno',INT,0),('samcardno',INT,0),('samno',STR,12),('samseqno',INT,0),
            ('cardasno',STR,16),('termdate',STR,8),('termtime',STR,6),('accreceivable',INT,0),('price',INT,0),
            ('amount',INT,0),('paycnt',INT,0),('cardbefbal',INT,0),('lockflag',INT,0),('grayflag',INT,0),
            ('tac',STR,8),('cardtype',INT,0)]
            
    def getRecordFields(self):
        return self.recordFields
    
    def parseRecord(self,dbflds,record,parser):
        dbflds.append(('fileid',':fileid'))
        dbflds.append(('hostdate',':hostdate'))
        dbflds.append(('hosttime',':hosttime'))
        dbflds.append(('merchid',parser.marchantno))
        dbflds.append(('posno',record['termno']))
        dbflds.append(('samno',record['samno']))
        dbflds.append(('samseqno',record['samseqno']))
        dbflds.append(('cardasno',record['cardasno']))
        dbflds.append(('cardtype',record['cardtype']))
        dbflds.append(('termdate',int(record['termdate'])))
        dbflds.append(('termtime',int(record['termtime'])))
        dbflds.append(('lockflag',record['lockflag']))
        dbflds.append(('transtype',record['grayflag']))
        dbflds.append(('cardcnt',record['paycnt']))
        dbflds.append(('amount',record['amount']))
        dbflds.append(('befcardbal',record['cardbefbal']))
        dbflds.append(('tac',record['tac']))
        dbflds.append(('accdate',0))
        dbflds.append(('status',BFS_INIT))
        dbflds.append(('errcode',0))
        return True
        
class RecordFileReader20110215:
    def __init__(self):
        self.recordFields=[('termno',STR,16),('termseqno',INT,0),('samcardno',INT,0),('samno',STR,12),('samseqno',INT,0),
            ('cardasno',STR,16),('termdate',STR,8),('termtime',STR,6),('accreceivable',INT,0),('price',INT,0),
            ('amount',INT,0),('paycnt',INT,0),('cardbefbal',INT,0),('lockflag',INT,0),('grayflag',INT,0),
            ('tac',STR,8),('cardtype',INT,0),('presamno',STR,12),('pretermdate',STR,8),('pretermtime',STR,6),
            ('prepaycnt',INT,0),('preamount',INT,0),('pretranstype',INT,0)]
            
    def getRecordFields(self):
        return self.recordFields
    
    def parseRecord(self,dbflds,record,parser):
        dbflds.append(('fileid',':fileid'))
        dbflds.append(('hostdate',':hostdate'))
        dbflds.append(('hosttime',':hosttime'))
        dbflds.append(('merchid',parser.marchantno))
        dbflds.append(('posno',record['termno']))
        dbflds.append(('samno',record['samno']))
        dbflds.append(('samseqno',record['samseqno']))
        dbflds.append(('cardasno',record['cardasno']))
        dbflds.append(('cardtype',record['cardtype']))
        dbflds.append(('termdate',int(record['termdate'])))
        dbflds.append(('termtime',int(record['termtime'])))
        dbflds.append(('lockflag',record['lockflag']))
        dbflds.append(('transtype',record['grayflag']))
        dbflds.append(('cardcnt',record['paycnt']))
        dbflds.append(('amount',record['amount']))
        dbflds.append(('befcardbal',record['cardbefbal']))
        dbflds.append(('tac',record['tac']))
        dbflds.append(('accdate',0))
        dbflds.append(('status',BFS_INIT))
        dbflds.append(('errcode',0))
        dbflds.append(('lasttermsno',record['presamno']))
        dbflds.append(('lasttermdate',record['pretermdate']))
        dbflds.append(('lasttermtime',record['pretermtime']))
        dbflds.append(('lasttranstype',record['pretranstype']))
        dbflds.append(('lastamount',record['preamount']))
        return True

class BusPOSParser:
    BUSPOSRECLEN=109
    UNITNOLEN=9
    MERCHANTNOLEN=9
    def __init__(self):
        self._reset()
        
    def _reset(self):
        ''' reset all parameters '''
        self.pkgfile = ''
        self.pkgdir = ''
        self.pkgTimestamp = ''
        self.recordCount = 0
        self.marchantno = ''
        self.recordFiles = []
        self.SQLFile = ''
        self.SQLHandle = None
        self.recordReaders={20101230:RecordFileReader20101230(),
            20110215:RecordFileReader20110215()}
            
        self.recordNames = None
        self.recordDefDict = {}
        self.record = None
        self.totalRecord = 0
        self.unitno=0
        self.versionnum=0
        
    def faildExit(self,msg):
        ''' exit with exit_code 1 and print error message to stdout'''
        print "Faild : %s" % msg
        sys.exit(1)
        
    def parseFile(self,filepath):
        ''' parse bus pos record file '''
        pass
        
    def parseAllFile(self,files):
        ''' parse bus pos record file one by one '''
        for f in files:
            self.parseFile(f)
            
    def _readPkgHead(self,head):
        ''' parse bus pos pkg file header line '''
        head = head.strip()
        flds = head.split(',')
        if len(flds) < 2:
            return False
        self.pkgTimestamp = flds[0]
        self.recordCount = int(flds[1])
        # 增加了流水文件版本号的参数
        if len(flds) >= 3 and len(flds[2]) > 0:
            self.versionnum = int(flds[2])
        else:
            self.versionnum = 20101230 # 此处为默认版本号
        return True
        
    def _checkRecordFile(self,record):
        ''' check record file '''
        flds = record.split(',')
        if len(flds) != 2:
            return False
        rec = (flds[0],int(flds[1]))
        fullpath = os.path.join(self.pkgdir,rec[0])
        if os.path.isfile(fullpath):
            self.recordFiles.append(rec)
            return True
        return False
        
        
    def _genHeadSQL(self):
        ''' generate head sql '''
        line = "UPDPKG :PKGNO='%s',CITYCODE=0,UNITNO=%09d,RECVDATE=:hostdate,RECVTIME=:hosttime,FILENUM=%d WHERE PKGID=:pkgid\n" \
            % (os.path.basename(self.pkgfile),self.unitno,self.recordCount)
        try:
            self.SQLHandle.write(line)
            self.SQLHandle.flush()
        except:
            return -1
        return 0
            
            
    def _data2Record(self,data,rec):
        ''' record binary data to struct '''
        begin = 0
        flds = data.split(',')
        for i in range(len(self.recordNames)):
            n = self.recordNames[i]
            v = flds[i]
            t,l = self.recordDefDict[n]
            v1 = None
            if t == STR:
                v1 = v
            elif t == INT:
                v1 = v
            else:
                self.faildExit('not support type field[%s]' % x)
            rec[n] = v1
        return True 
                    
        
    def _parseRecordFile(self,handle,cnt):
        i = 0
        if not self.recordReaders.has_key(self.versionnum):
            return -5
        reader = self.recordReaders[self.versionnum]
        while i < cnt:
            #print "deal[%d/%d]row" % (i ,cnt)
            recData = handle.readline().strip()
            record = {}
            self._data2Record(recData,record)
            #print record
            dbFld2Record=[]
            dbFld2Record.append(('rowno',i+1))
            if not reader.parseRecord(dbFld2Record,record,self):
                return -6
            
            t = 0
            fldclause='INSREC :('
            valclause='VALUES('
            for f,p in dbFld2Record:
                if t == 0:
                    fldclause = '%s %s' % (fldclause,f)
                    valclause = '%s %s' % (valclause,p)
                    t = 1
                else:
                    fldclause = '%s ,%s' % (fldclause,f)
                    if isinstance(p,int):
                        valclause = '%s ,%d' % (valclause,p)
                    elif isinstance(p,str):
                        if p[0] == ':':
                            valclause = "%s ,%s" % (valclause,p)
                        else:
                            valclause = "%s ,'%s'" % (valclause,p)
                    else:
                        valclause = "%s ,'%s'" % (valclause,p)
            
            fldclause = fldclause + ')'
            valclause = valclause + ')\n'
            line = fldclause + valclause
            try:
                self.SQLHandle.write(line)
            except:
                return -4
            i = i + 1
        self.totalRecord = self.totalRecord + cnt
        return 0
        
    def _genRecordSQL(self):
        seqno = 0
        for rec in self.recordFiles:
            handle = None
            reccnt = 0
            try:
                fullpath = os.path.join(self.pkgdir,rec[0])
                self.marchantno = rec[0][:BusPOSParser.MERCHANTNOLEN]
                filestat = os.stat(fullpath)
                reccnt = rec[1]
                handle = open(fullpath,'rb')
            except:
                return -1,'open file error [%s]' % rec[0]
                
            line = "INSPKGFILE :(FILEID,FILENAME,TOTALNUM,PKGID,SEQNO,STATUS)VALUES(:fileid,'%s',%d,:pkgid,:seqno,'%s')\n" \
                % (rec[0],reccnt,BFS_INIT)
            try:
                self.SQLHandle.write(line)
                self.SQLHandle.flush()
            except:
                return -1,'parse file error [%s]' % rec[0]
                
            if self._parseRecordFile(handle,reccnt) != 0:
                return -2,'parse file error [%s]' % rec[0]
            seqno = seqno + 1
            handle.close()
            try:
                self.SQLHandle.write("ENDPKGFILE :\n")
                self.SQLHandle.flush()
            except:
                return -1,'parse file error [%s]' % rec[0]
        return 0,'Success'   
        
    def _genSQL(self):
        ''' 生成 SQL 语句'''
        fname = os.path.basename(self.pkgfile)
        sqlfile = os.path.join(self.pkgdir,'%s.sql' % fname)
        try:
            self.SQLHandle = open(sqlfile,'w+')
        except:
            return -3,'create sql file'
            
        rc = self._genHeadSQL()
        if rc != 0:
            self.SQLHandle.close()
            return rc,'pkg file [%s] error' % (self.pkgfile)
        rc,m = self._genRecordSQL()
        if rc != 0:
            self.SQLHandle.close()
            return rc,m
        self.SQLHandle.close()
        self.SQLFile = sqlfile
        return 0,'Success'
        
    def _makeStructDef(self):
        '''   '''
        if not self.recordReaders.has_key(self.versionnum):
            return False
        fmtstr='<'
        flds = []
        defdict = {}
        reader = self.recordReaders[self.versionnum]
        defs = reader.getRecordFields()
        for n,t,l in defs:
            flds.append(n)
            defdict[n] = (t,l)
        self.recordDefDict = defdict
        self.recordNames = flds
        return True
        
    def _checkPkgFile(self):
        ''' 分析包裹单名称 '''
        fname = os.path.basename(self.pkgfile)
        self.unitno=int(fname[:BusPOSParser.UNITNOLEN])
        self.pkgTimestamp = fname[BusPOSParser.UNITNOLEN:]
        
    def _finishRemoveFile(self,pkgfile):
        ''' 删除中间文件 '''
        dstdir = os.path.dirname(pkgfile)
        for rec in self.recordFiles:
            dstfile = os.path.join(dstdir,rec[0])
            os.unlink(dstfile)
        os.unlink(pkgfile)
        #print "unlink pkg zip " , self._getFileNameWithExt(pkgfile,'.zip')
        os.unlink(self._getFileNameWithExt(pkgfile,'.zip'))
        #print "unlink pkg md5 ", self._getMD5FileName(pkgfile)
        os.unlink(self._getMD5FileName(pkgfile))
        
    def _getMD5FileName(self,tarfile):
        return self._getFileNameWithExt(tarfile,'.md5')
        
    def _getFileNameWithExt(self,fname,ext):
        dstdir = os.path.dirname(fname)
        tarname = os.path.basename(fname)
        base = os.path.splitext(tarname)[0]
        newname = os.path.join(dstdir,base+ext)
        return newname
            
    def parseFromPkg(self,pkgfile):
        ''' parse all bus record from pkg file '''
        beginTime = datetime.now()
        self.pkgfile = pkgfile
        self.pkgdir = os.path.dirname(self.pkgfile)
        if not os.path.isfile(self.pkgfile):
            self.faildExit("pkg file [%s] is not exists" % pkgfile)
        self._checkPkgFile()
        
        lineno = 1
        for line in fileinput.input(pkgfile):
            if lineno == 1:
                if not self._readPkgHead(line): # 分析包裹单文件头
                    self.faildExit("pkg head format error")
            elif lineno - 1 <= self.recordCount :
                if len(line) == 0: continue
                if not self._checkRecordFile(line): # 检查文件是否存在
                    self.faildExit("record file[%s] not exists or size error" % line)
            else: break
            lineno = lineno + 1
            
        if len(self.recordFiles) != self.recordCount:
            self.faildExit("pkg file list not match real files")
        
        fileinput.close()
        self._makeStructDef()
            
            
        r,m = self._genSQL() # 生成SQL 文件
        if r != 0:
            self.faildExit(m)
        self._finishRemoveFile(pkgfile)
        delta = datetime.now() - beginTime
        total = delta.seconds + delta.microseconds / 1000000.0
        print "Success : [%s] total[%d] time[%.2f]second" % (self.SQLFile,self.totalRecord,total)
        
    def _checkMd5(self,tarfile):
        ''' 验证 MD5 '''
        md5file = self._getMD5FileName(tarfile)
        if not os.path.exists(md5file):
            print "md5 file not exists[%s]" % md5file
            return False
        
        m = None
        if sys.hexversion >= 0x02050000:
            import hashlib
            m = hashlib.md5()
        else:
            import md5
            m = md5.md5()
        tarhandle = open(tarfile,'rb')
        while True:
            data = tarhandle.read(1024)
            if len(data) > 0:
                m.update(data)
            if len(data)<1024:
                break
        tarhandle.close()
        digest = m.hexdigest().upper()
        md5fileDigest = ''
        for line in fileinput.input(md5file):
            md5fileDigest = line.upper().strip()
            break
        fileinput.close()
        if digest == md5fileDigest[:32]:
            return True
        print "digest[%s][%s]" % (digest ,md5fileDigest)
        return False
        
    def parseFromTar(self,tarfile):
        ''' 从压缩包中解压文件 '''
        if not self._checkMd5(tarfile):
            print "check md5 error"
            return
            
        dstdir = os.path.dirname(tarfile)
        zip = ZipFile(tarfile,'r',ZIP_DEFLATED)
        fileinfo = zip.infolist()
        for x in fileinfo:
            fname = os.path.join(dstdir,x.filename)
            outfile = open(fname,'w+b')
            outfile.write(zip.read(x.filename))
            outfile.close()
        
        zip.close()
        
        files = os.listdir(dstdir)
        for x in files:
            ext = os.path.splitext(x)[1]
            if ext.lower() == '.pkg':
                full = os.path.join(dstdir,x)
                self.parseFromPkg(full)
        
        
if __name__ == "__main__":
    parser = BusPOSParser()
    if len(sys.argv) != 2:
        print "command error!"
        print "busposparse.py pkgfile"
        sys.exit(1)
    dir=os.path.dirname(sys.argv[0])
    if len(dir) > 0:
        os.chdir(dir)
    parser.parseFromTar(sys.argv[1])
        
