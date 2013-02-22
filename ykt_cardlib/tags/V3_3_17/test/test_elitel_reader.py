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
            
        #self.ser.setDTR(0)
        return True
        
    def close(self):
        if self.ser <> None:
            self.ser.close()
        
    def flush(self):
        self.ser.flushInput()
        self.ser.flushOutput()
        
            
    def test(self):
        #addr2 = addr_str[4:] + addr_str[2:4] + addr_str[0:2]
        cmd = "800590B0010000"
        answer = codecs.decode(cmd,'hex')
        self.flush()
        time.sleep(1)
        self.ser.write(answer)
        
        total = 0
        full_data = ''
        while True:
            print "waiting ..."
            l = self.ser.inWaiting()
            if l == 0: 
                continue
            print "recv ..."
            answer=self.ser.read(l)
            total += l
            full_data += answer
            p = codecs.encode(answer,'hex')
            print 'recv [%s]' % p
            if total >= 4:
                break
               
        return codecs.encode(full_data,'hex')
            
   
    
def mytest():
    sertest = Z18POSTest()
    try:
        sertest.open(17,115200)
        sertest.test()

    except:
        print "error "
        raise
    finally:
        sertest.close()
    
if __name__=='__main__':
    mytest()
    
