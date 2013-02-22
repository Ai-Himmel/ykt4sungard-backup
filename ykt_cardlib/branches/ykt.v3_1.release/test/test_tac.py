#! /usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex
import pyDes,pbocfunc



def calcTac(trans,tackey):
    k1 = codecs.decode(tackey[:16],'hex')
    k2 = codecs.decode(tackey[16:],'hex')
    k3 = ''
    for i in range(len(k1)):
        e1 = ord(k1[i])
        e2 = ord(k2[i])
        k3 = k3 + chr((e1^e2) & 0xFF)
    data="%08X06%s%08X%s%s8000" % (trans.transAmt,trans.termNo,trans.termSeqNo
		,trans.transDate,trans.transTime)
    print "cipherData[%s]" % data
    initData="0000000000000000"
    ek = codecs.encode(k3,'hex')
    print "delivery key[%s]" % ek
    tac = pbocfunc.CalcMacDESHex(data,initData,ek)
    return tac[:8]
    
def dotest():
    cardTest = [
    ('2301D146',pbocfunc.TransPack(
       cardPhyNo='2301D146',
       cardBefBal=18480,
       cardAftBal=18380,
       transAmt=100,
       transDate='20101125',
       transTime='152156',
       termNo='000000000015',
       termSeqNo=0,
       cardPayCnt=12),
       "909F18D0")
    ]
    DTAC='9A884C4005A89C50DF8607AE484B5B5B'
    for p,trans,tac in cardTest:
        tackey = pbocfunc.PbocDeliveryKeyHex(p,DTAC)
        print "Phyno[%s] TACKEY[%s]" % (p,tackey)
        t = calcTac(trans,tackey)
        print "TAC[%s] calc[%s]" % (tac,t)
        

if __name__=="__main__":
    dotest()