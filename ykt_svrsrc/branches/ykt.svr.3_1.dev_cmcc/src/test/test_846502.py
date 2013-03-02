#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform

class test_846502(unittest.TestCase):
    """交易收费配置"""
    def setUp(self):
        pass
	
    def tearDown(self):
        pass
        
    def testCfgFeeAdd(self):
        """ 添加收费参数 """
        obj = bccclt.new(common.MAINFUNC)
        
        v = {'lvol0': 3000, 'lvol1': 602, 'lvol2': 1, 'lvol3': 0, 'lvol5': 12, 'lsafe_level': 1, 
        'sbranch_code0': '0', 'damt0': 8.0, 'sstatus0': 'D', 'sstation0': '001C234F0EC3', 'semp': '1000',
        'lvol7':10}
        ret = obj.callsvr(846502,v,5000)
        #self.failUnless(ret==0,obj.errmsg)
        
        v = {'lvol0': 3000, 'lvol1': 602, 'lvol2': 1, 'lvol3': 0, 'lvol5': 12, 'lsafe_level': 1, 
        'sbranch_code0': '0', 'damt0': 8.0, 'sstatus0': 'A', 'sstation0': '001C234F0EC3', 'semp': '1000',
        'lvol7':10}
        ret = obj.callsvr(846502,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
        v = {'lvol0': 3000, 'lvol1': 602, 'lvol2': 1, 'lvol3': 0, 'lvol5': 12, 'lsafe_level': 1, 
        'sbranch_code0': '0', 'damt0': 8.0, 'sstatus0': 'D', 'sstation0': '001C234F0EC3', 'semp': '1000',
        'lvol7':30}
        ret = obj.callsvr(846502,v,5000)
        #self.failUnless(ret==0,obj.errmsg)
        
        v = {'lvol0': 3000, 'lvol1': 602, 'lvol2': 1, 'lvol3': 0, 'lvol5': 12, 'lsafe_level': 1, 
        'sbranch_code0': '0', 'damt0': 8.0, 'sstatus0': 'A', 'sstation0': '001C234F0EC3', 'semp': '1000',
        'lvol7':30}
        ret = obj.callsvr(846502,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
    def _testCfgFeeDel(self):
        """ 删除收费参数 """
        obj = bccclt.new(common.MAINFUNC)
        v = {'lvol0': 3000, 'lvol1': 602, 'lvol2': 1, 'lvol3': 0, 'lvol5': 12, 'lsafe_level': 1, 
        'sbranch_code0': '0', 'damt0': 8.0, 'sstatus0': 'D', 'sstation0': '001C234F0EC3', 'semp': '1000',
        'lvol7':10}
        ret = obj.callsvr(846502,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        
def suite():
    suites = ['testCfgFeeDel','testCfgFeeAdd']
    return unittest.TestSuite(map(test_846502,suites))
	
if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    unittest.main()
