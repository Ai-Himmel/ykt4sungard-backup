#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import unittest,sys,os
from distutils.util import get_platform
p = "build/lib.%s-%.3s" % (get_platform(), sys.version)
p = os.path.join(p,'bccclt/cpack.dat')

class bcccltTest (unittest.TestCase):
	def setUp(self):
		if bccclt.init('172.16.0.60',4000,1,'d:/cpack.dat') <> 0:
			print "init bccclt error"
		
	
	def tearDown(self):
		pass
	def testSign(self):
		"""圈存签到"""
		obj = bccclt.new(5000)
		v = {
			"snote":'圈存签到',
			"sdate0":'20090606',
			"stime0":'182144',
			"lvol0":'92083',
			"sclose_emp":'240101',
			"semp_pwd":'111111',
			"sstatus0":'0',
			"sserial0":'4800',
			"sorder2":'124'
		}
		ret = obj.callsvr(900077,v)
		self.failUnless(ret==0,obj.errmsg)
	def CardLost(self):
		"""卡挂失"""
		obj = bccclt.new(5000)
		v = {
			"snote":'卡挂失',
			"sdate0":'20090606',
			"stime0":'182144',
			"lvol0":'92083',
			"sclose_emp":'930001',
			"semp_pwd":'111111',
			"sstatus0":'0',
			"sserial0":'4800',
			"sorder2":'127',
		}
		ret = obj.callsvr(900077,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol8","damt0","damt1","damt2","lvol5"])
		#self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		#self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
	def PasswdUpdate(self):
		"""修改密码"""
		obj = bccclt.new(5000)
		v = {
			"lcert_code":210001,
			"lvol0":3797,
			"lvol1":24,
			"lvol2":0,
			"damt0":100.0,
			"damt1":1,
			"sclose_emp":'930001',
			"scust_no":'1000',
			'lvol3':1,
			'lvol4':125,
			'sname':'',
			'sphone':'13564319628'
		}
		ret = obj.callsvr(900077,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol8","damt0","damt1","damt2","lvol5"])
		#self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		#self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
		
	def testCardUnLost(self):
		"""卡解挂"""
		obj = bccclt.new(5000)
		v = {
			"snote":'卡解挂',
			"sdate0":'20090606',
			"stime0":'182144',
			"lvol0":'92083',
			"sclose_emp":'930002',
			"semp_pwd":'111111',
			"sstatus0":'0',
			"sserial0":'4942',
			"sorder2":'127',
		}
		ret = obj.callsvr(900077,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol8","damt0","damt1","damt2","lvol5"])
		#self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		#self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
	def BankCardBind(self):
		""""银行卡绑定"""
		obj = bccclt.new(6000)
		v = {
			"snote":'银行卡绑定',
			"sstatus0":'A',
			"lvol1":4800,
			"lwithdraw_flag":127,
			"semp":'1000',
			"spager":'spager',
			"sbank_code":'02',
			"scard0":"9558803602115542797",
			"sbranch_code0":'2'
		}
		ret = obj.callsvr(841602,v)
		print ret
		self.failUnless(ret==0,"%s , ret=%d " % (obj.errmsg,ret))
		#self.assertEqual(ret,0,obj.errmsg)
		x = obj.getrecord(["lvol8","damt0","damt1","damt2","lvol5"])
		#self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		#self.assertEqual(x["lvol5"],9900,'incorrect aftbala')		
	def BankTranser(self):
		"""银行转账"""
		obj = bccclt.new(5000)
		v = {
			"snote":'银行转账',
			"sdate0":'20090606',
			"stime0":'182144',
			"lvol0":'92083',
			"sclose_emp":'242002',
			"semp_pwd":'222222',
			"sstatus0":'0',
			"sserial0":'4942',
			"scust_auth":"9558803602115542797",
			"sstation1":"",
			"sorder0":'1.0000',
			"sorder2":'127',
			"lvol1":4
		}
		ret = obj.callsvr(900077,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol8","damt0","damt1","damt2","lvol5"])
		#self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		#self.assertEqual(x["lvol5"],9900,'incorrect aftbala')		
	def BankCardBind(self):
		""""银行卡绑定"""
		obj = bccclt.new(6000)
		v = {
			"snote":'银行卡绑定',
			"sstatus0":'A',
			"lvol1":4800,
			"lwithdraw_flag":127,
			"semp":'1000',
			"spager":'spager',
			"sbank_code":'02',
			"scard0":"9558803602115542797",
			"sbranch_code0":'2'
		}
		ret = obj.callsvr(841602,v)
		print ret
		self.failUnless(ret==0,"%s , ret=%d " % (obj.errmsg,ret))
		#self.assertEqual(ret,0,obj.errmsg)
		x = obj.getrecord(["lvol8","damt0","damt1","damt2","lvol5"])
		#self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		#self.assertEqual(x["lvol5"],9900,'incorrect aftbala')		
			
def suite():
	suites = ['testSign']
	return unittest.TestSuite(map(bcccltTest,suites))
	
if __name__ == "__main__":
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)