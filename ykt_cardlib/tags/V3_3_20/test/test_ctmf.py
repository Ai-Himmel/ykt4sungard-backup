#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex,sys,struct,collections
from datetime import datetime,timedelta,date
from CrcMoose import *


CARDKEYA = 1
CARDKEYB = 0
PORTNO = 2
DEBUG=0


class TransPack:
    def __init__(self):
        self.cardphyid = ''
        self.transdate = ''
        self.transtime = ''
        self.amount = 0
        self.cardbefbal = 0
        self.cardaftbal = 0
        self.paycnt = 0
        self.depositcnt = 0
        self.recordidx = 0

class CTRFSIM:
    PackagePara = collections.namedtuple('PackagePara','paycnt daypaymoney dpscnt dpsmoney recidx transflag')
    RecordData =  collections.namedtuple('RecordData','year month day hour minute second amount transtype block device')
    RECORDSECTNO = 10
    def __init__(self):
        self.ser = None
        self.packageSectNo = 1
        self.packageParaSectNo = 2
        self.cardKeyA = '010203040506'
        self.cardKeyB = 'A1A2A3A4A5A6'
        self._resetData()

    def _resetData(self):
        self.device_id = ''
        self.cardphyid = ''
        self.lastLoginKeyASect = 0xFF
        self.lastLoginKeyBSect = 0xFF
        
    def open(self,port=0,baud=115200):
        self.ser = serial.Serial()
        self.ser.baudrate = baud
        self.ser.port = port
        self.ser.timeout = 20
        try:
            self.ser.open()
        except:
            return False
        return True
        
    def close(self):
        if self.ser <> None:
            self.ser.close()
        
    def flush(self):
        self.ser.flushInput()
        self.ser.flushOutput()
        

    def initReader(self):
        pass
            
    def _log(self,msg):
        if DEBUG==1:
            print msg
            
    def _sendAndRecv(self,sendData,timeout=1000):
        answer = sendData
        self.flush()
        self.ser.write(answer)
        
        self._log("send[%s]" % codecs.encode(answer,'hex'))
        intime = datetime.today()
        outtime = intime + timedelta(milliseconds=timeout)
        total = 0
        full_data = ''
        while True:
            l = self.ser.inWaiting()
            if l == 0: 
                timespan = datetime.today()
                if timespan > outtime:
                    return False,''
                continue
            answer=self.ser.read(l)
            total += l
            full_data += answer
            if total >= 2:
                datalen = ord(full_data[1])
                if datalen <= total:
                    break
               
        self._log("recv[%s]" % codecs.encode(full_data,'hex'))
        return True,full_data
            
    def _sendPosCmd(self,cmd,timeout=3000):
        ucCmd = codecs.decode(cmd,'hex')
        cmdHead = '80%02X' % len(ucCmd)
        realCmd = codecs.decode(cmdHead,'hex') + ucCmd
        r , d = self._sendAndRecv(realCmd,timeout)
        if r:
            return True,d[2:]
        else:
            return False,''

    def _sendRFSIMCmd(self,cmd,timeout=3000):
        ucCmd = codecs.decode(cmd,'hex')
        cmdHead = 'A0%02X' % len(ucCmd)
        realCmd = codecs.decode(cmdHead,'hex') + ucCmd
        r , d = self._sendAndRecv(realCmd,timeout)
        if r:
            return True,d[2:]
        else:
            return False,''
    
    def connectRF(self):
        cmd = "90B0010000"
        r,d = self._sendPosCmd(cmd)
        if not r:
            return False
        return self._testRespStatusCode(d)
        
    def requestCard(self):
        self.cardphyid = ''
        #cmd = "400A000000"
        cmd="90B0045200"
        for i in range(10):
            c,r = self._sendPosCmd(cmd)
            if c :
                if len(r) < 2:
                    time.sleep(0.1)
                    continue
                if ord(r[0]) == 0x9C and ord(r[1]) == 0x03:
                    time.sleep(0.1)
                    continue
                # request card
                l = len(r)
                if ord(r[l-2]) == 0x9C and ord(r[l-1]) == 0x02:
                    self.cardphyid = codecs.encode(r[:4],'hex')
                    self._log("Request Card OK")
                    return True
                return False
            else:
                return False
       
        return False
        
    def selectAccounter(self):
        cmd = 'A0A40400104163636F756E74657220417070000000'
        st = self._sendPosCmd(cmd)
        if not st:
            print "Select Accounter Faild!"
            return False
        return True

    def _errorMsg(self,msg,ret):
        if DEBUG==1:
            print "%s [%02X%02X] " % (msg,ord(ret[0]),ord(ret[1]))
    
    def _loginCard(self,sect,key,keyflag):
        cmd = '4008%02X%02X06%s' % (sect,keyflag,key)
        c,r = self._sendPosCmd(cmd)
        if c:
            if ord(r[0]) == 0x90 and ord(r[1]) == 0x00:
                return True
            else:
                self._errorMsg("Login Card Error",r)
                return False

        self._log("Login Card Error")
        return False


    def _writeCard(self,block,data):
        return self._writeCardHex(block,codecs.encode(data,'hex'))

    def _writeCardHex(self,block,data):
        if len(data) != 32:
            print "write block [%d] data length not 16" % block
            return False
        cmd = '400202%02X10%s' % (block,data)
        if len(cmd) != (21*2):
            print "ERRRRRRRRRRR write card data length "
            return False
        c,r = self._sendPosCmd(cmd)
        if c:
            if ord(r[0]) == 0x90 and ord(r[1]) == 0x00:
                return True
            else:
                self._errorMsg("Write Card Error",r)
                return False

        print "write card no recv"
        return False

    def _unpackPackagePara(self,para):
        if len(para) != 16:
            return None
        paratuple = struct.unpack('>H',para[:1]) 
        paratuple = paratuple + struct.unpack('>I','\x00' + para[1:4])
        paratuple = paratuple + struct.unpack('>HIBBxxx',para[4:])
        p = CTRFSIM.PackagePara._make(paratuple)
        return p

    def _readCard(self,block):
        r,d = self._readCardHex(block)
        if r:
            return r,codecs.decode(d,'hex')
        return r,d

    def _readCardHex(self,block):
        cmd = '400201%02X00' % block
        c,r = self._sendPosCmd(cmd)
        if c:
            if len(r) == 0x12:
                if ord(r[16]) == 0x90 and ord(r[17]) == 0x00:
                    return True,codecs.encode(r[:16],'hex')
            else:
                self._errorMsg('Read Card Error',r)
                return False,''

        print "Read Card Error"
        return False,''

    def loginCardKeyA(self,sectno):
        if self.lastLoginKeyASect == sectno:
            return True
        st = self._loginCard(sectno,self.cardKeyA,CARDKEYA)
        if not st:
            return False
        self.lastLoginKeyASect = sectno
        return True
        
       
    def loginCardKeyB(self,sectno):
        if self.lastLoginKeyBSect == sectno:
            return True
        st = self._loginCard(sectno,self.cardKeyB,CARDKEYB)
        if not st:
            return False
        self.lastLoginKeyBSect = sectno
        return True

    def tryCard(self):
        sectno = (0,1,2,3,4,5,6,7,8,9)
        keyb = ['FFFFFFFFFFFF','C011A659DF36','000000000000','AB26395B44AD']
        print "test card key A..."
        for s in sectno:
            for key in keyb:
                st = self.requestCard()
                if not st:
                    print "未读到卡"
                    return
                st = self._loginCard(s,key,CARDKEYA)
                if st:
                    print "Login Card Success sectno[%d] key[%s]" % (s,key)
                    break
                

    def _formatCardMoney(self,sect):
        block = sect * 4
        data = "00000000FFFFFFFF00000000%02X%02X%02X%02X" % (block,(~block)&0xFF,block,(~block)&0xFF)
        print data
        st = self._writeCardHex(0,data)
        if not st:
            print "format main package error!"
            return False
        block = sect * 4 + 2
        data = "00000000FFFFFFFF00000000%02X%02X%02X%02X" % (block,(~block)&0xFF,block,(~block)&0xFF)
        st = self._writeCardHex(2,data)
        if not st:
            print "format backup package error!"
            return False
        
        return True


    def formatCard(self):
        orignCardKey = 'FFFFFFFFFFFF'
        # ctrlBit = '2A578D00'
        ctrlBit = '08778F69'

        for sect in range(16):
            st = self._loginCard(sect,orignCardKey,CARDKEYA)
            if not st:
                st = self.requestCard()
                if not st:
                    return False
                st = self._loginCard(sect,self.cardKeyB,CARDKEYB)
                if not st:
                    print "card has been used"
                    return False
                else:
                    print "card has already been format"
                    st = self._formatCardMoney(sect)
                    if not st:
                        return False
                    continue

            if sect in (self.packageSectNo,0xFF):
                st = self._formatCardMoney(sect)
                if not st:
                    return False 

                data = "%s%s%s" % (self.cardKeyA,ctrlBit,self.cardKeyB)
                st = self._writeCardHex(3,data)
                if not st:
                    return False
            else:
                data = "%s%s%s" % (self.cardKeyA,'7F078800',self.cardKeyB)
                if sect == 9:
                    initdata = '000000010000010000000000000000'
                    crc8 = CRC8_SMBUS.calcString(codecs.decode(initdata,'hex'))
                    initdata = '%s%02X' % (initdata, crc8 & 0xFF)
                    print "initialize data[%s]" % initdata
                else:
                    initdata = '00000000000000000000000000000000'

                for block in range(3):
                    if sect == 0:
                        continue
                    st = self._writeCardHex(block,initdata)
                    if not st:
                        return False
                st = self._writeCardHex(3,data) 
                if not st:
                    return False

        return True

    def recycleCard(self):
        ctrlBit = 'FF078069'
        orignCardKey = 'FFFFFFFFFFFF'
        for sect in range(16):
            st = self._loginCard(sect,self.cardKeyB,CARDKEYB)
            if not st:
                st = self.requestCard()
                if not st:
                    return False
                st = self._loginCard(sect,orignCardKey,CARDKEYA)
                if not st:
                    print "card has been used"
                    return False
                else:
                    print "card has already been recycled sect[%d]" % sect
                    continue 

            data = "%s%s%s" % (orignCardKey,ctrlBit,orignCardKey)
            st = self._writeCardHex(3,data)
            if not st:
                return False

        return True


    def checkDataCRC(self,data,crc):
        c = 0
        for x in data:
            c = c | (ord(x))

        if c == crc:
            return True
        return False

    def calcDataCRC(self,data):
        c = 0
        for x in data:
            c = c | (ord(x))
        return c

    def _data2BinaryStr(self,data):
        s = ''
        for x in data:
            s = s + str.format('{0:08b}',ord(x))
        return s

    def readRecord(self,idx):
        if idx == 0 or idx > 9:
            return None

        sectno = ((idx - 1) / 3) + 10
        st = self.loginCardKeyA(sectno)
        if not st:
            return None

        block = (idx-1) % 3
        st,recdata = self._readCard(block)
        if not st:
            print "Read Record Error"
            return None

        dataStr = self._data2BinaryStr(recdata[:4])
        print dataStr
        # 6 bit year
        # 4 bit month
        # 5 bit day
        # 5 bit hour
        # 6 bit min
        # 6 bit seconds
        datePart = (6,4,5,5,6,6)
        d = ()
        j = 0
        for i in datePart:
            d = d + int(dataStr[j:j+i],2)
            j = j+i

        d = d + struct.unpack('>IBB',recdata[4:10])
        d = d + codecs.encode(recdata[10:])
        print d
        rt = CTRFSIM._make(d)
        return rt


    def _checkTransProcess(self,para):
        if para.recidx == 0 or para.recidx > 9:
            return True

        record = self.readRecord(para.recidx)
        # if record.amount 

    def decMoney2(self,trans):
        st = self.loginCardKeyA(self.packageSectNo)
        if not st:
            print "Login for Inc Error"
            return False
        vec = []
        # restore money
        cmd = '4002050000'
        vec.append(cmd)
        cmd = '4002060100'
        vec.append(cmd)
        # Dec money
        currentDate = datetime.today().strftime("%d%H%M%S")
        money = codecs.encode(struct.pack('<i',trans.amount),'hex')
        cmd = "4002040010%s%s0000005501010000" % (money,currentDate)
        vec.append(cmd)

        # transfer , 2010 年
        currentDate = datetime.today().strftime("%S%M%H00%d%m02")
        cmd = "4002060007%s" % currentDate
        vec.append(cmd)

        for x in vec:
            st,rt = self._sendPosCmd(x)
            if not st:
                self._errorMsg("Dec money error",rt)
                return False
            if not self._testRespStatusCode(rt):
                self._errorMsg("Dec money error",rt)
                return False

        self.updateRecordIndex()
        return True

    def _testRespStatusCode(self,resp):
        pos = len(resp)
        if ord(resp[pos-2]) == 0x90 and ord(resp[pos-1]) == 0x00:
            return True
        return False

    def incMoney2(self,trans):
        st = self.loginCardKeyB(self.packageSectNo)
        if not st:
            print "Login for Inc Error"
            return False

        vec = []
        # restore money
        cmd = '4002050000'
        vec.append(cmd)
        cmd = '4002060100'
        vec.append(cmd)
        # Increment money
        currentDate = datetime.today().strftime("%d%H%M%S")
        money = codecs.encode(struct.pack('<i',trans.amount),'hex')
        cmd = "4002030010%s%s000000AA88010000" % (money,currentDate)
        vec.append(cmd)

        # transfer , 2010 年
        currentDate = datetime.today().strftime("%S%M%H00%d%m02")
        cmd = "4002060007%s" % currentDate
        vec.append(cmd)

        for x in vec:
            st,rt = self._sendPosCmd(x)
            if not st:
                self._errorMsg("Inc money error",rt)
                return False
            if not self._testRespStatusCode(rt):
                self._errorMsg("Inc money error",rt)
                return False
        self.updateRecordIndex()
        return True 


    def decMoney(self,trans):
        """ 扣款测试 """
        st = self.loginCardKeyA(self.packageParaSectNo)
        if not st:
            print "cannot read package para"
            return False
        mainPara = ''
        bakPara = ''

        st,mainPara = self._readCard(0)
        if not st:
            return False

        if not self.checkDataCRC(mainPara[:15],ord(mainPara[15])):
            # restore back para
            st,bakPara = self._readCard(1)
            if not st:
                print "card para error"
                return False
            mainPara = bakPara

        para = self._unpackPackagePara(mainPara)

        if mainPara != bakPara and para.transflag == 1:
            st = self._writeCard(1,mainPara)
            if not st:
                print "Backup package parameter Error!"
                return False

        print para
        record = None
        if para.transflag == 1:
            record = self._checkTransProcess()

    def incMoney(self,trans):
        """ 充值测试 """
        pass

    def _checkPackage(self,packData):
        x = struct.unpack('<iiibbbb',packData)
        if x[0] != (~x[1]) or x[0] != x[2]:
            print "Package check Error"
            return False,None
        return True,x

    def updateRecordIndex(self):
        #cmd = "4006000020"
        #st,rt = self._sendRFSIMCmd(cmd)
        #if not st:
        #    print "Read Mifare Header Error"
        #    return False

        #print codecs.encode(rt,'hex')
        #if not self._testRespStatusCode(rt):
        #    print "Read Mifare Header Error"
        #    return False
        #i = ord(rt[18]) + 1
        #if i >= 9:
        #    i = 0
        #data = rt[:18] + chr(i) + rt[19:]
        #cmd = "4006040020" + codecs.encode(data,'hex')
        #print "update[%s]" % cmd

        #st,rt = self._sendRFSIMCmd(cmd)
        #if not st:
        #    print "Update Mifare Header Error"
        #    return False

        #if not self._testRespStatusCode(rt):
        #    print "Update Mifare Header Error"
        #    return False
        
        st = self.loginCardKeyA(9)
        if not st:
            return False
        st ,rt = self._readCard(0)
        if not st:
            return False
        idx = ord(rt[0]) + 1
        if idx >= 9:
            idx = 0
        data = chr(idx) + rt[1:15]
        data = data + chr(CRC8_SMBUS.calcString(data))
        st = self._writeCard(0,data)
        if not st:
            return False
        st = self.loginCardKeyA(self.packageSectNo)
        if not st:
            return False
        return True


    def getBalance(self,trans):
        cmd = "4006000020"
        st,rt = self._sendRFSIMCmd(cmd)
        if not st:
            print "Read Mifare Header Error"
            return False

        print codecs.encode(rt,'hex')
        if not self._testRespStatusCode(rt):
            print "Read Mifare Header Error"
            return False

        trans.recordidx = ord(rt[18])

        st = self.loginCardKeyA(self.packageSectNo)
        if not st:
            return False

        st,d = self._readCard(0)
        if not st:
            return False
        x = None
        st,x = self._checkPackage(d)
        if not st:
            return False
        trans.cardbefbal = x[0]

        st,d = self._readCardHex(2)
        print "backup package[%s]" % d
        return True
        
    def activateCard(self):
        if not self.requestCard():
            return False
        
        cmd = "A0A404F0104D696661726531332041707000000000"
        r,d = self._sendRFSIMCmd(cmd)
        if not r:
            return False
        
        return self._testRespStatusCode(d)



