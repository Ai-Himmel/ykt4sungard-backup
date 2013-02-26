#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os

class paymentAgentTest (unittest.TestCase):
	""" 广州大学城仿新中兴接口测试用例 """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
		
	def testQuery(self):
		""" 测试查询第三方账户 """
		obj = bccclt.new(9900)
		v = {
		'scust_limit':'001',
		'sbank_code':'1000',
		'sbank_acc':'12345',
		'spager':'200901010',
		'sall_name':'张三',
		'lwithdraw_flag':common.TERMID,
		'vsvarstr0':'aaaaaaaa',
		'sholder_ac_no2':'10.49.188.13',
		'lvol4':3000,
		'lsafe_level':3
		}
		ret = obj.callsvr(851001,v,10000)
		self.failUnless(ret==0,obj.errmsg)
		
		x = obj.getrecord(['scust_limit',
		'sbank_code',
		'sbank_acc',
		'scusttypes',
		'lvol1',
		'sstation0',
		'lsafe_level',
		'vsmess',])
		
		self.failUnless(x['lsafe_level']==0,'查询账户 : ' + x['vsmess'])
		print x
		
		
	

	
def suite():
	suites = ['testQuery']
	return unittest.TestSuite(map(termGDTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)
	
