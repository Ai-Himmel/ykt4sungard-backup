#!/usr/bin/python
# :vim: codepage=936:
import socket

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
			
def do_server():
	s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	s.bind((HOST,PORT))
	s.listen(1)
	print "start listen..."
	while True:
		conn,addr = s.accept()
		do_alide(conn)
		conn.close()
	
	
if __name__=="__main__":
	do_server()