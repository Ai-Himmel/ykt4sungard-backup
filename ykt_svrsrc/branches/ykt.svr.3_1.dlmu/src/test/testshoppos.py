#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class paymentTest (unittest.TestCase):
	""" 第三方支付测试用例 """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
		
	def testShopPosAdd(self):
		"""设备商户分配"""
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"lwithdraw_flag":127,
			"semp":common.OPERCODE,
			"sstatus0":"A",
			"lvol0":0,
			"lvol3":19,
			"lvol5":common.TERMID,
			"stime2":"235959",
			"sdate1":"20090101",
			"sdate2":"20501010",
		}
		ret = obj.callsvr(843371,v)
		self.failUnless(ret==0,obj.errmsg)
def suite():
	suites = ['testShopPosAdd']
	return unittest.TestSuite(map(paymentTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	unittest.main()
