#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class voucherTest (unittest.TestCase):
	""" ƾ֤���� """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
	""" ƾ֤¼�� """	
	def testVoucherMake(self):
		""" ����ƾ֤¼�빦�� """
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"sstatus0":"A",
			"lsafe_level":11,
			"lwithdraw_flag":common.TERMID,
			"semp":"1000",
			"sorder0":"20100815",
			"lvol0":2,
			"snote":"�˿�",
			"lbank_acc_type":5,
			"lvol9":2,
			"sname2":"14525678",
			"scust_auth":"220201",
			"damt1":500,
			"damt2":0,
			"damt3":0,
			"damt4":500,			
			"snote2":"�˿�",
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
		""" ����ƾ֤���˹��� """
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
		""" ����ƾ֤���˹��� """
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
