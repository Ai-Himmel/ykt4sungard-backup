#!/usr/bin/env python
# -*- coding: GB2312 -*-
from bccclt import bccclt
import common
import unittest,sys,os,re
from distutils.util import get_platform

RE_REQUESTFIELD=re.compile('[0-9][0-9]:[0-9][0-9]:[0-9][0-9] TKCDataset\.([0-9a-zA-Z_]*)=(.*)')
RE_REQUESTNO=re.compile('[0-9][0-9]:[0-9][0-9]:[0-9][0-9] FuncNo=[0-9]*,RequestType=([0-9]*)')

class RequestData:
    def __init__(self):
        self.req = {}
        self.reqno = 0
        
def parseline(req,line):
    g = RE_REQUESTFIELD.match(line)
    if g <> None:
        x = g.groups()
        fld = x[0].lower()
        if fld[0] == 'l':
            req.req[fld] = int(x[1])
        elif fld[0] == 'd':
            req.req[fld] = float(x[1])
        elif fld[0] == 's':
            req.req[fld] = x[1]
        elif fld[:2] == 'vs':
            req.req[fld] = x[1]
       
    g = RE_REQUESTNO.match(line)
    if g <> None:
        x = g.groups()
        req.reqno = int(x[0])
        
    return True
        

def parseonefile(f):
    handle = None
    try:
        handle = open(f,'r')
    except ex as Exception:
        print "open file [%s] error [%s]" % (f,ex)
        return False
        
    req = RequestData()
    
    while True:
        line = handle.readline()
        if line == "":
            break
        parseline(req,line)
        
    handle.close()
    if req.reqno == 0:
        print "parse file [%s] error, no RequestNo" % f
        return False
    # print data
    codetxt = "v = %s" % req.req
    print codetxt
    print "ret = obj.callsvr(%d,v,5000)" % req.reqno
    return True
            
    
def gendata(filelist):
    cnt = 0;
    for f in filelist:
        if not parseonefile(f):
            print "parse data file [%s] error" % f 
        else:
            cnt = cnt + 1
    
    print "process success! total [%d]" % cnt

if __name__=="__main__":
    gendata(sys.argv[1:])
