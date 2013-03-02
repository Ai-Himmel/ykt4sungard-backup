#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os
from distutils.util import get_platform


class subsidy(unittest.TestCase):
    """վ�����"""
    def setUp(self):
        pass

    def tearDown(self):
        pass
    def testDownloadSubsidy(self):
        """ ���ز��� """
        bcc = bccclt.new(common.MAINFUNC)
        
        v = {
            "lwithdraw_flag":1, # termid
            "lvol0":4, # cardno
            "lvol5":1, # ��ֵ����
            "lvol6":1, # ���Ѵ���
            "lvol7":1000, # �����
            "lvol4":0, # �������κ�
        }
        ret = bcc.callsvr(846318,v)
        self.failUnless(ret==0,bcc.errmsg)
        x = bcc.getrecord(['lvol0','lvol8','sdate3','lwithdraw_flag','lserial1','damt0','vsmess'])
        #x = bcc.getrecord(["lvol0"])
        print x

		
def suite():
	suites = ['testDownloadSubsidy']
	return unittest.TestSuite(map(subsidy,suites))
	
if __name__ == "__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
		print "init bccclt error"
	unittest.main()
