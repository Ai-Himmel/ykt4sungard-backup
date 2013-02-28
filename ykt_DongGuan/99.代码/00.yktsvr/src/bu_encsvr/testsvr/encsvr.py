#!/usr/bin/env
#coding: cp936

import socket,sys,os,codecs,pbocfunc
import datetime


class TransPack:
    def __init__(self):
        self.transcode='100105'
        self.transdate='20101216'
        self.transtime='230000'
        self.samno='000000000025'
        self.termseqno='000000002010121600000000002500000001'
        self.cardno='0000000000000001230'
        self.cardasno='00003114000000000014'
        self.befbala='%08d' % 1000
        self.amount='%08d' % 1000
        self.randomnum='12345678'
        self.dpscnt='%04X' % 1000
        self.transtype='02'
        self.mac1='00000000'
        self.mac2=''

class DGEncsvr:
    def __init__(self):
        self.svrip='0.0.0.0'
        self.svrport=18220
        self.sock = None
        self.stopService=False
        
    def startsvr(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.bind((self.svrip,self.svrport))
        self.sock.listen(1)
        print "start server ok......"
        return True
        
    def stopsvr(self):
        if self.sock == None:
            return
        self.sock.close()
        
    def recvdata(self,s,l):
        while 1:
            d = s.recv(l)
            if len(d) >= l:
                return d
        return None
        
    def calcdpsmac(self,pack):
        # calc sk
        dlk="\x76\xe1\x62\x7b\x8c\x60\xda\x55\x00\xd1\x9f\x5b\x1d\x35\x47\xe0"
        print "random[%s]cnt[%d]" % (pack.randomnum,pack.dpscnt)
        seed = '%s%04X8000' % (pack.randomnum,pack.dpscnt)
        print "seed[%s]" % seed
        seed = codecs.decode(seed,'hex')
        cardno=codecs.decode(pack.cardasno[12:],'hex')
        carddlk=pbocfunc.PbocDeliveryKey(cardno,dlk)
        print "card dlk[%s]" % codecs.encode(carddlk,'hex')
        
        sk = pbocfunc.tripledesencrypt(carddlk,seed)
        print "sk [%s]" % codecs.encode(sk,'hex')
        szData = "%08X02%s%s%s800000000000" % (pack.amount,pack.samno,pack.transdate,pack.transtime)
        print "data[%s]" % szData
        szData = codecs.decode(szData,'hex')
        
        initdata="\x00\x00\x00\x00\x00\x00\x00\x00"
        mac2 = pbocfunc.CalcMacDES(szData,initdata,sk)
        return mac2[:4]
        
    def calcmac(self):
        clt,addr = self.sock.accept()
        print "connect by " , addr
        
        data = self.recvdata(clt,4)
        recvlen=int(data)
        
        print "recvlen[%d]" % recvlen
        data = self.recvdata(clt,recvlen)
        
        print "recv[%s]" % data
        pack = TransPack()
        self.unpack(data,pack)
        
        if pack.transcode != "100105":
            return
        
        pack.mac2 = codecs.encode(self.calcdpsmac(pack),'hex')
        print "mac is[%s]" % pack.mac2
        
        msg=''
        for i in range(60):
            msg = msg + ' '
            
        current = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        data = pack.transcode+"000000000"+msg+pack.termseqno+current+pack.mac2
        
        datalen = '%04d' % len(data)
        
        data = datalen + data
        print "send[%s]" % data
        clt.send(data)
        
            
    def unpack(self,data,pack):
        """ begin """
        # data=pack.transcode+pack.transdate+pack.transtime+pack.samno+pack.termseqno+\
        # pack.cardno+pack.cardasno+pack.befbala+pack.amount+pack.randomnum+pack.dpscnt+\
        # pack.transtype+pack.mac1
        offset = 0
        pack.transcode=data[offset:offset+6]
        offset = offset + 6
        if pack.transcode == "199999":
            self.stopService = True
            return
        elif pack.transcode == "100105":
            if len(data) < 144:
                print "data length error"
                return
        else:
            return
        pack.transdate=data[offset:offset+8]
        offset = offset + 8
        
        pack.transtime=data[offset:offset+6]
        offset = offset + 6
        
        pack.samno=data[offset:offset+12]
        offset = offset + 12
        
        pack.termseqno=data[offset:offset+36]
        offset = offset + 36
        
        pack.cardno=data[offset:offset+19]
        offset = offset + 19
        
        pack.cardasno=data[offset:offset+20]
        offset = offset + 20
        
        pack.befbal = int(data[offset:offset+8])
        offset = offset + 8
        
        pack.amount = int(data[offset:offset+8])
        offset = offset + 8
        
        pack.randomnum = data[offset:offset+8]
        offset = offset + 8
        
        pack.dpscnt = int(data[offset:offset+4],16)
        offset = offset + 4
        
        pack.transtype = data[offset:offset+2]
        offset = offset + 2
        
        pack.mac1 = data[offset:offset+8]
        offset = offset + 8
        
        
    def test(self):
        if not self.startsvr():
            return
           
        print "start service..."   
        while not self.stopService:
            self.calcmac()
        
        self.stopsvr()
        
        
if __name__=="__main__":
    svr = DGEncsvr()
    svr.test()