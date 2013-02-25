#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class paymentTest (unittest.TestCase):
	""" ������֧���������� """
	def setUp(self):
		pass
	
	def tearDown(self):
		pass
		
	def testNormalTrans(self):
		""" ���Ա�׼֧������ """
		obj = bccclt.new(common.MAINFUNC)
		
		#v={"sstatus1":"0","lwithdraw_flag":125,"lvol0":3797}
		#ret = obj.callsvr(846307,v)
		#self.failUnless(ret==0,obj.errmsg)
		
		# ������������
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,obj.errmsg)
		self.failUnless(obj.recordcnt==1,'no record')
		x = obj.getrecord(["lvol0","damt0","damt1","damt2","lvol5","sdate1"])
		self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
		
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret==0,obj.errmsg)
		
		# ��ͬһ�����ظ�����
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret==0,obj.errmsg)
		
		# ׼����ѯ������ˮ
		v = {"sdate1":x['sdate1'],
		"sdate2":x['sdate1'],
		'lwithdraw_flag':common.TERMID,
		'lserial1':x['lvol0']}
		ret = obj.callsvr(846606,v)
		self.failUnless(ret==0,obj.errmsg)
		self.failUnless(obj.recordcnt==2,'trans record error');
		r = obj.getrecord(["sdate0"])
		self.failUnless(r<>None,'no trans record')
		self.assertEquals(r['sdate0'],x['sdate1'],'account trans date error')
		r = obj.getrecord(["sdate0"])
		self.failUnless(r<>None,'no trans record')
		self.assertEquals(r['sdate0'],x['sdate1'],'account trans date error')
		r = obj.getrecord(["sdate0"])
		self.failUnless(r==None,'no trans record')
		
	def testWaterTrans(self):
		""" ���Թ��ݴ�ѧ��ˮ�س�ֵ """
		obj = bccclt.new(6000)
		
		befbala=100.0
		tranbala=5.0
		
		# ��������
		v = {"lcert_code":240201,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":befbala,"damt1":tranbala,"scust_no":'1000','lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol0","damt0","damt1","damt2","lvol5",'damt10','damt11','damt12'])
		self.assertEqual(x["damt0"],befbala-tranbala,'incorrect aftbala')
		self.assertEqual(x["lvol5"],(befbala-tranbala)*100,'incorrect aftbala')
		self.failUnless(x['damt10']>0.0,'water price1')
		self.failUnless(x['damt11']>0.0,'water price2')
		self.failUnless(x['damt12']>0.0,'water price3')
		
		v = {"lcert_code":240201,"lvol0":3797,"lvol1":24,"lvol2":0,
		"damt0":100.0,"damt1":1,"scust_no":'1000','lvol3':1,'lvol4':125,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret==0,obj.errmsg)
		
		
	def testInconstantTrans(self):
		""" ���Է�������ˮ֧�� """
		obj = bccclt.new(common.MAINFUNC)
		# �����쳣����
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,obj.errmsg)
		x = obj.getrecord(["lvol0","damt0","damt1","damt2","lvol5"])
		self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
		
		v = {"lcert_code":210002,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret<>0,obj.errmsg)
		
		# �����쳣���׽��
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":1.2,"damt1":1.2,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,obj.errmsg)
		
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":1.2,"damt1":1.21,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret<>0,obj.errmsg)
		
	def testLossCardTrans(self):
		""" ���Թ�ʧ��֧�� """
		obj = bccclt.new(common.MAINFUNC)
		# ����ʧ�����
		v={"sstatus1":"1","lwithdraw_flag":common.TERMID,"lvol0":common.CARDNO}
		ret = obj.callsvr(846307,v)
		self.failUnless(ret==0,obj.errmsg)
		
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret<>0,obj.errmsg)
		# �����
		v={"sstatus1":"0","lwithdraw_flag":common.TERMID,"lvol0":common.CARDNO}
		ret = obj.callsvr(846307,v)
		self.failUnless(ret==0,obj.errmsg)
	
	def testFronzenCardTrans(self):
		""" ���Զ��Ῠ֧�� """
		obj = bccclt.new(common.MAINFUNC)
		# ����������
		v={"sstatus1":"1","lwithdraw_flag":common.TERMID,"lvol0":common.CARDNO}
		ret = obj.callsvr(846308,v)
		self.failUnless(ret==0,obj.errmsg)
		
		v = {"lcert_code":210001,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret<>0,obj.errmsg)
		# ���ⶳ
		v={"sstatus1":"0","lwithdraw_flag":common.TERMID,"lvol0":common.CARDNO}
		ret = obj.callsvr(846308,v)
		self.failUnless(ret==0,obj.errmsg)
		
	def testReaderTrans(self):
		""" ���Դ�ѧ�Ƕ������շ� """
		obj = bccclt.new(common.MAINFUNC)
		# �豸�̻���
		v = {
			"semp":common.OPERCODE,
			"sstatus0":"A",
			"lvol0":0,
			"lvol3":19,
			"lvol5":common.TERMID,
			"stime2":"235959",
			"sdate1":"20090101",
			"sdate2":"20501010",
		}
		#ret = obj.callsvr(843371,v)
		#self.failUnless(ret==0,obj.errmsg)
		
		# ������������
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628'}
		ret = obj.callsvr(847316,v)
		self.failUnless(ret==0,"%s ,value %d " % (obj.errmsg,ret))
		x = obj.getrecord(["lvol0","damt0","damt1","damt2","lvol5","sdate1"])
		self.assertEqual(x["damt0"],99.0,'incorrect aftbala')
		self.assertEqual(x["lvol5"],9900,'incorrect aftbala')
		
		v = {"lcert_code":240202,"lvol0":common.CARDNO,"lvol1":common.CARDCNT,"lvol2":0,
		"damt0":100.0,"damt1":1,'lvol3':1,'lvol4':common.TERMID,
		'sname':'','sphone':'13564319628','lvol6':x['lvol0']}
		ret = obj.callsvr(847317,v)
		self.failUnless(ret==0,obj.errmsg)
		
		v = {"sdate1":x['sdate1'],
		"sdate2":x['sdate1'],
		'lwithdraw_flag':common.TERMID,
		'lserial1':x['lvol0']}
		ret = obj.callsvr(846606,v)
		self.failUnless(ret==0,obj.errmsg)
		self.failUnless(obj.recordcnt==2,'trans record error');
		r = obj.getrecord(["sdate0"])
		self.failUnless(r<>None,'no trans record')
		self.assertEquals(r['sdate0'],x['sdate1'],'account trans date error')
		r = obj.getrecord(["sdate0"])
		self.failUnless(r<>None,'no trans record')
		self.assertEquals(r['sdate0'],x['sdate1'],'account trans date error')
		r = obj.getrecord(["sdate0"])
		self.failUnless(r==None,'no trans record')

	
			
def suite():
	suites = ['testNormalTrans','testWaterTrans','testInconstantTrans',
	'testLossCardTrans','testFronzenCardTrans','testReaderTrans']
	return unittest.TestSuite(map(paymentTest,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	runner = unittest.TextTestRunner(verbosity=2)
	unittest.main(testRunner=runner)
