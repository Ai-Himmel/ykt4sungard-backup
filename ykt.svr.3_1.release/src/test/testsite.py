#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class site(unittest.TestCase):
	"""站点管理"""
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
	def SiteAdd1(self):
		""" 站点添加1 """
		obj = bccclt.new(600)
		v = {
			"semp":"system",
			"sstatus0":"A",
			"scust_limit":"liweifang测试站点",
			"sphone":"172.16.0.39"
		}
		ret = obj.callsvr(820341,v)
		self.failUnless(ret==0,obj.errmsg)	
	def testSiteAdd2(self):
		""" 站点添加2 """
		obj = bccclt.new(600)
		v = {
			"semp":"system",
			"sstatus0":"A",
			"scust_limit":"wenjian测试站点",
			"sphone":"192.168.234.1"
		}
		ret = obj.callsvr(820341,v)
		self.failUnless(ret==0,obj.errmsg)
def suite():
	suites = ['testSiteAdd2']
	return unittest.TestSuite(map(paymentTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	unittest.main()
