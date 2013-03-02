#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class voucherTest (unittest.TestCase):
	""" 凭证管理 """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
	""" 凭证录入 """	
	def testVoucherMake(self):
		""" 测试凭证录入功能 """
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"sstatus0":"A",
			"lsafe_level":11,
			"lwithdraw_flag":common.TERMID,
			"semp":"1000",
			"sorder0":"20100815",
			"lvol0":2,
			"snote":"退款",
			"lbank_acc_type":5,
			"lvol9":2,
			"sname2":"14525678",
			"scust_auth":"220201",
			"damt1":500,
			"damt2":0,
			"damt3":0,
			"damt4":500,			
			"snote2":"退款",
			"scust_auth2":"1001",
			
		}
		ret = obj.callsvr(850050,v)
		self.failUnless(ret==0,obj.errmsg)
		self.failUnless(obj.recordcnt==1,'no record')
		x = obj.getrecord(["lserial1","lserial0","lsafe_level"])
		#self.assertEqual(x["lvol8"],9900,'incorrect aftbala')
		#self.assertEqual(x["lsafe_level2"],200,'incorrect water aftbala')
		#self.assertEqual(x["lvol10"],4,'incorrect ') 
	def testVoucherCheck(self):
		""" 测试凭证入账功能 """
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"sstatus0":"K",
			"lsafe_level":11,
			"semp":"1000",
			"lserial0":3,
		}
		ret = obj.callsvr(850050,v)
		self.failUnless(ret==0,obj.errmsg)		
	def testVoucherEntry(self):
		""" 测试凭证入账功能 """
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"sstatus0":"B",
			"lsafe_level":11,
			"semp":"1000",
			"lserial0":3,
		}
		ret = obj.callsvr(850050,v)
		self.failUnless(ret==0,obj.errmsg)
def suite():
	#suites = ['testVoucherMake']
	#suites = ['VoucherCheck']
	#suites = ['VoucherMake']
	return unittest.TestSuite(map(voucherTest,suites))
	
if __name__ == "__main__":
	if bccclt.init("vmlinux",common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)
