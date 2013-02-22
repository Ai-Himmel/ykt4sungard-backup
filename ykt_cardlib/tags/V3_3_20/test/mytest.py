#!/usr/bin/env python
# vim: encoding=cp936:

import serial,time,string,codecs,msvcrt
import binascii,binhex
import pyDes

if __name__=="__main__":
    s = '4D69666172653420417070'
    i = 0
    a = ''
    while i < len(s):
        x = int(s[i:i+2],16)
        a = a + chr(x)
        i = i + 2
    print a