class CTTest:
    def __init__(self):
        self.rfsim = None

    def openDevice(self):
        self.rfsim = CTRFSIM()
        try:
            self.rfsim.open(PORTNO-1,115200)
        except:
            print "open device error "
            self.rfsim = None
            return False
        return True
        
    def doMyTest(self):
        st = self.rfsim.requestCard()
        if not st :
            print "please put your card..."
            return
        st = self.rfsim.formatCard()
        if not st:
            return
        print "format ok..."

    def doTestRecycle(self):
        st = self.rfsim.recycleCard()
        if not st:
            return
        print "recycle ok..."

    
    def _dumpRecord(self):
        st,rt = self.rfsim._readCardHex(2)
        print "backup [%s]" % rt
        for sect in (0,2,8,9):
            st = self.rfsim.loginCardKeyA(sect)
            if not st:
                print "login sect %d error" % sect
                return
            for block in (0,1,2):
                st,rt = self.rfsim._readCardHex(block)
                if not st:
                    return 
                print "sect[%d]block[%d][%s]" % (sect,block,rt)


    def doTestMoney(self):
        st = self.rfsim.requestCard()
        if not st:
            print "please put your card..."
            return

        trans = TransPack()
        st = self.rfsim.getBalance(trans)
        if not st:
            return 
        print "card balance is [%d]" % trans.cardbefbal

        # dec Money
        trans.amount = 5000
        if not self.rfsim.incMoney2(trans):
            return
        print "Inc money[%d] success" % trans.amount
        st = self.rfsim.getBalance(trans)
        if not st:
            return
        print "after inc balance[%d]" % trans.cardbefbal

        self._dumpRecord()
                
        st = self.rfsim.getBalance(trans)
        if not st:
            return
        trans.amount = 100
        if not self.rfsim.decMoney2(trans):
            return
        st = self.rfsim.getBalance(trans)
        if not st:
            return
        print "after dec balance[%d]" % trans.cardbefbal


        self._dumpRecord()
        
    def testActivateCard(self):
        self.rfsim.connectRF()
        self.rfsim.activateCard()
        sys.exit(0)

    def testWriteCard(self):
        self.rfsim.selectAccounter()
        while True:
            ch = msvcrt.getch()
            if ord(ch) == 0x0D:
                break
        print "Are you want format card(N/y)"
        ch = msvcrt.getch()
        if ch in ('Y','y','yes'):
            print "Waiting format your card..."
            self.doMyTest()
        
        print "Are you want test card pay(N/y)"
        ch = msvcrt.getch()
        if ch in ('Y','y','yes'):
            print "Waiting test your card..."
            self.doTestMoney()

        print "Are you want recycle card(N/y)"
        ch = msvcrt.getch()
        if ch in ('Y','y','yes'):
            print "Waiting recycle your card..."
            self.doTestRecycle()

        self.rfsim.close()
        print "Close Device..."
        sys.exit(0) 

    def mytest(self):
        if not self.openDevice():
            sys.exit(1)
        print "Open Device Success..."
        print "Please put your card and press any key...(W/A)"
        ch = msvcrt.getch()
        if ch in ('A','a'):
            self.testActivateCard()
        else:
            #self.testWriteCard()
            self.rfsim.tryCard()


if __name__=='__main__':
    t = CTTest()
    t.mytest()


