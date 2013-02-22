#
# Test script for the Python Cryptography Toolkit.
#

__revision__ = "$Id: test.py,v 1.7 2002/07/11 14:31:19 akuchling Exp $"

import os, sys
from bccclt import bccclt
import testbank
import unittest,common

if __name__=="__main__":
	if bccclt.init(common.TESTSVRIP,common.TESTSVRPORT,common.DEBUGBCC,common.XPACKDATA) <> 0:
			print "init bccclt error"
	alltests = unittest.TestSuite([
		testbank.suite()
		])
	runner = unittest.TextTestRunner(verbosity=2)
	runner.run(alltests)


