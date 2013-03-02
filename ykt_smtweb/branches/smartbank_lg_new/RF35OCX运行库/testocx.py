#!/usr/bin/env python
# vim: encoding=cp936:
import win32com.client

def testOcx():
	#ocx = win32com.client.Dispatch("RF35OCXLib._DRF35OCX")
	#repr(win32com.client.Dispatch)
	#repr(win32com.client.constants)
	ocx = win32com.client.Dispatch("RF35OCX.RF35OCXCtrl.1")
	#win32com.client.gencache.MakeModuleForTypelib("77BADB02-4AEB-4F23-AA67-850E29099245")
	#win32com.client.gencache.EnsureModule("77BADB02-4AEB-4F23-AA67-850E29099245")
	#ocx = win32com.client.gencache.GetModuleForCLSID("77BADB02-4AEB-4F23-AA67-850E29099245")
	try:
		ocx
		print repr(ocx._oleobj_)
		print ocx.GetVersion()
		ocx.DoScan()
		cardno = ocx.CardNo
		print cardno
		ocx.BeginUpdate(cardno)
		ocx.SetCardProperty("feetype","15")
		ret = ocx.UpdateCard('4344334539413846')
		if ret <> 0:
			print "update faild ,ret[%d]" % ret
		else:
			print "update success"
	except Exception as e:
		print "Error[%010lu][%ld] [%s]" % (e[0],e[0],e[1])
		

if __name__ == "__main__":
	testOcx()