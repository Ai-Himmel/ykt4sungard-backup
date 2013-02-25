#! /usr/bin/env python

import socket 
import binascii
from struct import *
import md5
#from Crypto.Cipher import DES
import sys

SEND_DATA_STRUCT = 'liili'

STATIC_KEY = '54869752'

HOST = '127.0.0.1'
PORT = 6001
MAC = '000D61634879'
FUNC_NO = 400000

#def _strxor(s1,s2):
#    return "".join(map(lambda x,y: chr(ord(x) ^ ord(y)),s1,s2))
#
#def _paddingbuf(buf,padchar='X',sect_len=8):
#    padding = ''
#    for x in range(sect_len):
#        padding += padchar
#    pad_len = len(buf) % sect_len
#    return buf + padding[pad_len:]
#
#def genencbuf(buf,key):
#    deskey = binascii.a2b_hex("%016X"%0)
#    buf = _paddingbuf(buf)
#    key = _paddingbuf(key)
#    x = 0;
#    while x < len(key):
#        deskey = _strxor(deskey,key[x:x+8])
#        x = x + 8
#    des = DES.new(deskey,DES.MODE_ECB)
#    return des.encrypt(buf)
#
#def genkey():
#    d = DES.new(STATIC_KEY,DES.MODE_ECB)
#    plain = '%s%d' % (HOST , PORT)
#    plain = _paddingbuf(plain)
#    return d.encrypt(plain)

def genbuf(buf,index,last):
    # Md5
    m = md5.new()
    m.update(buf)
    crc = m.digest()
    # encrypt
    #buf = genencbuf(buf,genkey())

    # calc length
    databuf_len = len(buf)
    # next pack
    next_pack = last
    # count
    card_count = 2
    # pack index
    p_index = index
      
    header = pack(SEND_DATA_STRUCT,databuf_len,FUNC_NO,p_index,card_count,next_pack)
    #data
    databuf = header + crc + buf
    print binascii.b2a_hex(crc)
    # data
    print "length of data [%d] : length of buf [%08x] " % (databuf_len , len(databuf))
    return databuf

def genoutput(buf):
    return unpack('ii',buf)

def dotest():
    datafile = "data1.dat"
    if( len(sys.argv) > 1 ):
        datafile = sys.argv[1]
    file_handle = None
    try:
        file_handle = open(datafile,"r")
    except:
        print "Cannot open data file %s" % datafile
        sys.exit(1)
    file_content = ""
    line = file_handle.readline()
    while line: 
        line = line.strip('\n\r\t')
        file_content += line
        line = file_handle.readline()
    print "content [%d] %s" % (len(file_content),file_content)
    file_handle.close()
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.connect((HOST,PORT))
    # send pack 1
    sock.send(genbuf(file_content,0,1))
    data = sock.recv(1024)
    if data:
        print genoutput(data)

    sock.send(genbuf(file_content,1,0))
    data = sock.recv(1024)
    if data:
        print genoutput(data)

    sock.close()

if __name__ == "__main__":
    dotest()

