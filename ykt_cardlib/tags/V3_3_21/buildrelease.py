#!/usr/bin/env python
# vim: coding=cp936

import pysvn,fileinput,re,tempfile,os,shutil,subprocess,zipfile,sys,imp,hashlib,traceback
from datetime import datetime
import getopt




class KsCardlibBuildSystem:
    VERSIONFILE=['kscard/version.h']
    VER_MAJOR_RE=re.compile('#define _KSCARD_VER_MAJOR ([0-9]*)')
    VER_MINOR_RE=re.compile('#define _KSCARD_VER_MINOR ([0-9]*)')
    VER_BUILD_RE=re.compile('#define _KSCARD_VER_BUILD ([0-9]*)')

    RELEASEFILES=[
    'cpack.dat',
    'pub.key',
    'ksitfcdaemon.exe']

    BUILDDIR='bin'
    RELEASEDIR='release'

    def __init__(self):
        self.CURRENTRELEASEVER=''
        self.srcPath=''
        self.tagname=''
        
    def doCheckVER(self,line,regobj):
        obj = regobj.match(line)
        if obj:
            vernum = int(obj.group(1))
            return True,vernum
        else:
            return False,0
            
    def doUpdateVersion(self,nogenver):
        find = False
        majorver=0
        minorver=0
        buildver=0
        for x in KsCardlibBuildSystem.VERSIONFILE:
            f = tempfile.NamedTemporaryFile(delete=False)
            print "regenerate build version number"
            for line in fileinput.input(x):
                m,n = self.doCheckVER(line,KsCardlibBuildSystem.VER_MAJOR_RE)
                if m:
                    majorver = n
                    f.write(line)
                    continue
                m,n = self.doCheckVER(line,KsCardlibBuildSystem.VER_MINOR_RE)
                if m:
                    minorver = n
                    f.write(line)
                    continue
                m,n = self.doCheckVER(line,KsCardlibBuildSystem.VER_BUILD_RE)
                if m:
                    buildver = n
                    f.write("#define _KSCARD_VER_BUILD %d\n" % (buildver + 1))
                    find = True
                    continue
                
                # write line 
                f.write(line)
            f.close()
            
            
            if find:
                if not nogenver:
                    shutil.copyfile(f.name,x)
                    buildver = buildver + 1 
                self.CURRENTRELEASEVER = "V%d_%d_%d" % (majorver,minorver,buildver)
                print "build version [%s]" % self.CURRENTRELEASEVER
                return True
            else:
                print "build version number has not been found !"
                return False

    def mktagCBLog(self):
        return True,"make tag %s\nbugid: #9999" % self.tagname
        
    def doCheckTagPath(self,svn,path):
        info=None
        try:
            info = svn.ls(path)
        except pysvn.ClientError, e:
            print "CheckTagPaht :%s" % (e.args[0])
            return False
        return True
    
    def doDelTagPath(self,svn,path):
        try:
            print "waiting delete tag [%s]" % path
            svn.remove(path)
        except pysvn.ClientError, e:
            print "delete tag error[%s]" % e.args[0]
            return False
        return True
        
    def doMakeTag(self):
        if not self.doUpdateVersion(True):
            return False
        client = pysvn.Client()
        tagslist = client.status(self.srcPath)
        totalcnt=0
        updcnt=0
        errcnt=0
        for x in tagslist:
            totalcnt+=1
            if x.entry <> None and x.entry.name == "buildrelease.py":
                continue
            if str(x.text_status) in ('missing','conflicted','obstructed','incomplete'):
                print "File[%s]st[%s]" % (x.path,x.text_status)
                errcnt+=1
                return False
            elif str(x.text_status) in ('added','deleted','replaced','modified','merged'):
                print "File[%s]st[%s]" % (x.path,x.text_status)
                updcnt+=1
        
        if updcnt > 0:
            print "Notice ************************************************"
            print "total[%d] update[%d]" %  (totalcnt,updcnt)
            print "please commit-in first!!!"
            return False
        
        info = client.info(self.srcPath)
        repos = info.repos
        frompath = info.url
        self.tagname = self.CURRENTRELEASEVER
        topath = repos+'/tags/' + self.tagname
        
        client.callback_get_log_message = self.mktagCBLog
        if self.doCheckTagPath(client,topath):
            anw = raw_input("Tag[%s] already exists, delete first!(N/y)" % self.tagname)
            if anw in ('y','Y'):
                if not self.doDelTagPath(client,topath):
                    return False
            else:
                return False
        try:
            client.copy(frompath,topath)
        except pysvn.ClientError ,e:
            print "make tag error [%s]" % e.args[0]
            return False
        
        print "make tag success!"
        print "tag url is :" + topath
        return True

    def _checkFileExt(self,filename,ext):
        f = filename.upper()
        e = ext.upper()
        idx = f.rfind(e)
        if idx == (len(f)-len(ext)):
            return True
        return False
        
    def _load_module(self,code_path):
        try:
            try:
                code_dir = os.path.dirname(code_path)
                code_file = os.path.basename(code_path)
                fin = open(code_path, 'rb')
                mn = hashlib.md5()
                mn.update(code_path)
                return imp.load_source(mn.hexdigest(), code_path, fin)
            finally:
                try: fin.close()
                except: pass
        except ImportError, x:
            traceback.print_exc(file = sys.stderr)
            raise
        except:
            traceback.print_exc(file = sys.stderr)
            raise

    def doCopyReleaseFile(self,makefile):
        ''' 打包生成打包文件 '''
        distfiles = os.listdir(KsCardlibBuildSystem.BUILDDIR)
        for f in distfiles:
            src = os.path.join(KsCardlibBuildSystem.BUILDDIR,f)
            if not os.path.isfile(src):
                continue
            s = os.path.basename(src)
            if not self._checkFileExt(s,'.dll') and not(s in KsCardlibBuildSystem.RELEASEFILES):
                continue
            dst = os.path.join(KsCardlibBuildSystem.RELEASEDIR,f)
            shutil.copyfile(src,dst)
            print "copy file %s ..." % f
        

        m = self._load_module(os.path.join('.',makefile))
        #print m
        #print m.distfiles
        
        todayDay = datetime.today().strftime("%Y%m%d")
        releasename = "kscardlib%s_%s.zip" % (todayDay,self.CURRENTRELEASEVER)
        if m.__dict__.has_key('buildname') and m.buildname != '':
            releasename = "kscardlib%s_%s_%s.zip" % (todayDay,self.CURRENTRELEASEVER,m.buildname)
            
            
        # 发布文件路径
        publish_dir = KsCardlibBuildSystem.RELEASEDIR
        if m.__dict__.has_key("distdir") and m.distdir != '':
            publish_dir = m.distdir
        releasefile = os.path.join(publish_dir,releasename)
        zip = zipfile.ZipFile(releasefile,mode='w',compression=zipfile.ZIP_DEFLATED)
        
        
            
        localfiles = ['changelog.txt','kscard.ini','kscardinterface.ini']
        files = m.distfiles + localfiles + KsCardlibBuildSystem.RELEASEFILES
        for f in files:
            dst = os.path.join(KsCardlibBuildSystem.RELEASEDIR,f.lower())
            print "zip file %s ..." % f
            zip.write(dst)
            
        relfile = open(os.path.join(KsCardlibBuildSystem.RELEASEDIR,("00.publish_%s.txt" % todayDay)),'w')
        relfile.close()
        print "waiting for add release file[%s] to svn..." % releasename
        if self.checkReleaseAddSVN(releasefile):
            print "create relase [%s] success!" % releasename
            
    
    def checkReleaseAddSVN(self,releasefile):
        ''' 将打包文件增加到 svn 中 '''
        reldir = os.path.dirname(releasefile)
        relname = os.path.basename(releasefile)
        client = pysvn.Client()
        info = client.status(releasefile)
        x = info[0]
        ci_msg = ''
        try:
            if str(x.text_status) in ('unversioned'):
                anw = raw_input("release file has not been add to svn , add it?(Y/n)")
                if anw in ('n','N'):
                    return True
                client.add(releasefile)
                ci_msg = 'add new release file\n bugid: #9999'
            elif str(x.text_status) in ('added','deleted','replaced','modified','merged'):
                ci_msg = 'update release file \n bugid: #9999'
            else:
                print "release file unknonw status [%s]" % str(x.text_status)
                return False
            anw = raw_input("check in release file to svn? (Y/n)")
            if anw in ('n','N'):
                return True
            revision = client.checkin(reldir,ci_msg)
            print "add release success, revision number is [%d]" % revision.number
        except pysvn.ClientError ,e:
            print "make tag error [%s]" % e.args[0]
            return False
        
        return False
        
    def checkRebuildResult(self,outfile,rebuild):
        buildRe = None
        if not rebuild:
            # buildRe = re.compile('Build: ([0-9]*) succeeded, ([0-9]*) failed, ([0-9]*) skipped')
            # buildRe = re.compile('Build: ([0-9]*) succeeded, ([0-9]*) failed, ([0-9]*) up-to-date, ([0-9]*) skipped')
            buildRe = re.compile('生成: 成功 ([0-9]*) 个，失败 ([0-9]*) 个，最新 ([0-9]*) 个，跳过 ([0-9]*) 个')
        else:
            buildRe = re.compile('Rebuild All: ([0-9]*) succeeded, ([0-9]*) failed, ([0-9]*) skipped')
            
        for line in fileinput.input(outfile):
            line = line.strip()
            obj = buildRe.search(line)
            #print "[%s]" % line
            if obj:
                buildsucc = int(obj.group(1))
                buildfaild = int(obj.group(2))
                buildskipped = int(obj.group(3))
                print "Result : %s " % line
                if buildfaild > 0:
                    return False
                return True
        return False

    def doRebuildPrj(self,rebuild):
        logfile = 'build.log'
        # cmd = '"c:\\tools\\Microsoft Visual Studio 9.0\\Common7\\IDE\\VCExpress.exe"'
        cmd = '"c:\\Tools\\Microsoft Visual Studio 9.0\\Common7\\IDE\\devenv.exe"'
        # cmd = '"d:\Microsoft Visual Studio .NET 2003\Common7\IDE\devenv.exe"'
        if os.path.exists(logfile):
            os.unlink(logfile)
        if rebuild:
            print "rebuild wait ..."
            p = subprocess.Popen(cmd + ' ykt_cardlib_v3_1_release.sln /rebuild release /out build.log',
                stdout = subprocess.PIPE)
            print p.stdout.read()
            p.wait()
        else:
            print "compling wait ..."
            os.utime("kscard/kscard.cpp",None)
            p = subprocess.Popen(cmd + ' ykt_cardlib_v3_1_release.sln /build release /out build.log',
                stdout = subprocess.PIPE)
            print p.stdout.read()
            p.wait()
            
        if not self.checkRebuildResult(logfile,rebuild):
            return False
        return True
                    
    def printUsage(self):
        print "buildrelease.py [-h] [--nobuild|{--rebuild}[--nogenver]] [--mktag] [-f config]"
        print "\t--nobuild  not build project"
        print "\t--mktag    make SVN tag"
        print "\t--rebuild  force rebuild project"
        print "\t--nogenver force not generate version build number"
        print "\t-h         print this screen"
        print "\t-f config  use configrature file"
        
    def doCheck(self,argc):
        self.srcPath = os.getcwd()
        nobuild = False
        rebuild = False
        nogenver = False
        mktag = False
        makefile = 'Config'
        try:
            optlist, args = getopt.getopt(argc,'hf:',['nobuild','rebuild','nogenver','mktag'])
            for a,v in optlist:
                if a == '--nobuild':
                    nobuild = True
                elif a == '--rebuild':
                    rebuild = True
                elif a == '--nogenver':
                    nogenver = True
                elif a == '-h':
                    self.printUsage()
                    sys.exit(0)
                elif a == '-f':
                    makefile=v
                elif a == '--mktag':
                    mktag = True
                else:
                    self.printUsage()
                    sys.exit(1)
        except:
            self.printUsage()
            sys.exit(1)
             
        # 只做tag基线，不做编译
        if mktag:
            self.doMakeTag()
            return
            
        if nobuild == True and rebuild == True:
            self.printUsage()
            sys.exit(1)
        
        if nobuild:
            nogenver = True
        
        if self.doUpdateVersion(nogenver):
            if not nobuild:
                if not self.doRebuildPrj(rebuild):
                    print "build error! please check log file [build.log]"
                    sys.exit(1)
        else:
            print "build project error!"
            sys.exit(1)
            
        self.doCopyReleaseFile(makefile)
    

if __name__ == "__main__":
    build = KsCardlibBuildSystem()
    build.doCheck(sys.argv[1:])
