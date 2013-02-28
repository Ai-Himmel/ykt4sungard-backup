#!/usr/bin/env

import datetime

class CheckPerf:
    def __init__(self):
        self.begintime = datetime.datetime.now()
        self.endtime = None
        self.mintime = 0.0
        self.maxtime = 0.0
        self.checkcount = 0
        self.totaltime = 0.0
        self.reportmsg = ''
        self.prechktime = None
        
    def startchk(self):
        self.begintime = datetime.datetime.now()
        self.endtime = None
        self.mintime = 99999999.0
        self.maxtime = 0.0
        self.checkcount = 0
        self.totaltime = 0.0
        self.reportmsg = ''
        self.prechktime = self.begintime
    
    def setchkpoint(self):
        self.endtime = datetime.datetime.now()
        delta = self.endtime - self.prechktime
        t = delta.seconds + delta.microseconds / 1000000.0
        if t < self.mintime: self.mintime = t
        if t > self.maxtime: self.maxtime = t
        self.checkcount += 1
        self.totaltime += t
        self.prechktime = self.endtime
        
    def report(self):
        rpt = 'execute[%d]count cost(s) [%.4f]max[%.4f]min[%.4f]avg[%.4f]' \
            % (self.checkcount,self.totaltime,self.maxtime,self.mintime,self.totaltime/self.checkcount)
        self.reportmsg = rpt
        return rpt
        