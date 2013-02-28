#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os,datetime
from distutils.util import get_platform


class testBUBank(unittest.TestCase):
    """圈存前置测试"""
    svrid=0
    dynkey=''
    batchno=0
    refno=''
    samno='000000000024'
    samseqno=0
    randomnum='346778C7'
    befbal=0
    transdate='20101218'
    transtime='001852'
    cardasno='1103000000000054' # 3114000000000014 ,  , 000000002301D146
    dpscnt=1
    amount=19680
    mac1='4657D754'
    def setUp(self):
        pass

    def tearDown(self):
        pass
        
    def testLogin(self):
        """ 圈存前置机签到 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "scust_limit":"192.168.56.3",
            "scust_auth":"00-22-15-50-94-BF",
            "scust_auth2":"86435D353079A787"
        }
        ret = obj.callsvr(50001,v)
        self.failUnless(ret==0,obj.errmsg)	
        x = obj.getrecord(['scust_limit','lserial0','lwithdraw_flag'])
        testBUBank.svrid=x['lwithdraw_flag']
        testBUBank.dynkey=x['scust_limit']
        testBUBank.batchno=x['lserial0']
        print x
        
    def testInitForLoad(self):
        """ 圈存初始化 """
        d = datetime.datetime.now()
        current = d.strftime("%Y%m%d%H%M%S")
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "scust_limit":testBUBank.dynkey,
            "lcert_code":testBUBank.batchno,
            "lwithdraw_flag":testBUBank.svrid,
            "sholder_ac_no":testBUBank.samno,
            "lserial0":testBUBank.samseqno,
            "scust_auth":testBUBank.cardasno,
            "lvol2":testBUBank.befbal,
            "lvol1":testBUBank.dpscnt,
            "lvol0":testBUBank.amount,
            "sdate1":"20110505",
            "sdate0":current[:8],
            "stime0":current[8:],
            "sname":"",
            "sbank_acc":"6225881204373798"
        }
        ret = obj.callsvr(50002,v)
        self.failUnless(ret==0,obj.errmsg)	
        x = obj.getrecord(['sphone'])
        testBUBank.refno=x['sphone']
        print x
        
    def testDebitForLoad(self):
        """ 测试圈存确认 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "scust_limit":testBUBank.dynkey,
            "lcert_code":testBUBank.batchno,
            "lwithdraw_flag":testBUBank.svrid,
            "scust_auth2":testBUBank.randomnum,
            "lvol1":testBUBank.dpscnt,
            "lvol0":testBUBank.befbal,
            "scust_limit2":"20110505000001",
            "sname":"",
            "sphone":testBUBank.refno,
            "sbank_acc":"6225881204373798",
            "sholder_ac_no2":testBUBank.mac1
        }
        ret = obj.callsvr(50003,v,5000)
        self.failUnless(ret==0,obj.errmsg)	
        x = obj.getrecord(['sphone','scust_auth2'])
        print x

    def testQueryTrans(self):
        ''' 测试圈存流水查询 '''
        obj = bccclt.new(common.MAINFUNC)
        v = {
        "scust_limit":testBUBank.dynkey,
        "lcert_code":testBUBank.batchno,
        "lwithdraw_flag":testBUBank.svrid,
        "sdate0":'20110101',
        'sdate1':'20110218',
        "scust_auth":testBUBank.cardasno
        }
        ret = obj.callsvr(50101,v,5000)
        self.failUnless(ret==0,obj.errmsg)	
        x = obj.getrecord(['sphone','scust_auth2'])
        print x
        

def suite():
    suites = ['testLogin','testInitForLoad','testDebitForLoad','testQueryTrans']
    return unittest.TestSuite(map(testBUBank,suites))

if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    unittest.TextTestRunner(verbosity=2).run(suite())

