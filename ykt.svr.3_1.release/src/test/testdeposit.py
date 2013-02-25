#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class depositTest (unittest.TestCase):
	""" 充值测试 """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
		
	def testDeposit(self):
		"""柜面充值"""
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"lwithdraw_flag":127,
			"semp":common.OPERCODE,
			"lvol5":common.TERMID,
			"semp":"3000",
			"stime2":"235959",
			"sdate1":"20090101",
			"sdate2":"20501010",
			"lvol0":59,
			"sstation0":"261E6466",
			"lvol6":4,
			"lvol7":12400,
			"lvol9":1,
			"damt0":amount,
		}
		ret = obj.callsvr(846312,v)
		self.failUnless(ret==0,obj.errmsg)
def suite():
	suites = ['testDeposit']
	return unittest.TestSuite(map(paymentTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	unittest.main()
