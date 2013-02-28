#!/usr/bin/env
#coding: cp936

import socket,sys,os,codecs,datetime


class TransPack:
    def __init__(self):
        #self.transcode='100105'
        #self.transcode='199999'
        #self.transdate='20101216'
        #self.transtime='230000'
        #self.samno='000000000025'
        #self.termseqno='000000002010121600000000002500000001'
        #self.cardno='0000000000000001230'
        #self.cardasno='00003114000000000014'
        #self.befbala='%08d' % 1000
        #self.amount='%08d' % 1000
        #self.randomnum='12345678'
        #self.dpscnt='%04X' % 1000
        #self.transtype='02'
        #self.mac1='00000000'
        #self.mac2=''
        self.transcode='100105'
        self.transdate='20101217'
        self.transtime='220312'
        self.samno='310310000060'
        self.termseqno='000000002010121600000000002500000001'
        self.cardno='0000000000219897176'
        self.cardasno='00001103000000000054'
        self.befbala='%08d' % 1000
        self.amount='%08d' % 19680
        self.randomnum='346778C7'
        self.dpscnt='%04X' % 1
        self.transtype='02'
        self.mac1='957B035E'
        self.mac2=''
        
        self.establishment='000000000000'
        self.teller='000000000000'
        self.channel='000'
        self.hostseqno='                             2521176'
        self.hostdate='20101217'
        

class DGEncsvr:
    def __init__(self):
        self.svrip='120.196.172.14'
        #self.svrip='192.168.0.103'
        self.svrport=18220
        self.sock = None
        
    def connectsvr(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.svrip,self.svrport))
        print "connect to server ok......"
        return True
        
    def disconnect(self):
        if self.sock == None:
            return
        self.sock.close()
        
    def calcmac(self):
        pack = TransPack()
        data=pack.transcode+pack.transdate+pack.transtime+pack.samno+pack.termseqno+\
            pack.cardno+pack.cardasno+pack.befbala+pack.amount+pack.randomnum+pack.dpscnt+\
            pack.transtype+pack.mac1
        #data=pack.transcode+pack.transdate+pack.transtime+pack.establishment+pack.teller+pack.samno+\
        #    pack.channel+pack.termseqno+pack.hostseqno+pack.hostdate+\
        #    pack.cardno+pack.cardasno+pack.befbala+pack.amount+pack.randomnum+pack.dpscnt+\
        #    pack.transtype+pack.mac1
        datalen='%04d' % len(data)
        sendpack = datalen + data
        print "send data ================="
        print "[%s]" % sendpack
        self.sock.send(sendpack)
        while 1:
            data = self.sock.recv(4)
            if data: break
        
        if not data:
            print "cannot recv data"
            return False
        recvlen = int(data)
        print "recvlen [%d]" % recvlen
        if recvlen > 200:
            recvlen = 200
        data=''
        currlen=0
        if recvlen > 0:
            while 1:
                r = self.sock.recv(recvlen-currlen)
                if r:
                    print "recv ok====================="
                    data = data + r
                    currlen = len(data)
                    if currlen >= recvlen:
                        print "currlen[%d]recv[%d]" % (currlen,recvlen)
                        break
                        
        print "recv[%s]" % data
        
        
    def test(self):        
        times = 100
        mintime=100000000
        maxtime=0
        totaltime=0.0
        begin = datetime.datetime.now()
        for i in range(times):
            if not self.connectsvr():
                return
            self.calcmac()
            self.disconnect()
            end = datetime.datetime.now()
            delta = end - begin
            t = delta.seconds + delta.microseconds / 1000000.0
            if t < mintime: mintime = t
            if t > maxtime: maxtime = t
            begin = end
            totaltime = totaltime + t
        
        print "calc [%d]times cost [%.4f]s,max[%.4f]min[%.4f]avg[%.4f]" % (times,totaltime,maxtime,mintime,totaltime/times)
        
        

if __name__ == "__main__":
    encsvr = DGEncsvr()
    encsvr.test()