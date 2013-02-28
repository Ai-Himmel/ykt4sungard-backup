#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from datetime import datetime
from distutils.util import get_platform

class dpsPOSTest(unittest.TestCase):
    """ POS充值测试 """
    opercode=''
    batchno=0
    authcode=0
    def setUp(self):
        pass
	
    def tearDown(self):
        pass
		
    def testPOSLogin(self):
        """ 测试充值签到功能 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
        'sphone3':'0181100706',
        'sstation0':'000000000015',
        'lvol0':12,
        'stx_pwd':'666666',
        }
        ret = obj.callsvr(950070,v,1000) 
        self.failUnless(ret==0,obj.errmsg)
        self.failUnless(obj.recordcnt==1,'no record')
        x = obj.getrecord(['lcert_code','sphone3','lvol0','lwithdraw_flag','semp_no','sname','lvol1',
            'lvol2','lvol3','lvol4','sdate3','stime3','sholder_ac_no','lvol5']) 
        print x
        msg = '后台返回[%d]' % x['lcert_code']
        self.failUnless(x['lcert_code']==0,msg)
        dpsPOSTest.opercode=x['semp_no']
        dpsPOSTest.batchno=x['lvol1']
        dpsPOSTest.authcode=x['lvol2']
        
    def testPOSAdd(self):
        """ 测试充值流程 """
        obj = bccclt.new(common.MAINFUNC)
        current = datetime.today().strftime('%Y%m%d%H%M%S')
        v = {
        'sphone3':'0181100706',
        'lwithdraw_flag':0,
        'lserial0':123,
        'sstation0':'0000000015',
        'lvol10':12,
        'lvol1':dpsPOSTest.batchno,
        'lvol2':dpsPOSTest.authcode,
        'semp_no':dpsPOSTest.opercode,
        'lvol4':12,
        'lvol7':30870,
        'lvol8':100,
        'lvol5':4,
        'sdate0':current[:8],
        'stime0':current[8:],
        'stx_pwd':'666666',
        }
        ret = obj.callsvr(950072,v,1000) 
        self.failUnless(ret==0,obj.errmsg)
        self.failUnless(obj.recordcnt==1,'no record')
        x = obj.getrecord(['lcert_code','lbank_acc_type','sdate3','stime3','sstock_code2','sphone3','lserial0',
            'scust_auth','lvol4','lvol7','lvol8','lvol10']) 
        print x
        msg = '后台返回[%d]' % x['lcert_code']
        self.failUnless(x['lcert_code']==0,msg)
        
    def testPOSReverse(self):
        """ 测试充值冲正 """
        obj = bccclt.new(common.MAINFUNC)
        current = datetime.today().strftime('%Y%m%d%H%M%S')
        v = {
        'sphone3':'0181100706',
        'lwithdraw_flag':0,
        'lserial0':124,
        'sstation0':'0000000015',
        'lvol10':12,
        'lvol1':dpsPOSTest.batchno,
        'lvol2':dpsPOSTest.authcode,
        'semp_no':dpsPOSTest.opercode,
        'lvol4':12,
        'lvol7':30870,
        'lvol8':100,
        'lvol5':4,
        'sdate0':current[:8],
        'stime0':current[8:]
        }
        ret = obj.callsvr(950073,v,1000) 
        self.failUnless(ret==0,obj.errmsg)
        self.failUnless(obj.recordcnt==1,'no record')
        x = obj.getrecord(['lcert_code','lbank_acc_type','sdate3','stime3','sstock_code2','sphone3','lserial0',
            'scust_auth','lvol4','lvol7','lvol8','lvol10']) 
        print x
        msg = '后台返回[%d]' % x['lcert_code']
        self.failUnless(x['lcert_code']==0,msg)

def suite():
    suites = ['testPOSLogin','testPOSAdd','testPOSReverse']
    return unittest.TestSuite(map(dpsPOSTest,suites))
	
if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    #runner = unittest.TextTestRunner(verbosity=2)
    #unittest.main(testRunner=runner)
    unittest.TextTestRunner(verbosity=2).run(suite())
