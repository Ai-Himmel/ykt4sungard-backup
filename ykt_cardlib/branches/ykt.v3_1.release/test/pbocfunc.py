#! /usr/bin/env python
# vim: tabstop=4

import pyDes,codecs



def desencrypt(key,data):
    k = pyDes.des(key,pad=None, padmode=pyDes.PAD_NORMAL)
    return k.encrypt(data) 

def tripledesencrypt(key,data):
    k = pyDes.triple_des(key,pad=None, padmode=pyDes.PAD_NORMAL)
    return k.encrypt(data)


def desencrypthex(key,data):
    k = pyDes.des(codecs.decode(key,'hex'), pad=None, padmode=pyDes.PAD_NORMAL)
    e = k.encrypt(codecs.decode(data,'hex')) 
    return codecs.encode(e,'hex')

def tripledesencrypthex(key,data):
    k = pyDes.triple_des(codecs.decode(key,'hex'),pad=None, padmode=pyDes.PAD_NORMAL)
    e1 = k.encrypt(codecs.decode(data,'hex'))
    return codecs.encode(e1,'hex')

def DataNot(data):
    r = ''
    for a in data:
        r = r + chr((~ord(a))&0xFF)
    return r
        
def PadCardPhyNo(phyno):
    r=''
    if len(phyno) < 8:
        pad = "\x80\x00\x00\x00\x00\x00\x00\x00"
        l = 8 - len(phyno)
        r = phyno + pad[:l]
    elif len(phyno) == 8:
        r = phyno
    else:
        r = phyno[:8]
    return r
    
def PadCardPhyNoHex(phyno):
    return codecs.encode(PadCardPhyNo(codecs.decode(phyno,'hex')),'hex')
    
def PbocDeliveryKey(factor,key):
    cipherdatanot = ''
    cipherdata = PadCardPhyNo(factor)
    
    print "factor is [%s]" % codecs.encode(cipherdata,'hex')

    cipherdatanot = DataNot(cipherdata)
    
    k1 = tripledesencrypt(key,cipherdata)
    k2 = tripledesencrypt(key,cipherdatanot)
    
    return k1+k2
    
def PbocDeliveryKeyHex(factor,key):
    f = codecs.decode(factor,'hex')
    k = codecs.decode(key,'hex')
    k1 = PbocDeliveryKey(f,k)
    return codecs.encode(k1,'hex')
   

def CalcMac3DES(data,initdata,key):
    datalen = len(data)
    k = pyDes.des(key[:8],pad=None, padmode=pyDes.PAD_NORMAL)

    for i in range(datalen/8):
        m = ""
        for j in range(len(initdata)):
            m = m + chr(ord(initdata[j]) ^ ord(p[i*8+j]))

        initdata = m
        x = k.encrypt(initdata)
        initdata = x


    k1 = pyDes.des(key[8:],pad=None, padmode=pyDes.PAD_NORMAL)
    n = k1.decrypt(initdata)
    initdata = k.encrypt(n)
    return initdata
    
def CalcMac3DESHex(data,initdata,key):
    d = codecs.decode(data,'hex')
    id = codecs.decode(initdata,'hex')
    k = codecs.decode(key,'hex')
    k1 = CalcMac3DES(d,id,k)
    return codecs.encode(k1,'hex')
    
def CalcMacDES(data,initdata,key):
    datalen = len(data)
    k = pyDes.des(key,pad=None, padmode=pyDes.PAD_NORMAL)
    
    for i in range(datalen/8):
        m = ""
        for j in range(len(initdata)):
            m = m + chr(ord(initdata[j]) ^ ord(data[i*8+j]))

        initdata = m
        x = k.encrypt(initdata)
        initdata = x
        
    return initdata
        
def CalcMacDESHex(data,initdata,key):
    d = codecs.decode(data,'hex')
    id = codecs.decode(initdata,'hex')
    k = codecs.decode(key,'hex')
    k1 = CalcMacDES(d,id,k)
    return codecs.encode(k1,'hex')
    
    
class TransPack:
    TRANS_PURCHASE=6
    TRANS_LOAD=2
    def __init__(self):
        self.cardPhyNo=''
        self.cardBefBal=0
        self.cardAftBal=0
        self.transAmt=0
        dt = datetime.datetime.today().strftime('%Y%m%d%H%M%S')
        self.transDate=dt[:8]
        self.transTime=dt[8:]
        self.random=''
        self.mac=''
        self.termNo=''
        self.termSeqNo=0
        self.cardNo=0
        self.cardPayCnt=0
        self.cardDpsCnt=0
        self.transType=0
    
    def __init__(self,cardPhyNo='',cardBefBal=0,cardAftBal=0,transAmt=0,transDate='',transTime='',
        random='',mac='',termNo='',termSeqNo=0,cardNo=0,cardPayCnt=0,cardDpsCnt=0,transType=TRANS_PURCHASE):
        self.cardPhyNo=cardPhyNo
        self.cardBefBal=cardBefBal
        self.cardAftBal=cardAftBal
        self.transAmt=transAmt
        self.transDate=transDate
        self.transTime=transTime
        self.random=random
        self.mac=mac
        self.termNo=termNo
        self.termSeqNo=termSeqNo
        self.cardNo=cardNo
        self.cardPayCnt=cardPayCnt
        self.cardDpsCnt=cardDpsCnt
        self.transType=transType
        