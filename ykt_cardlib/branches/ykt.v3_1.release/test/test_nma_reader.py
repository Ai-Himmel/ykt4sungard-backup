#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt,sys
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
        except Exception as e:
            print e
            return False
            
        #self.ser.setDTR(0)
        return True
        
    def close(self):
        if self.ser <> None:
            self.ser.close()
        
    def flush(self):
        self.ser.flushInput()
        self.ser.flushOutput()
        		
    def test_cmd(self):
        # Reset
        resetWaiting = 10
        #print "waiting for reset..."
        #self.test(('Reset','A112'))
        #print "reset ok waiting %d seconds..." % resetWaiting
        #time.sleep(resetWaiting)
        #return
        cmd_str = [
            ('Reset','A112',10.0,0),
            ('PowerOff','A232',3.0,1),
            ('ConnRF1','A23103E8',0.5,1),
            ('ConnRF2','A23103E8',0,1),
            ('SelectADF','A23300A4040010D1560001018003800000000100001002',0.0,1),
            ('ReadFile','A23300B095001E',0.0,1)]
        
        for cmd in  cmd_str:
            if cmd[3] == 1:
                e,r = self.test(cmd)
                
                if r == False:
                    print "Execute failed!"
                    return
                    
                print "waiting for next command [%.2f]s..." % cmd[2]
                if cmd[2] > 0.0:
                    time.sleep(cmd[2])
		
    def pack_cmd(self,cmd):
        lrc = 0
        for x in range(len(cmd)):
            v = ord(cmd[x])
            lrc = (lrc ^ (v & 0xFF)) & 0xFF
        
        str_cmd = '02%02X%02X%s%02X03' % (len(cmd)/256,len(cmd)%256,codecs.encode(cmd,'hex'),lrc)
        return codecs.decode(str_cmd,'hex')
            
    def test(self,command):
        #addr2 = addr_str[4:] + addr_str[2:4] + addr_str[0:2]
        #cmd = "800590B0010000"
        cmd = command[1]
        answer = codecs.decode(cmd,'hex')
        self.flush()
        time.sleep(1)
        answer = self.pack_cmd(answer)
        self.ser.write(answer)
        
        total = 0
        print "[%s]send [%s]" % (command[0],codecs.encode(answer,'hex').upper())
        full_data = ''
        while True:
            #print "waiting ..."
            l = self.ser.inWaiting()
            if l == 0: 
                continue
            #print "recv ..."
            answer=self.ser.read(l)
            total += l
            full_data += answer
            p = codecs.encode(answer,'hex')
            #print 'recv [%s]' % p
            if ord(answer[-1]) == 0x03:
                break
             
        e = codecs.encode(full_data,'hex').upper()
        print "[%s]recv [%s]" % (command[0],e)
        if e[:2] != '02' or e[-2:] != '03':
            return e,False
        if e[6:10] != '0000':
            return e,False
            
        return e,True
   
    
def mytest():
    sertest = Z18POSTest()
    try:
        if not sertest.open(5,115200):
            print "Open port ERR"
            sys.exit(1)
            
        sertest.test_cmd()
        
    except Exception as ex:
        print ex
        raise
    finally:
        sertest.close()
    
if __name__=='__main__':
    mytest()
    
