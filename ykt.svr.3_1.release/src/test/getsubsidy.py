#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform

class GetSubsidy (unittest.TestCase):
	""" 测试领取补贴 """
	def setUp(self):
		pass

	def tearDown(self):
		pass
		
	def testGetSubsidy(self):
		""" 测试查询卡信息 """
		obj = bccclt.new(6000)
		
		v = {
		"lwithdraw_flag":1220,
		'lvol0':81,
		'lvol5':5, # 充值次数
		'lvol6':295, # 消费次数
		'lvol7':11981, # 入卡值
		}
		ret = obj.callsvr(846318,v,8000)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(['lvol0','lvol8','sdate3','lwithdraw_flag','lserial1','damt0','vsmess'])
		print x
		
def suite():
	suites = ['testGetSubsidy']
	return unittest.TestSuite(map(GetSubsidy,suites))
	
if __name__ == "__main__":
	if bccclt.init('172.16.0.107',4000,1,'cpack.dat') <> 0:
		print "init bccclt error"
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)
	
