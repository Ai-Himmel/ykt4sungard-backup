#!/usr/bin/python
# -*- coding: GB2312 -*-
import socket,string,time

HOST=''
PORT=3000

def do_alide(conn):
	conn.settimeout(1)
	data = conn.recv(1024)
	if not data : return
	print 'reqt :' + data
	print data[5:9]
	if data[5:9] == '0001':
		resp = '0014200010000000000000000' + data[25:67] \
		+'000010007281430392009072800000001830001000100000000000000000000000000000000'
	else:
		resp = '0014200020000000000000000' + data[25:67] \
		+'000010007281430392009072800000001830001000100000000000000000000000000000000'
	print 'resp :' + resp
	conn.send(resp)
	
	
def parse_payment(data,req):
	l = string.split(data,':')
	i = 1
	while i < len(l):
		if l[i][0] == 'i':
			req.append(int(l[i+1]))
		elif l[i][0] == 's':
			req.append(l[i+1])
		elif l[i][0] == 'd':
			req.append(float(l[i+1]))
		else:
			return False
		i+=2
	return True
	
def do_payment(conn):
	conn.settimeout(5)
	req = []
	data = conn.recv(1024)
	
	if not data : return
	print 'reqt ' + data
	
	
	#elif req[2] == '1001':
	#	resp = ':s%d:%s:s%d:%s:s%d:%s:s4:张三:i4:1000:s%d:%s:i3:0:s8:success' % (len(req[1]),req[1],len(req[2]),req[2],len(req[3]),req[3]
	#	,len(req[13]),req[13])
	
	parse_payment(data,req)
	if req[2] == '1000':
		resp = ':s%d:%s:s%d:%s:s%d:%s:s%d:%s:i3:100:s4:1000' % (len(req[1]),req[1],len(req[2]),req[2],len(req[3]),req[3]
		,len(req[5]),req[5])
	elif req[2] == '1001':
		time.sleep(3)
		resp = ''
	elif req[2] == '1002':
		resp = ''
		
	p = ':i2:%d%s' % (len(resp),resp)
	print 'resp ' + p
	conn.send(p)
			
def do_server():
	s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	s.bind((HOST,PORT))
	s.listen(1)
	print "start listen..."
	while True:
		conn,addr = s.accept()
		do_payment(conn)
		conn.close()
	
	
def test_func():
	req = []
	parse_payment(':i3:102:s3:001:s4:1000:s5:12345:s9:200901010:s4:张三:i4:4100:s8:aaaaaaaa:s32:860601DDA3DE0E6A8544CE169FDEED07',req)
	print req
	
if __name__=="__main__":
	do_server()
	#test_func()
	
	