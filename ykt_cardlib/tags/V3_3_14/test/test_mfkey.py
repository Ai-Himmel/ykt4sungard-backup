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
	
		
def testkeyb(mainkey,plain):
    #mainkey = '417C1C77E6F36FEA010905DE07DFB634'
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

def testkeya(mainkey,plain):
    #mainkey = '417C1C77E6F36FEA'
    mainkey = mainkey[:16]
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

def encryptmainkey(mainkey):
    e = codecs.decode(mainkey[:16],'hex')
    x = codecs.decode('3230303530313331','hex')
    encryptkey = ''
    for i in range(len(e)):
        k = ((~ord(e[i])) ^ ord(x[i])) & 0xFF
        encryptkey = encryptkey + chr(k)
        
    return codecs.encode(encryptkey,'hex')

def mainkey4keyb(mainkey):
    e = codecs.decode(mainkey,'hex')
    x = e
    for i in range(len(e)):
        t = (~ord(e[i])) & 0xFF
        x = x + chr(t)
     
    return codecs.encode(x,'hex')

def testencrypt():
    #cardphy = ['42972E91BD68D16E','A2127F215DED80DE']
    cardphy = ['912E9742','F22712A2','929D2E91','912E9D92','2305E516']
    # mainkey='417C1C77E6F36FEA010905DE07DFB634' -- 测试密钥
    #mainkey='A519E5FEF969990A84F822BDBFF8D86C'
    mainkey = 'a519e5fef969990a'
    #mainkey=mainkey4keyb('0F36258AB21C7AAA')
    print "encrypt main key [%s]" % encryptmainkey(mainkey)
    for x in cardphy:
        y = calcphyid(x)
        print "calc physical [%s] data[%s]" % (x , y)
        testkeya(mainkey,y)
        testkeyb(mainkey,y)
        print "=============================="
	
	
def decryptKey():
    key='1122334455667788'
    data='5B4A94494D94CCAEB823A0302D789E5DA0EE5C28AF05D1354EFF59C3C3EDD44A'
    data2='3CF5F19CFE622E70D1BBF719A6D29CCE229A3AB5C502C90C37EC16E8C7962B53'
    k = pyDes.des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
    e = k.decrypt(codecs.decode(data,'hex')) 
    print 'load key[%s]' %  codecs.encode(e,'hex')
    
    e = k.decrypt(codecs.decode(data2,'hex')) 
    print 'main key[%s]' %  codecs.encode(e,'hex')

	
	
	
if __name__=="__main__":
	testencrypt()
    #decryptKey()
    
    