#!/usr/bin/python
# coding: gbk
# vim: et:ts=4:ff=unix
"""
Ks Cardlib dist utils , make zip file from license config
"""
import sys,os,getopt
import subprocess
import re,ConfigParser
import zipfile,shutil,datetime

class DllCfg:
    def __init__(self):
        self.name=''
        self.dependence=[]
        self.rename=''

class ZipFileReader:
    def __init__(self,zipname):
        self.zipName = zipname
        self.reader = zipfile.ZipFile(self.zipName,'r',zipfile.ZIP_STORED)

    def copyfile(self,fname,writer,toname=''):
        srcname = 'release/'+fname
        if len(toname) == 0:
            toname = fname
        try:
            writer.writestr(toname,self.reader.read(srcname))
        except Exception,e:
            print "copy file <%s> error %s " % (fname,e)
            return False
        return True

        return True

class DirFileReader:
    def __init__(self,distdir):
        self.distDir = distdir

    def copyfile(self,fname,writer,toname=''):
        fullpath = os.path.join(self.distDir,fname)
        if len(toname) == 0:
            toname = fname
        try:
            writer.write(fullpath,toname)
        except Exception,e:
            print "copy file <%s> error %s " % (fname,e)
            return False
        return True

class CardlibDistUtil:
    def __init__(self,execName):
        self.getRunEnv(execName)
        # license file
        self.lcsFile=''
        # config file
        self.cfgFile=os.path.join(self.execPath,'mkdistcfg.ini')
        # source file ,zip file
        self.zipDistFile=''
        # source directory 
        self.distDir=os.path.join(self.execPath,'release')
        # parameters
        self.lcsParams={}
        self.mustFiles=[]
        self.dllCfgs={}
        self.tempDir=os.path.join(self.execPath,'temp')

    def getRunEnv(self,execName):
        ''' get system environment '''
        # execute name
        self.execName = os.path.basename(execName)
        # execute path
        self.execPath = os.path.realpath(os.path.dirname(execName))


    def loadLcsFile(self):
        if not os.path.exists(self.lcsFile):
            return False
        keyFile = os.path.join(self.execPath,'bin')
        keyFile = os.path.join(keyFile,'pub.key')
        cmdline = os.path.join(self.execPath,'readlcs.exe')
        cmdline += ' -k %s -l %s' % (keyFile,self.lcsFile)
        pipe = subprocess.Popen(cmdline, shell=False, bufsize=4096, stdout=subprocess.PIPE).stdout
        output = pipe.read()
        return self.parseLcsOutput(output)

    def parseLcsOutput(self,output):
        lines = output.split('\r\n')
        m = re.match('KS License Version: ([0-9]*) Expired: ([0-9]*) Cust: ([a-zA-Z0-9]*)',lines[0])
        if not m:
            print "read lcs : %s" % lines[0]
            return False
        self.lcsCustId=m.group(3)
        for l in lines[1:]:
            fld = l.split(',')
            if len(fld) >= 4:
                n = fld[1]
                v = fld[3]
                self.lcsParams[n] = v

        return True


    def error(self,msg):
        print msg
        sys.exit(1)

    def run(self,argv):
        args,optlist = getopt.getopt(argv,'hl:c:z:s:')
        for n,v in args:
            if n == '-h':
                pass
            elif n == '-l':
                self.lcsFile=v
            elif n == '-c':
                self.cfgFile=v
            elif n == '-z':
                self.zipDistFile=v
            elif n == '-s':
                self.distDir = v
            else:
                sys.exit(1)

        if not self.loadLcsFile():
            self.error('Cannot load license file <%s>' % self.lcsFile)

        if not self.loadCfgFile():
            self.error('Cannot load cfg file <%s>' % self.cfgFile)

        return self.mkdist()

    def loadCfgFile(self):
        if not os.path.exists(self.cfgFile):
            return False

        # load config
        parser = ConfigParser.RawConfigParser()
        l = parser.read(self.cfgFile)
        if len(l) == 0:
            return False

        value = parser.get('BASE','MUSTFILES')
        self.mustFiles = value.split(',')

        sections = parser.sections()
        for sec in sections:
            if 'BASE' == sec:
                continue
            cfg = DllCfg()
            cfg.name=sec
            if parser.has_option(sec,'dependence'):
                v = parser.get(sec,'dependence')
                cfg.dependence = v.split(',')
            if parser.has_option(sec,'rename'):
                cfg.rename= parser.get(sec,'rename')

            self.dllCfgs[cfg.name]=cfg

        return True

    def copyOneFile(self,reader,writer,fname):
        if len(fname)==0:
            return True
        if not self.dllCfgs.has_key(fname):
            print "copy file <%s> ..." % fname
            if not reader.copyfile(fname,writer):
                return False
            else:
                return True

        print "copy file <%s> ..." % fname
        cfg = self.dllCfgs[fname]
        ret = False
        if len(cfg.rename) > 0:
            print "rename file <%s> to <%s> ..." % (fname,cfg.rename)
            ret = reader.copyfile(fname,writer,cfg.rename)
        else:
            ret = reader.copyfile(fname,writer)

        if not ret:
            print "copy file <%s> error" % fname
            return False

        for dep in cfg.dependence:
            print "copy <%s> dependence <%s>" % (fname,dep)
            if not reader.copyfile(dep,writer):
                print "copy file <%s> error" % dep
                return False

        return True

    def copyLcsFiles(self,reader,writer):
        ''' copy files '''
        for m in self.mustFiles:
            if not self.copyOneFile(reader,writer,m):
                return False

        cardtypeDllCnt = int(self.lcsParams['kscardlib.cardtypecnt'])
        for i in range(cardtypeDllCnt):
            param = 'kscardlib.cardtype%d' % (i+1)
            fname = self.lcsParams[param]
            if not self.copyOneFile(reader,writer,fname):
                return False

        psamCardtype = self.lcsParams['kscardlib.psamcardtype']
        if 'None' != psamCardtype:
            if not self.copyOneFile(reader,writer,psamCardtype):
                return False

        readerCnt = int(self.lcsParams['kscardlib.dllcount'])
        for i in range(readerCnt):
            param = 'kscardlib.dll%d' % (i+1)
            fname = self.lcsParams[param]
            if not self.copyOneFile(reader,writer,fname):
                return False


        if not self.lcsParams.has_key('kscardlib.dependence'):
            return True

        deps = self.lcsParams['kscardlib.dependence'].split(';')
        for fname in deps:
            if not self.copyOneFile(reader,writer,fname):
                return False

        return True

    def mkdist(self):
        reader=None
        # dt = datetime.datetime.now().strftime('%Y%m%d%H%M%S')
        dt = datetime.datetime.now().strftime('%Y%m%d')
        publishFile = os.path.join(self.execPath,'kscardlib-%s-%s.zip' % (self.lcsCustId,dt))
        print "publish file <%s> !" % os.path.basename(publishFile)
        if os.path.exists(self.zipDistFile):
            reader = ZipFileReader(self.zipDistFile)
        elif os.path.exists(self.distDir) and os.path.isdir(self.distDir):
            reader = DirFileReader(self.distDir)
        else:
            self.error("Please specify dist file or dir")

        writer = zipfile.ZipFile(publishFile,'w',zipfile.ZIP_DEFLATED)
        ret = self.copyLcsFiles(reader,writer)
        if not ret:
            os.unlink(publishFile)
            return -1

        toname=os.path.basename(self.lcsFile)
        print "copy file <%s> ..." % toname
        writer.write(self.lcsFile,'license.lcs')
        writer.close()
        return 0

if __name__ == "__main__":
    dist = CardlibDistUtil(sys.argv[0])
    dist.run(sys.argv[1:])

