#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex
from datetime import datetime,timedelta


class Z18POSTest:
    def __init__(self):
        self.ser = None
        self.device_id = ''
        
    def open(self,port=0,baud=57600):
        self.ser = serial.Serial()
        self.ser.baudrate = baud
        self.ser.port = port
        self.ser.timeout = 20
        try:
            self.ser.open()
        except:
            return False
            
        self.ser.setDTR(0)
        return True
        
    def close(self):
        if self.ser <> None:
            self.ser.close()
        
    def flush(self):
        self.ser.flushInput()
        self.ser.flushOutput()
        
    def _my_send_data(self,data):
        pad = 22
        start = 0
        end = pad
        i = 0
        data_len = len(data)
        
        for i in range(10):
            self.ser.write(data[0])
            ret = self.ser.read(1)
            if ret != 'G' :
                time.sleep(0.02)
                continue
            break
        if i == 10:
            raise ValueError,"send cmd timeout"
        
        print "send header ok"
        start = 1
        end = start + pad
        while True:
            if end > data_len:
                end = data_len
                self.ser.write(data[start:end])
                break
            else:
                self.ser.write(data[start:end])
                
            start += pad
            end = start+pad
            ret = self.ser.read(1)
            if ord(ret) <> 0x47:
                print "recv error! [%s]" % ret
                return
            else:
                print "send pack[%d] ok" % start
                time.sleep(0.01)
            
    def _my_recv_data(self):
        a = self.ser.read(3)
        if len(a) == 0:
            raise ValueError,"recv timeout"
            
        total = int(codecs.encode(a[1:],'hex'),16)
        for i in range(20):
            l = self.ser.inWaiting()
            if l == 0:
                time.sleep(0.1)
                continue
            a += self.ser.read(l)
            total -= l
            if total == 0:
                break
        print a
        p = codecs.encode(a,'hex')
        print p
        if ord(a[-1]) <> 0xC3:
            raise ValueError,"recv error"
        
        
        return p
        
        
    def calc_sum(self,data):
        x = 0
        i = 0
        if (len(data) % 2 ) <> 0:
            raise TypeError,"not Odd-value"

        while i < len(data)/2:
            a = int(data[i*2:i*2+2],16) & 0xFF
            x = (a + x )&0xFF
            i += 1

        return x
    
    def calc_cmd_sum(self,data):
        return self.calc_sum(data[6:])
        
    def calc_sum_str(self,data):
        x = self.calc_sum(data)
        r = '%02X' % x
        return r
        
    def check_cmd_crc(self,data):
        crc = self.calc_sum_str(data[6:-4])
        x = str.upper(data[-4:-2])
        print "calc[%s]data[%s]" % (crc ,x )
        if crc == x:
            return True
        return False
        
    def get_cmd_ret(self,data,cmd=0):
        if len(data) == 0:
            raise ValueError,"response data is empty"
        if cmd > 0:
            r = int(data[6:8],16)
            if r <> cmd:
                raise ValueError,"response data cmd incorrect"
        r = int(data[8:10],16)
        if r <> 0:
            print "command [%s] error,ret[%02X]" % (data[6:8],r)
        return r
        
    def get_bcd_datetime(self,curr_time):
        ret = ''
        i = 0
        if (len(curr_time) % 2) != 0:
            raise ValueError,"datetime not Odd-value"
        n = len(curr_time) >> 1
        while i < n:
            reg1 = int(curr_time[i*2])
            reg2 = int(curr_time[i*2+1])
            ret = "%s%02X" % (ret , ((reg1<<4)&0xF0) + (reg2&0x0F))
            i += 1
            
        return ret
            
    def testReadEEPROM(self,addr,len=48):
        #addr2 = addr_str[4:] + addr_str[2:4] + addr_str[0:2]
        if len >= 512:
            raise ValueError, "input data len error!"

        if len >= 256:
            answer='C00008A100%02X03%06XC1' % (len - 256 , addr)
            expect_len = len + 9
        else:
            answer='C00007A1%02X03%06XC1' % ( len ,addr)
            expect_len = len + 8
            
        print 'send[%s]' % answer
        answer = codecs.decode(answer,'hex')
        #print codecs.encode(answer,'hex')
        self.flush()
        time.sleep(1)
        self._my_send_data(answer)
        
        total = 0
        full_data = ''
        while True:
            l = self.ser.inWaiting()
            if l == 0: 
                continue
            answer=self.ser.read(l)
            print answer
            total += l
            full_data += answer
            p = codecs.encode(answer,'hex')
            print 'recv [%s]' % p
            if total >= expect_len:
                break
                
        print 'full data[%s]' % codecs.encode(full_data,'hex')
        start = (expect_len-len-2)*2
        return codecs.encode(full_data,'hex')[start:-4]
            
    def testSetTimer(self):
        # 校对时钟
        dt = datetime.now() #+ timedelta(days=1)
        curr_time = dt.strftime("%Y%m%d%H%M%S")
        #curr_time = '20090701102000'
        answer='C0000CC49907' + self.get_bcd_datetime(curr_time)
        #answer='C00DC29908' + '0000AABB' + '0000BBAA'
        crc = self.calc_cmd_sum(answer)
        p = '%s%02XC1' % (answer,crc)
        print "len[%d][%s]" % (len(p),p)
        answer = codecs.decode(p,'hex')
        #print codecs.encode(answer,'hex')
        self.flush()
        self._my_send_data(answer)
        answer=self.ser.read(6)
        #print answer
        p = codecs.encode(answer,'hex')
        print p
        print 'len[%d][%s]' % (len(p),p)
        self.get_cmd_ret(p,0xC4)
        
    def testStart(self):
        print 'waiting for press enter key...'
        while True:
            k = msvcrt.getch()
            if ord(k) == 0x0D:
                break
        
        print 'waiting for 3 secs ...'
        self.flush()
        
        time.sleep(3)
        while True:
            l = self.ser.inWaiting()
            if l == 0:
                break
            answer=self.ser.read(l)
            print answer
            
    
    def testPhyId(self,phyid='1000BBA2'):
        # 设置物理ID  
        if len(phyid) <> 8:
            raise ValueError,"physical id error"

        answer='C0000DC29908' + str.upper(self.device_id) + phyid
        #answer='C00DC29908' + '0000AABB' + '0000BBAA'
        crc = self.calc_cmd_sum(answer)
        p = '%s%02XC1' % (answer,crc)
        print p
        answer = codecs.decode(p,'hex')
        #print codecs.encode(answer,'hex')
        self.flush()
        self._my_send_data(answer)
        answer=self.ser.read(6)
        print answer
        p = codecs.encode(answer,'hex')
        print 'len[%d][%s]' % (len(p),p)
        self.get_cmd_ret(p,0xC2)
        
        # 设置时钟
        #answer='C49907'
        
        
    def mytest(self):
        #answer = '\x55\xaa'
        #print answer
        #print codecs.encode(answer,'hex')
        self.flush()
        while True:
            l = self.ser.inWaiting()
            if l == 0:
                break
            answer=self.ser.read(l)
            print answer
            
        answer = 'C00003C501C1'
        print answer
        self._my_send_data(codecs.decode(answer,'hex'))
        answer=self.ser.read(12)
        print answer
        p = codecs.encode(answer,'hex')
        print 'len[%d][%s]' % (len(p),p)
        
        if not self.check_cmd_crc(p):
            print 'crc not right'
        else:
            self.device_id = str.upper(p[12:20])
            print 'device phyid[%s]' % self.device_id
            
    def testSetWorkKey(self):
        # 设置工作密钥
        curr_time = datetime.now().strftime("%Y%m%d%H%M%S")
        answer='C00014C301000E' + curr_time[2:] + '4344334539413846' #'8E8BFC8FF68FF488'
        #answer='C00014C301000E' + curr_time[2:] + '5CF24B0867CE19DA'
        crc = self.calc_cmd_sum(answer)
        p = '%s%02XC1' % (answer,crc)
        print p
        answer = codecs.decode(p,'hex')
        self.flush()
        self._my_send_data(answer)
        time.sleep(1)
        p = self._my_recv_data()
        # answer=self.ser.read(6)
        # p = codecs.encode(answer,'hex')
        # print 'len[%d][%s]' % (len(p),p)
        # self.get_cmd_ret(p,0xC3)
        
        # self.testReadEEPROM(0x40)
        # 测试不能更新
        # answer='C00014C301000E0906210000018E8BFC8FF68FF488'
        # crc = self.calc_cmd_sum(answer)
        # p = '%s%02XC1' % (answer,crc)
        # print p
        # answer = codecs.decode(p,'hex')
        # self.flush()
        # self._my_send_data(answer)
        # time.sleep(1)
        # answer=self.ser.read(5)
        # print answer
        # p = codecs.encode(answer,'hex')
        # print 'len[%d][%s]' % (len(p),p)
        # self.get_cmd_ret(p,0xC3)
        # self.testReadEEPROM(0x40)
        
    def testConsumeParam(self):
        # 设置工作密钥
        curr_time = datetime.now().strftime("%Y%m%d%H%M%S")
        fee = 100 # 1 元
        col_day = 45 # 天
        consume_interval = 60 * 1# 60 秒
        answer = 'C00011B2010C%s%06X%02X%04X' % (curr_time[2:],fee,col_day,consume_interval)
        crc = self.calc_cmd_sum(answer)
        p = '%s%02XC1' % (answer,crc)
        print p
        answer = codecs.decode(p,'hex')
        self.flush()
        self._my_send_data(answer)
        time.sleep(1)
        answer=self.ser.read(6)
        #print answer
        p = codecs.encode(answer,'hex')
        print 'len[%d][%s]' % (len(p),p)
        self.get_cmd_ret(p,0xB2)
        
        #self.testReadEEPROM(0x60)
        
    def testClearSerial(self):
        # 清除流水
        curr_time = datetime.now().strftime("%Y%m%d%H%M%S")
        answer = 'C0000CB155AA06%s' % curr_time[2:]
        crc = self.calc_cmd_sum(answer)
        p = '%s%02XC1' % (answer,crc)
        print p
        answer = codecs.decode(p,'hex')
        self.flush()
        self._my_send_data(answer)
        time.sleep(1)
        answer=self.ser.read(5)
        #print answer
        p = codecs.encode(answer,'hex')
        print 'len[%d][%s]' % (len(p),p)
        self.get_cmd_ret(p,0xB1)
        self.testReadEEPROM(0x10)
        
    def testSetWelcome(self,msg='Sungard一卡通'):
        # 清除流水
        answer = 'B600%02X%s' % (len(msg),codecs.encode(msg,'hex'))
        p = 'C0%04X%sC1' % (len(answer)+1,answer)
        print p
        answer = codecs.decode(p,'hex')
        self.flush()
        self._my_send_data(answer)
        time.sleep(1)
        answer=self.ser.read(6)
        print answer
        # p = codecs.encode(answer,'hex')
        # print 'len[%d][%s]' % (len(p),p)
        # self.get_cmd_ret(p,0xB6)
        # self.testReadEEPROM(0xD0,16)
    
    def _print_record(self,rec):
        print "ver: [%s]" % rec[:2]
        print "device id : [%s]" % rec[2:10]
        print "serial no : [%d]" % int(rec[10:18],16)
        print "card no : [%d]" % int(rec[18:24],16)
        print "in balance: [%d]" % int(rec[24:32],16)
        print "amount : [%d]" % int(rec[32:38],16)
        print "trace count : [%d]" % int(rec[38:42],16)
        print "date time : [%s]" % rec[42:54]
        print "tx mark : [%s]" % rec[54:56]
        print "tx type : [%s]" % rec[56:58]
        print "purse no : [%s]" % rec[58:60]
        print "pre device id : [%s]" % rec[60:68]
        print "pre date time : [%s]" % rec[68:76]
        print "pre in bala : [%d]" % int(rec[76:84],16)
        print "pre amount : [%d]" % int(rec[84:90],16)
        print "pre mark : [%s]" % rec[90:92]
        print "reserved : [%s]" % rec[92:122]
        print "crc : [%s]" % rec[122:126]
        print "tx status[%s]" % rec[126:128]
        return int(rec[10:18],16)
        
    def testReadSerial(self):
        print "测试读取流水"
        begin_addr = 0x030EC0
        rec_idx = 21
        begin_addr += rec_idx * 64
        print 'read serial [%d]' % rec_idx
        rec = self.testReadEEPROM(begin_addr,64)
        
        self._print_record(rec)
        
        
        
    def testCardRight(self):
        # 清除流水
        test_right = 31
        curr_time = datetime.now().strftime("%Y%m%d%H%M%S")
        answer = 'B4990300%s' % curr_time[2:]
        for i in range(32):
            low = i*8
            hi = (i+1)*8
            if (low < test_right) and (test_right<=hi):
                #answer += 'FD'
                answer += 'FF'
            else:
                answer += 'FF'
        for i in range(256):
            if i == test_right - 1:
                answer+='64'
            else:
                answer += '64'

        crc = self.calc_sum(answer)
        p = 'C0%04X%s%02XC1' % (len(answer)/2+2,answer,crc)
        print p
        answer = codecs.decode(p,'hex')
        self.flush()
        print "start send"
        self._my_send_data(answer)      
        print "send ok!" 
        time.sleep(2)
        answer=self.ser.read(6)
        print answer
        p = codecs.encode(answer,'hex')
        print 'len[%d][%s]' % (len(p),p)
        self.get_cmd_ret(p,0xB4)
        
    def testConfirmSerial(self,serial_no):
        answer = 'C00009560104%08X' % serial_no
        crc = self.calc_cmd_sum(answer)
        answer = '%s%02XC1' % (answer,crc)
        print answer
        self._my_send_data(codecs.decode(answer,'hex'))
        p = self._my_recv_data()
        print p
        
    def testCollectSerial(self):
        answer = 'C000045500'
        crc = self.calc_cmd_sum(answer)
        answer = '%s%02XC1' % (answer,crc)
        print answer
        self._my_send_data(codecs.decode(answer,'hex'))
        time.sleep(3)
        p = self._my_recv_data()
        serial_no = self._print_record(p[12:])
        
        print "press [Y] confirm serial[%d]" % serial_no
        r = msvcrt.getch()
        if r == 'Y' or r == 'y':
            print 'confirm serial'
            self.testConfirmSerial(serial_no)
        
    def testUpdateCollDate(self):
        answer = 'C00004B799'
        crc = self.calc_cmd_sum(answer)
        answer = '%s%02XC1' % (answer,crc)
        print answer
        self._my_send_data(codecs.decode(answer,'hex'))
        p = self._my_recv_data()
        print p
        self.testReadEEPROM(0x80,6)
        
    def testClearBlklist(self):
        answer = 'C00005B39900'
        crc = self.calc_cmd_sum(answer)
        answer = '%s%02XC1' % (answer,crc)
        print answer
        self._my_send_data(codecs.decode(answer,'hex'))
        p = self._my_recv_data()
        print p
        
    def testSetBlackCard(self):
        answer = 'C00009B3000100303900'
        crc = self.calc_cmd_sum(answer)
        answer = '%s%02XC1' % (answer,crc)
        print answer
        self._my_send_data(codecs.decode(answer,'hex'))
        p = self._my_recv_data()
        print p
        
        
    
def mytest():
    sertest = Z18POSTest()
    try:
        sertest.open()
        sertest.testStart()
        #print sertest.check_cmd_crc('0907011526050003E80A0960FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF')
        sertest.testReadEEPROM(0x000010,40)
        
        # sertest.mytest()
        # sertest.testPhyId()
        # sertest.testSetTimer()
        # sertest.testConsumeParam()
        # sertest.testSetWelcome("一卡通")
        # sertest.testClearSerial()
        # sertest.testSetWorkKey()
        # sertest.testCardRight()
        # sertest.testReadSerial()
        # sertest.testReadEEPROM(0x40,26)
        # sertest.testReadEEPROM(0x030DA0,32)
        # print sertest.calc_sum('C4990720090622215509');
        # sertest.testCollectSerial()
        # sertest.testUpdateCollDate()
        # sertest.testSetBlackCard()
        

    except:
        print "error "
        raise
    finally:
        sertest.close()
    
if __name__=='__main__':
    mytest()
    
