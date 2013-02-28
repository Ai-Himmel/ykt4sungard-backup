#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class CalcMAC(unittest.TestCase):
    """计算MAC"""
    def setUp(self):
        pass
    def tearDown(self):
        pass
    def testOnlineMac(self):
        """ 计算MAC """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "sdate0":'20101028',
            "stime0":'112345',
            "lvol1":19680,
            "lvol6":9,
            "lvol7":100520,
            "sstock_code":'E1DA5FE2',
            "semp":'1001',
            "sserial0":'000000000001',
            "sstation1":'217F12A280000000'
        }
        ret = obj.callsvr(846313,v)
        self.failUnless(ret==0,obj.errmsg)

        x = obj.getrecord(['sstock_code2'])
        self.failUnless('C6097175'==x['sstock_code2'],'Mac计算错误')
        
    def testOnlineMacWithMac1(self):
        """ 计算MAC2 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "sdate0":'20101028',
            "stime0":'122005',
            "lvol1":19680,
            "lvol6":12,
            "lvol7":159560,
            "sstock_code":'932712A3',
            "sstock_code2":'2C7DB987',
            "semp":'1001',
            "sserial0":'000000000001',
            "sstation1":'217F12A280000000'
        }
        ret = obj.callsvr(846313,v)
        self.failUnless(ret==0,obj.errmsg)

        x = obj.getrecord(['sstock_code2'])
        self.failUnless('B9277FC6'==x['sstock_code2'],'Mac计算错误')
        
    def testOnlineMacWithMac2(self):
        """ 计算MAC2 """
        obj = bccclt.new(common.MAINFUNC)
        v = {
            "sdate0":'20101028',
            "stime0":'122005',
            "lvol1":19680,
            "lvol6":12,
            "lvol7":159560,
            "sstock_code":'932712A3',
            "sstock_code2":'2C7DB987',
            "semp":'1001',
            "sserial0":'000000000001',
            "sstation1":'217F12A280000000'
        }
        ret = obj.callsvr(846313,v)
        self.failUnless(ret==0,obj.errmsg)

        x = obj.getrecord(['sstock_code2'])
        self.failUnless('B9277FC6'==x['sstock_code2'],'Mac计算错误')
	
def suite():
    suites = ['testOnlineMac']
    return unittest.TestSuite(map(paymentTest,suites))
	
if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    unittest.main()
