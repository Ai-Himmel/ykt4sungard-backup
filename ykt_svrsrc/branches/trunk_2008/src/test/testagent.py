#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform

class termGDTest (unittest.TestCase):
	""" 广州大学城仿新中兴接口测试用例 """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
		
	def testLogin(self):
		""" 测试前置机登录 """
		obj = bccclt.new(common.MAINFUNC)
		v = {
		'scust_limit':'10.49.188.13',
		'scust_limit2':'00-1C-23-4F-0E-C3',
		'scert_no':'sungard kingstar gateway common version'
		}
		ret = obj.callsvr(950001,v)
		self.failUnless(ret==0,obj.errmsg)
		
		x = obj.getrecord(['lvol0','scust_limit'])
		
		v = {
		'lvol0':x['lvol0'],
		'scust_limit':x['scust_limit']
		}
		
		ret = obj.callsvr(950002,v)
		self.failUnless(ret==0,obj.errmsg)
		
		y = obj.getrecord(['lvol0','lvol1','lvol2','lvol3','lvol4',
		'lvol5','lvol6','lvol7','lvol8','lvol9','sname','sname2'])
		print y
		self.failUnless(y['lvol3']>0,'parameter error')
		self.failUnless(y['lvol9']>0,'parameter error')
	
	def testDownloadDevice(self):
		pass
		
	
	
def suite():
	suites = ['testLogin']
	return unittest.TestSuite(map(termGDTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)
	
