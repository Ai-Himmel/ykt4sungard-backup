#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class testGate(unittest.TestCase):
	"""站点管理"""
	def setUp(self):
		pass
	
	def tearDown(self):
		pass

	def testGetDownloadList(self):
		""" 下载门禁名单队列 """
		obj = bccclt.new(common.MAINFUNC)
		v = {
			"lcert_code":common.SYSID,
            "lvol0":20,
            "lvol1":10,
            "lvol2":0
		}
		ret = obj.callsvr(950103,v)
		self.failUnless(ret==0,obj.errmsg)
        
def suite():
	suites = ['testGetDownloadList']
	return unittest.TestSuite(map(testGate,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	unittest.main()
