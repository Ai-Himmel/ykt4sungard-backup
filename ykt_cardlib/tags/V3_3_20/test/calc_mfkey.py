#!/usr/bin/env python
# vim: encoding=cp936 :

import serial,time,string,codecs,sys
import binascii,binhex
import pyDes

def des_encrypt(key,data):
	k = pyDes.des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
	e = k.encrypt(codecs.decode(data,'hex')) 
	return codecs.encode(e,'hex')
	
def encryptmainkey(mainkey):
    e = codecs.decode(mainkey[:16],'hex')
    x = codecs.decode('3230303530313331','hex')
    encryptkey = ''
    for i in range(len(e)):
        k = ((~ord(e[i])) ^ ord(x[i])) & 0xFF
        encryptkey = encryptkey + chr(k)
        
    return codecs.encode(encryptkey,'hex')

def calcEncrypt(key):
    e = key[:16]
    x = '3230303530313331'
    k = des_encrypt(e,x)
    return k
    
def testencrypt(mainkey):
    e = calcEncrypt(mainkey)
    k = encryptmainkey(e)
    print "main key is [%s]" % e
    print "encrypt main key [%s]" % k
	
	
if __name__=="__main__":
	testencrypt(sys.argv[1])
    
    
