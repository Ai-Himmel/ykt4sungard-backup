#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform

class test_846405(unittest.TestCase):
    """交易收费配置"""
    def setUp(self):
        pass
	
    def tearDown(self):
        pass
        
    def testAddWaterFee(self):
        """ 添加费率 """
        obj = bccclt.new(common.MAINFUNC)
        
        v = {'semail':'费率1','lwithdraw_flag':2,'lserial0':0,'lvol10':3,'sstation0':'A','semp':'1000'}
        ret = obj.callsvr(846405,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        x = obj.getrecord(['lcert_code'])
        self.feeid = x['lcert_code']
        print x
        
        v = {'lcert_code':x['lcert_code'],'lvol11':10,'lvol12':1,'lvol0':0,'lvol1':10,'lvol2':1,'sstation0':'I','semp':'1000'}
        ret = obj.callsvr(846405,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
        v = {'lcert_code':x['lcert_code'],'lvol11':11,'lvol12':2,'lvol0':0,'lvol1':10,'lvol2':1,
        'lvol3':4,'lvol4':15,'lvol5':1,'sstation0':'I','semp':'1000'}
        ret = obj.callsvr(846405,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
        v = {'lcert_code':x['lcert_code'],'lvol11':12,'lvol12':3,'lvol0':0,'lvol1':10,'lvol2':1,
        'lvol3':4,'lvol4':15,'lvol5':1,'lvol6':8,'lvol7':20,'lvol8':1,'sstation0':'I','semp':'1000'}
        ret = obj.callsvr(846405,v,5000)
        self.failUnless(ret==0,obj.errmsg)
    
        v = {'lcert_code':self.feeid,'sstation0':'R','semp':'1000'}
        ret = obj.callsvr(846405,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
        recordcnt = 0
        while True:
            x = obj.getrecord(['lcert_code','semail','lserial0','lwithdraw_flag','lvol0','lvol1','lvol2',
            'lvol3','lvol4','lvol5','lvol6','lvol7','lvol8'])
            if x is None:
                break
            recordcnt = recordcnt + 1
            print x
        
        self.failUnless(recordcnt == 3,'费率数量不正确')
        
        v = {'lcert_code':self.feeid,'sstation0':'D','semp':'1000'}
        ret = obj.callsvr(846405,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
def suite():
    suites = ['testAddWaterFee']
    return unittest.TestSuite(map(test_846405,suites))
	
if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    unittest.main()
