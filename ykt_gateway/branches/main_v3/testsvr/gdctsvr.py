#!/usr/env/python
# -*- coding: GB2312 -*-
import socket,string,time
from datetime import datetime

"""
广州大学城空中充值模拟服务端
"""
HOST='0.0.0.0'
PORT=8000

class GDCTData:
    def __init__(self):
        self.datalen=0
        self.reqno=''
        self.msgtype=''
        self.msgcode=''
        self.bodylen=0
        self.body=''
        self.respcode=''
        
class GDCTTransfer:
    def __init__(self):
        self.req_data=GDCTData()
        self.resp_data=GDCTData()
    
    def parse_data(self,data):
        print "recv[%s]" % data
        self.req_data.datalen = int(data[0:4],10)
        self.req_data.reqno = data[4:14]
        self.req_data.msgtype = data[14:18]
        self.req_data.msgcode = data[18:24]
        self.req_data.bodylen = len(data)-24
        self.req_data.body = data[24:]
        
    def get_response(self):
        self.resp_data.reqno=self.req_data.reqno
        self.resp_data.msgtype=self.req_data.msgtype
        self.resp_data.bodylen = 0
        self.resp_data.body=''
        if self.req_data.msgcode == '000001':
            self.resp_data.msgcode='800001'
            self.resp_data.bodylen = 0
            self.resp_data.respcode='0000'
        elif self.req_data.msgcode == '000002':
            self.resp_data.msgcode='800001'
            self.resp_data.bodylen = 0
            self.resp_data.respcode='0000'
        elif self.req_data.msgcode == '000006':
            self.resp_data.msgcode='800006'
            self.resp_data.respcode='0000'
            self.resp_data.body=self.req_data.body[38:71]
            self.resp_data.bodylen = 33
        elif self.req_data.msgcode == '000005':
            self.resp_data.msgcode='800005'
            self.resp_data.respcode='0000'
            self.resp_data.body='00000000000000000000000000000000'
            dt = datetime.now()
            curr_time = dt.strftime("%Y%m%d%H%M%S")
            self.resp_data.body = self.resp_data.body + curr_time
            self.resp_data.body = self.resp_data.body + '0012000000000000'
            self.resp_data.body = self.resp_data.body + '0000000000001000'
            self.resp_data.body = self.resp_data.body + self.req_data.body[61:81]
            self.resp_data.bodylen = len(self.resp_data.body)
        elif self.req_data.msgcode=='000119':
            self.resp_data.msgcode='800119'
            self.resp_data.bodylen = 0
            self.resp_data.respcode='0000'
        else:
            return ""
        
        
        resp = "%s%s%s%s" % (self.resp_data.reqno,self.resp_data.msgtype,self.resp_data.msgcode,self.resp_data.respcode)
        self.resp_data.datalen = len(resp) + self.resp_data.bodylen + 4
        
        resp = resp + self.resp_data.body
        #print "body[%s]" % self.resp_data.body
        resp = "%04d%s" % (self.resp_data.datalen,resp)
        print "send[%s]bodylen[%d]" % (resp,self.resp_data.bodylen)
        return resp
            
def do_payment(conn):
    conn.settimeout(3)
    head = ''
    try:
        head = conn.recv(4)
    except:
        print "recv timeout"
        return True
        
    if len(head) == 0:
        print "recv head error"
        return False
    print "recv head[%s]" % head
    datalen = int(head,10)
    if datalen < 512:
        body = conn.recv(datalen-4)
        if body is None:
            return
            
        transfer = GDCTTransfer()
        transfer.parse_data(head+body)
        resp = transfer.get_response()
        conn.send(resp)
        
    return True
    
def do_server():
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind((HOST,PORT))
    s.listen(1)
    s.settimeout(5)
    print "start listen...port(%d) " % PORT
    while True:
        conn = None
        addr = None
        try:
            conn,addr = s.accept()
        except:
            continue
        if conn is None:
            continue
        while True:
            if not do_payment(conn):
                conn.close()
                break
        


if __name__ == "__main__":
    do_server()