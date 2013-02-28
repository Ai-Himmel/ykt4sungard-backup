#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class subsidy(unittest.TestCase):
    """站点管理"""
    def setUp(self):
        pass

    def tearDown(self):
        pass
    def testDownloadSubsidy(self):
        """ 下载补助 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "semp":"system",
            "sstatus0":"A",
            "scust_limit":"wenjian测试站点",
            "sphone":"192.168.113.1"
        }
        ret = obj.callsvr(849007,v)
        self.failUnless(ret==0,obj.errmsg)
    def testGetSubsidy(self):
        """ 领取补助 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "lvol0":292214,
            "lvol3":0,
            "lvol5":380547
        }
        ret = obj.callsvr(849006,v)
        self.failUnless(ret==0,obj.errmsg)

    
    
		
def suite():
    suites = ['testDownloadSubsidy']
    return unittest.TestSuite(map(paymentTest,suites))
	
if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    unittest.main()
