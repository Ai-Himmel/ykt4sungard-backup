#! /usr/bin/env python
# -*- coding: utf-8 -*-
# $Id: testclient.py 15 2005-08-22 02:39:12Z cash $
import socket 
import binascii
from struct import *
import md5
#from Crypto.Cipher import DES
import sys
import os
import getopt

SEND_DATA_STRUCT = 'iiilibb'
RECV_DATA_STRUCT = 'iiili'

STATIC_KEY = '54869752'

HOST = '127.0.0.1'
PORT = 5000
MAC = '000D61634879'
FUNC_NO = 400000

def genbuf(buf,index,count):
    # Md5
    m = md5.new()
    m.update(buf)
    crc = m.digest()
    # encrypt
    #buf = genencbuf(buf,genkey())
    # calc length
    databuf_len = len(buf)
    if (count > 1):
        next_pack = 1
    else:
        next_pack = 0

    # pack index
    p_index = index

    header = pack(SEND_DATA_STRUCT,socket.htonl(databuf_len),
                  socket.htonl(FUNC_NO),socket.htonl(p_index),
                  socket.htonl(1),socket.htonl(next_pack),0,0)
    #data
    databuf = header + crc + buf
    print binascii.b2a_hex(crc)
    # data
    print "length of data [%d] : length of buf [%08x] " % (databuf_len , len(databuf))
    return databuf

def genoutput(buf):
    print "buffer len %d [%s]" % (len(buf) , binascii.b2a_hex(buf))
    input = unpack(SEND_DATA_STRUCT,buf[:22])
    value = map(lambda x: socket.ntohl(x),input[:5])
    print value
    if input[5] == 1:
		print "加密数据"

    if value[3] == 0:
        print "业务处理成功"
        if value[0] > 0 :
            print "业务返回结果[%d][%s]" % (len(buf[38:]),buf[38:])

    else:
        print "业务处理失败 返回码[%d] ,返回信息[%s]" % (value[3],buf[38:])


def senddatafile(sock,filename,index,count):
    file_handle = None
    try:
        file_handle = open(filename,"r")
    except:
        print "Cannot open data file %s" % filename
        sys.exit(1)

    file_content = ""
    line = file_handle.readline()
    while line: 
        line = line.strip('\n\r\t')
        file_content += line
        line = file_handle.readline()

    file_handle.close()

    sock.send(genbuf(file_content,index,count))
    data = sock.recv(8129)
    if data:
        genoutput(data)

def dotest():
    global HOST,PORT
    optlist, args = getopt.getopt(sys.argv[1:],':h:p:')
    for n,v in optlist:
        if n == "-h":
            HOST = v
        elif n == "-p":
            PORT = int(v)
		elif n == '-f':
			FUNC_NO = int(v)
        else:
            print "parameter error"
            sys.exit(1)

    if( len(args) <= 0 ):
        print "no data file was specified"
        sys.exit(1)

    for x in range(0,len(args)):
        if(not os.path.exists(args[x])):
            print "data file %s was not found." % args[x]

    pack_count = len(args)
    print "tatol package %d " % pack_count
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.connect((HOST,PORT))
    for x in range(len(args)):
        senddatafile(sock,args[x],x,pack_count)
        pack_count -= 1

    sock.close()


if __name__ == "__main__":
    dotest()

