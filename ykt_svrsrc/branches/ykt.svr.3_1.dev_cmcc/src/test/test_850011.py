#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform

class test_850011(unittest.TestCase):
    """�����շ�����"""
    def setUp(self):
        pass
	
    def tearDown(self):
        pass
        
    def _testPay(self):
        """ ��������ˮ���� """
        obj = bccclt.new(common.MAINFUNC)
        
        v = {'lvol0':7,'semp':'1000','lvol1':5000,'lvol2':39,'sphone':'0022100807','sdate0':'20100825','stime0':'150301',
        'sstation0':'D19EE170','lvol3':39}
        ret = obj.callsvr(850011,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        x = obj.getrecord(['lvol0','lvol4','lvol5','damt0','sdate0','stime0'])
        #print x
        self.failUnless(x['lvol4']==30,'���׽���ȷ')
        self.failUnless(x['lvol5']==5000-30,'��������ȷ')
        self.failUnless(x['damt0']==(5000-30)/100.0,'��������ȷ')
        
        
    def _testPayUnlock(self):
        """ ���Բ��貹�� """
        obj = bccclt.new(common.MAINFUNC)
        
        v = {'lvol0':7,'semp':'1000','lvol1':5000,'lvol2':40,'sphone':'0022100807','sdate0':'20100825','stime0':'150301',
        'sstation0':'D19EE170','lvol3':39}
        ret = obj.callsvr(850011,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        x = obj.getrecord(['lvol0','lvol4','lvol5','damt0','sdate0','stime0'])
        #print x
        self.failUnless(x['lvol4']==0,'���׽���ȷ')
        self.failUnless(x['lvol5']==5000,'��������ȷ')
        self.failUnless(x['damt0']==5000/100.0,'��������ȷ')
        
    def testPayWithSerial(self):
        """ ��������ˮ���� """
        obj = bccclt.new(common.MAINFUNC)
        
        v = {'lvol0':7,'semp':'1000','lvol1':97501,'lvol2':45,'sphone':'0022100807','sdate0':'20100826','stime0':'193152',
        'sstation0':'D19EE170','lvol3':45}
        ret = obj.callsvr(850011,v,5000)
        self.failUnless(ret==0,obj.errmsg)
        x = obj.getrecord(['lvol0','lvol4','lvol5','damt0','sdate0','stime0'])
        print x
        self.failUnless(x['lvol4']==20,'���׽���ȷ')
        self.failUnless(x['lvol5']==5000-20,'��������ȷ')
        self.failUnless(x['damt0']==(5000-30)/100.0,'��������ȷ')
        
def suite():
    suites = ['testPay','testPayUnlock','testPayWithSerial']
    return unittest.TestSuite(map(test_850011,suites))
	
if __name__ == "__main__":
    if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
        print "init bccclt error"
    unittest.main()
