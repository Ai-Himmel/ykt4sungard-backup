#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex
import pyDes

# 外部认证
DACK='DF8607AE484B5B5B7B7F9ACB511A21BC'
# 消费
DPK1='FF44D94ECA35772612327FCAB4CE6E48'
# 圈存
DLK1='76E1627B8C60DA5500D19F5B1D3547E0'


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


def calc_mid_key(key,seed):
    """ 密钥分散 80 1A  """
    dk = pyDes.triple_des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
    e1 = codecs.decode(seed,'hex')
    e2 = ''
    for i in range(len(e1)):
        e2 = e2 + chr((~ord(e1[i])) & 0xFF)

    ed1 = dk.encrypt(e1)
    ed2 = dk.encrypt(e2)

    s = codecs.encode(ed1+ed2,'hex')
    return s


def calcmac(key,data,seedkey,random):
    """ 使用过程密钥计算 MAC """
    p = codecs.decode(data,'hex')
    datalen = len(p)
    #keytext = codecs.decode(key,'hex')
    keytext = codecs.decode(calc_mid_key(key,seedkey),'hex')
    k = pyDes.des(keytext[:8],pad=None, padmode=pyDes.PAD_NORMAL)
    initdata = codecs.decode(random,'hex')

    for i in range(datalen/8):
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



def CalcExtAuth(phyno,random):
    if len(phyno) == 8:
        phyno = phyno + '80000000'

    # calc seed key
    k = calc_mid_key(DACK,phyno)
    mac = triple_desencrypt(k,random)
    return mac


def testExtAuth():
    phyno = [
        ('217E2DD2','A9B0A12E00000000'),
        ('217F12A2','BA50007300000000')]

    for p in  phyno:
        mac = CalcExtAuth(p[0],p[1])
        print "phyno[%s]random[%s],mac[%s]" % (p[0],p[1],mac)


if __name__=="__main__":
    testExtAuth()

