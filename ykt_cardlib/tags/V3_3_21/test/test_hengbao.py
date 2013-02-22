#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex
import pyDes


def desencrypt(key,data):
	k = pyDes.des(codecs.decode(key,'hex'),pad=None, padmode=pyDes.PAD_NORMAL)
	return k.encrypt(codecs.decode(data,'hex')) 
	
def triple_desencrypt(key,data):
	k = pyDes.triple_des(codecs.decode(key,'hex'),pad=None, padmode=pyDes.PAD_NORMAL)
	return k.encrypt(codecs.decode(data,'hex'))
	

def padcmd(cmd):
	padding = "8000000000000000"
	cmdlen = len(cmd)
	if cmdlen % 16 == 0:
		return cmd
	else:
		pl = (16 - (cmdlen%16))
		d = cmd + padding[:pl]
		return d
	
def calcmac(key,data,random):
	p = codecs.decode(data,'hex')
	datalen = len(p)
	keytext = codecs.decode(key,'hex')
	k = pyDes.des(keytext[:8],pad=None, padmode=pyDes.PAD_NORMAL)
	initdata = codecs.decode(random,'hex')
	
	for i in range(datalen/8):
		print "calc mac [%d] " % i
		m = ""
		for j in range(len(initdata)):
			m = m + chr(ord(initdata[j]) ^ ord(p[i*8+j]))
		initdata = m
		x = k.encrypt(initdata)
		initdata = x
		
	
	k1 = pyDes.des(keytext[8:],pad=None, padmode=pyDes.PAD_NORMAL)
	n = k1.decrypt(initdata)
	initdata = k.encrypt(n)
	return initdata
		

def testencrypt():
	print chr(ord('0'))
	mainkey = "57415443484441544154696D65434F53"
	random = "464E84AF00000000"
	sessionKey = codecs.encode(triple_desencrypt(mainkey,random),'hex')
	print "session key [%s] " % sessionKey
	# 
	#sessionKey = sessionKey[:16]
	data = "08112233445566778880000000000000"
	#e = desencrypt(sessionKey,data)
	#print "encrypt [%s]" % codecs.encode(e,'hex')
	
	e = triple_desencrypt(mainkey,data)
	print "just encrypt [%s]" % codecs.encode(e,'hex')
	
	cmd = "04D6830014" + codecs.encode(e,'hex')
	print "cmd [%s] "% cmd
	pcmd = padcmd(cmd)
	print "padding cmd[%d][%s]" % (len(pcmd),pcmd)
	
	e = calcmac(mainkey,pcmd,random)
	print "mac [%s]"  % codecs.encode(e,'hex')
	
	
	
if __name__=="__main__":
	testencrypt()