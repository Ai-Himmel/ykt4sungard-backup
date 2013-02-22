#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex
import pyDes


def desencrypt(key,data):
	k = pyDes.des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
	return k.encrypt(codecs.decode(data,'hex')) 
	
def tripledesencrypt(key,data):
	k = pyDes.triple_des(codecs.decode(key,'hex'),pad=None, padmode=pyDes.PAD_NORMAL)
	return k.encrypt(codecs.decode(data,'hex'))
	
	
def des_encrypt(key,data):
	k = pyDes.des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
	e = k.encrypt(codecs.decode(data,'hex')) 
	return codecs.encode(e,'hex')
	
def triple_desencrypt(key,data):
	k = pyDes.triple_des(codecs.decode(key,'hex'),pad=None, padmode=pyDes.PAD_NORMAL)
	e1 = k.encrypt(codecs.decode(data,'hex'))
	return codecs.encode(e1,'hex')

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
		#print "calc mac [%d] " % i
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
		
		
def calc_mid_key(key,seed):
	dk = pyDes.triple_des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
	e1 = codecs.decode(seed,'hex')
	e2 = ''
	for i in range(len(e1)):
		e2 = e2 + chr((~ord(e1[i])) & 0xFF)
		
	ed1 = dk.encrypt(e1)
	ed2 = dk.encrypt(e2)
	
	s = codecs.encode(ed1+ed2,'hex')
	return s
	
		
def testkeyb(plain):
	mainkey = '417C1C77E6F36FEA010905DE07DFB634'
	seedkey = '3230303530313331'
	#plain = '42972E91BD68D16E'
	e = calc_mid_key(mainkey,seedkey)
	print "delivery [%s]" % e
	e1 = triple_desencrypt(e,plain)
	#print "key B [%s]" % codecs.encode(e1,'hex')
	print "cphier data[%s]" % e1
	
	s = codecs.decode(e1+e1,'hex')
	pos = 0
	for x in range(8):
		pos = pos + ord(s[x])
	
	startpos = pos % 7
	e1 = codecs.encode(s[startpos:startpos+6],'hex')
	print "key B [%s]" % e1.upper()
	
	#startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
	#memcpy(sect->key,sCipher+startpos,6);

def testkeya(plain):
	mainkey = '417C1C77E6F36FEA'
	#mainkey = '417C1C77E6F36FEA010905DE07DFB634'
	seedkey = '3230303530313331'
	#plain = '42972E91BD68D16E'
	e = des_encrypt(mainkey,seedkey)
	print "delivery [%s]" % e
	e1 = des_encrypt(e,plain)
	print "cphier data[%s]" % e1
	s = codecs.decode(e1+e1,'hex')
	pos = 0
	for x in range(8):
		pos = pos + ord(s[x])
	
	startpos = pos % 7
	e1 = codecs.encode(s[startpos:startpos+6],'hex')
	print "key A [%s]" % e1.upper()

	
def calcphyid(phyid):
	hexphy = codecs.decode(phyid,'hex')
	cipherData1 = ''
	cipherData2 = ''
	for i in range(len(hexphy)):
		x = hexphy[i]
		cipherData1 = x + cipherData1
		cipherData2 = chr((~ord(x))&0xFF) + cipherData2
		
	return codecs.encode(cipherData1 + cipherData2, 'HEX')
	
def testencrypt():
    mainkey = '3390eb4d0c594019d2ca3ab69f3febad'
    data='5F323031303031303100000000000000000000000030FFFFFF2820990305100011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100'
    seed1='0010000000102101' # 应用序列号
    seed2='7AA27AC380000000' # 随机数
    k1 = calc_mid_key(mainkey,seed1)
    k2 = calc_mid_key(k1,seed2)
    
    e = triple_desencrypt(k2,data)
    print e
    
    data='845401006A010000000005' + e + '8000000000'
    
    print "len[%d]data[%s]" % (len(data),data)
    
    e = calcmac(k2,data,'0000000000000000')
    print "mac [%s]" % codecs.encode(e,'hex')
    
	
	
def decryptKey():
    key='1122334455667788'
    #data='5B4A94494D94CCAEB823A0302D789E5DA0EE5C28AF05D1354EFF59C3C3EDD44A'
    data='5B4A94494D94CCAE1ACE030AB50901307431EC4B05D664D02DD465898F8BBF07'
    data2='3CF5F19CFE622E70D1BBF719A6D29CCE229A3AB5C502C90C37EC16E8C7962B53'
    k = pyDes.des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
    e = k.decrypt(codecs.decode(data,'hex')) 
    print 'load key[%s]' %  codecs.encode(e,'hex')
    
    e = k.decrypt(codecs.decode(data2,'hex')) 
    print 'main key[%s]' %  codecs.encode(e,'hex')

    
	
	
	
if __name__=="__main__":
	decryptKey()
    #testencrypt()
    
    