#!/usr/bin/env python
#coding: cp936

import sys,os,datetime,codecs
import fileinput
import cx_Oracle
from bccclt import bccclt
import chkpfmnc


class CustInfoGen:
    ''' 生成用户数据 '''
    SRC_DBNAME='YKT.DGYD.250'
    SRC_DBPWD='kingstar'
    SRC_DBUSER='ykt_cur'
    MAINFUNC=8000
    SVRIP='10.49.188.100'
    SVRPORT=4000
    
    def __init__(self):
        self.connect=None
        self.cursor=None
        self.custidlist=[]
        self.opercode='1000'
        self.computerip='10.49.188.13'
        self.samno='000000000033'
        os.environ["NLS_LANG"] = "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
        self.connect = cx_Oracle.Connection(CustInfoGen.SRC_DBUSER + "/" + CustInfoGen.SRC_DBPWD + "@" + CustInfoGen.SRC_DBNAME)
        self.cursor = self.connect.cursor()
        
    def doGenCardId(self,custid,idx):
        areacode=('10','12','13','14','15')
        i = idx % 5
        code = '%s%07d' % (areacode[i],custid)
        return int(code)

    def doInsertIntoDB(self,sql):
        try:
            self.cursor.execute(sql)
        except cx_Oracle.DatabaseError, exc:
            error, = exc.args
            print "写入数据库失败[ORA-%d][%s]" % (error.code,error.message)
            return False
        return True
        
    def doGenCustSQL(self,flds):
        insclause = 'INSERT INTO T_CUSTOMER ( '
        valueclause = ' VALUES ('
        i = 0
        for f in flds.keys():
            v = flds[f]
            if i == 0:
                insclause = '%s%s' % (insclause,f)
            else:
                insclause = '%s, %s' % (insclause,f)
            
            v1 = v
            if isinstance(v,(str)):
                v1 = "'%s'" % v1
            
            if i == 0:
                valueclause = '%s%s' % (valueclause,v1)
            else:
                valueclause = '%s, %s' % (valueclause,v1)
            
            i += 1
            
        sqlline = insclause + ') ' + valueclause + ')'
        return self.doInsertIntoDB(sqlline)
        
        
    def doGenUserCard(self):
        print "正在生成客户信息..."
        lineno = 0
        for line in fileinput.input('custtest.csv'):
            lineno += 1
            if lineno == 1:
                continue
            if lineno >= 100:
                return True
            line = line.strip()
            flds = line.split(',')
            if len(flds[0]) == 0:
                continue
            v = {}
            v['CUSTID']=int(flds[0])
            cardno=self.doGenCardId(int(flds[0]),lineno)
            v['CARDNO']=cardno
            v['CARDID']=int(flds[0])
            v['CARDTYPE']=1
            v['ISSUEUNIT']=cardno/10000000
            v['APPLYSTATUS']='1'
            v['PREPAIDAMT']=4000
            v['CUSTNAME']=flds[1]
            v['IDTYPE']='10'
            v['IDNO']=flds[3]
            v['SEX']=flds[4]
            v['DELFLAG']=0
            if not self.doGenCustSQL(v):
                return False
            #print "增加客户信息custid[%d]" % v['CUSTID']
            self.custidlist.append(v['CUSTID'])
        return True

    def doLogin(self,bcc):
        #scust_no=1000
        #scust_limit=03DEF051098BDC1B
        #sphone=10.253.42.88
        #sphone2=001C234F0EC3
        #sholder_type2=B
        #sstatus2=0
        #sstatus3=1
        #sserial2=0
        #lvol12=0
        #sserial3=200
        #scard1=00-1C-23-4F-0E-C3
        #13:41:45 FuncNo=8000,RequestType=820351
        v = {
        "scust_no":self.opercode,
        "scust_limit":"03DEF051098BDC1B",
        "sphone":self.computerip,
        "sphone2":"001C234F0EC3",
        "sholder_type2":"B",
        "sstatus2":"0",
        "sstatus3":"1",
        "sserial2":"0",
        "lvol12":0,
        "sserial3":"200",
        "scard1":"00-1C-23-4F-0E-C3"
        }
        ret = bcc.callsvr(820351,v,3000)
        if ret != 0:
            print "签到失败,ret[%d][%s]",(ret,bcc.errmsg)
            return False
        return True
        
    def doPayCard(self):
        bcc = bccclt.new(CustInfoGen.MAINFUNC)
        if not self.doLogin(bcc):
            return False
        rpt = chkpfmnc.CheckPerf()
        rpt.startchk()
        for custid in self.custidlist:
            current = datetime.datetime.now().strftime('%Y%m%d%H%M%S')
            v = {
            'lvol0':custid,
            'damt0':40.0,
            'snote':self.samno,
            'sdate0':current[:8],
            'stime0':current[8:],
            'semp':self.opercode,
            'sstat_type':'F'
            }
            print "正在缴费客户号[%d]..." % custid
            ret = 0
            ret = bcc.callsvr(2001,v,3000)
            if ret != 0:
                print "卡缴费失败custid[%d],ret[%d][%s]" % (custid,ret,bcc.errmsg)
                return False
            rpt.setchkpoint()
        print rpt.report()
        return True
            
    def dogen(self):
        if bccclt.init(CustInfoGen.SVRIP,CustInfoGen.SVRPORT,0,'cpack.dat') <> 0:
            print "init bccclt error"
            return
        a = raw_input("是否删除原始客户表数据(Y/n) :")
        if a in ('Y','y') or a == '' :
            print "删除原始数据..."
            self.doInsertIntoDB("delete from t_customer")
            self.doInsertIntoDB("delete from t_card")
            self.doInsertIntoDB("delete from t_carddtl")
            self.connect.commit()
            

        if not self.doGenUserCard():
            self.connect.rollback()
            return
        print "提交数据库..."
        self.connect.commit()
        print "正在卡缴费..."
        self.doPayCard()
        print "缴费完成"

if __name__ == "__main__":
    rpt = chkpfmnc.CheckPerf()
    gen = CustInfoGen()
    gen.dogen()