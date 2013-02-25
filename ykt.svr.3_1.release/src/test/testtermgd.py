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
		
	def testDeviceLogin(self):
		""" 测试终端登录 """
		obj = bccclt.new(common.MAINFUNC)
		# 设备商户绑定
		v = {
			"semp":common.OPERCODE,
			"sstatus0":"A",
			"lvol0":0,
			"lvol3":19,
			"lvol5":128,
			"stime2":"235959",
			"sdate1":"20090101",
			"sdate2":"20501010",
		}
		#ret = obj.callsvr(843371,v)
		#self.failUnless(ret==0,obj.errmsg)
		
		v = {
		"lcert_code":3,
		"lvol0":5
		}
		ret = obj.callsvr(849001,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol0","lvol1","scust_limit",'lvol2','lvol3','lvol4','scust_no','lvol5'])
		#print x
		self.assertEquals(x['lvol5'],1,'终端消费开关错误')
		self.assertNotEquals(x['lvol0'],0,'终端号错误')
		print "消费金额1 : %d " % (x['lvol3'])
		print "消费金额2 : %d " % (x['lvol4'])
		
		v = {
		"lcert_code":3,
		"lvol0":1
		}
		ret = obj.callsvr(849001,v)
		self.failUnless(ret<>0,obj.errmsg)
		
		v = {
		"lcert_code":3,
		"lvol0":0
		}
		ret = obj.callsvr(849001,v)
		self.failUnless(ret<>0,obj.errmsg)
		
		v = {
		"lcert_code":2,
		"lvol0":1
		}
		ret = obj.callsvr(849001,v)
		self.failUnless(ret<>0,obj.errmsg)
		
	def testReadCardFromDB(self):
		""" 测试查询卡信息 """
		obj = bccclt.new(common.MAINFUNC)
		
		v = {
		"lvol1":common.CUSTID
		}
		ret = obj.callsvr(849002,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(['lvol1','semail','smarket_code','sphone','scust_auth2',
		'scert_no','sstatus1','lvol6','sdate0','damt0','sdate2','scust_no2','sroom_no','lvol2'])
		#print x
		
		v = {
		"lvol0":common.CARDNO
		}
		ret = obj.callsvr(847173,v)
		self.failUnless(ret==0,obj.errmsg)
		
	def testExcLoss(self):
		""" 测试第三方挂失卡 """
		
		obj = bccclt.new(common.MAINFUNC)
		
		# 先修改密码
		v = {
		"lvol0":common.CARDNO,
		"scust_no":common.CARDPWD,
		"lwithdraw_flag":common.TERMID,
		"semp":common.OPERCODE
		}
		
		ret = obj.callsvr(847111,v)
		self.failUnless(ret==0,obj.errmsg)
		
		# 挂失卡
		v = {
		"lvol0":common.CUSTID,
		"lvol1":0,
		"lvol2":0,
		"sstatus0":'1',
		"semp_pwd":common.CARDPWD,
		"scust_limit":common.OPERCODE,
		"lvol6":common.TERMID,
		"lvol7":common.TERMID
		}
		ret = obj.callsvr(847318,v)
		self.failUnless(ret==0,obj.errmsg)
		
		# 查询卡信息
		v = {
		"lvol1":common.CUSTID
		}
		query_ret = obj.callsvr(849002,v)
		if query_ret == 0:
			x = obj.getrecord(['lvol1','semail','smarket_code','sphone','scust_auth2',
			'scert_no','sstatus1','lvol6','sdate0','damt0','sdate2','scust_no2','sroom_no','lvol2'])
		
		# 卡解挂
		v={"sstatus1":"0","lwithdraw_flag":common.TERMID,"lvol0":common.CARDNO}
		ret = obj.callsvr(846307,v)
		self.failUnless(ret==0,obj.errmsg)
		
		self.failUnless(query_ret==0,obj.errmsg)
		self.assertEquals(x['sdate2'][1],'1','card is not loss')
	
	def testTermTrans(self):
		""" 测试终端消费 """
		obj = bccclt.new(common.MAINFUNC)
		# 解挂
		v={"sstatus1":"0","lwithdraw_flag":common.TERMID,"lvol0":common.CARDNO}
		ret = obj.callsvr(846307,v)
		self.failUnless(ret==0,obj.errmsg)
		
		# 终端登录
		v = {
		"lcert_code":3,
		"lvol0":5
		}
		ret = obj.callsvr(849001,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol0","lvol1","scust_limit",'lvol2','lvol3','lvol4','scust_no','lvol5'])
		self.failUnless(x['lvol1']>0,'serial error!')
		devid=x['lvol0']
		serialno=x['lvol1']
		
		# 终端消费
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':devid,
		'sname':'','sphone':'13564319628','lvol5':serialno}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,"%s ,value %d " % (obj.errmsg,ret))
		x = obj.getrecord(["lvol0","damt0","damt1","damt2","lvol5","sdate1"])
		self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
		
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':devid,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret==0,obj.errmsg)
		
		# 测试终端流水号重复的问题
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':devid,
		'sname':'','sphone':'13564319628','lvol5':serialno}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret<>0,"%s ,value %d " % (obj.errmsg,ret))
		
		# 再测试一笔正常消费
		serialno+=1
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':devid,
		'sname':'','sphone':'13564319628','lvol5':serialno}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,"%s ,value %d ,serial %d " % (obj.errmsg,ret,serialno))
		x = obj.getrecord(["lvol0","damt0","damt1","damt2","lvol5","sdate1"])
		self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
		
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':devid,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret==0,obj.errmsg)

		
		
		
	def getDict(self,dictno):
		obj = bccclt.new(6000)
		
		# 部门代码
		v = {
		"lcert_code":dictno,
		"scust_auth":common.OPERCODE
		}
		
		ret = obj.callsvr(820502,v)
		self.failUnless(ret==0,obj.errmsg)
		cnt = 0
		while True:
			x=obj.getrecord(['lcert_code','sname','sall_name'])
			if x == None:
				break;
			#print x
			cnt+=1
		
		# no record
		if cnt == 0:
			self.fail('dict no record [%d] ' % dictno)
		else:
			self.assertEquals(obj.recordcnt,cnt,'record cnt not equals')
		
	def testDeptment(self):
		""" 测试部门代码 """
		self.getDict(3001)
		
	def testCusttype(self):
		""" 测试身份代码 """
		self.getDict(3000)
		
	def testIDType(self):
		""" 测试证件类型 """
		self.getDict(87)
	
	def testPeopleNation(self):
		""" 测试民族 """
		self.getDict(2001)
		
	def testNation(self):
		""" 测试国籍 """
		self.getDict(89)
		
	def testArea(self):
		""" 测试校区 """
		self.getDict(-27)
	
		

def suite():
	suites = ['testDeptment','testCusttype','testIDType','testPeopleNation','testNation',
	'testArea','testReadCardFromDB','testDeviceLogin','testTermTrans']
	return unittest.TestSuite(map(termGDTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)
	
