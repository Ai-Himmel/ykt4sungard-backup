#! /usr/bin/env python
# $Id: testclient.py 15 2005-08-22 02:39:12Z cash $
import socket 
import binascii
from struct import *
import md5
#from Crypto.Cipher import DES
import sys
import os
import getopt

SEND_DATA_STRUCT = 'liilibb'

STATIC_KEY = '54869752'

HOST = '10.49.188.20'
PORT = 5000
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

def genbuf(buf,index,count):
    # Md5
    m = md5.new()
    m.update(buf)
    crc = m.digest()
    # encrypt
    #buf = genencbuf(buf,genkey())

    # calc length
    databuf_len = len(buf)
    # next pack
    next_pack = count 
    # count
    card_count = 2
    # pack index
    p_index = index
      
    header = pack(SEND_DATA_STRUCT,socket.htonl(databuf_len),
    	socket.htonl(FUNC_NO),socket.htonl(p_index),
    	socket.htonl(card_count),socket.htonl(next_pack),0,0)
    #data
    databuf = header + crc + buf
    print binascii.b2a_hex(crc)
    # data
    print "length of data [%d] : length of buf [%08x] " % (databuf_len , len(databuf))
    return databuf

def genoutput(buf):
    value = unpack('ii',buf)
    return map(lambda x: socket.ntohl(x),value)

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
	data = sock.recv(1024)
	if data:
		print genoutput(data)


def dotest():
	global HOST,PORT
	optlist, args = getopt.getopt(sys.argv[1:],':h:p:')
	for n,v in optlist:
		if n == "-h":
			HOST = v
		elif n == "-p":
			PORT = int(v)
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
	sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	sock.connect((HOST,PORT))
	for x in range(len(args)):
		senddatafile(sock,args[x],x,pack_count)
		pack_count -= 1
	sock.close()


if __name__ == "__main__":
	dotest()

