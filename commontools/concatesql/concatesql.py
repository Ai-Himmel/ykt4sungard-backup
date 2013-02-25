#! /usr/bin/env python
"""This is a tools that can concatenate some SQL Script
Usage :
   concatesql [options] -i [inputfile] -o [outputfile]
   options:
      -s Search : search path.
      -r Recursive : Search Recursively. !!! Not implemented !!!
      -h help : print this screen.
"""
#$Id: concatesql.py 11 2004-01-01 11:10:05Z cash $	

import getopt,string,sys,os
import re

re_include_file = re.compile(r'--[ \t]*@[ \t]*include[ \t]*file[ \t]*=',re.I)

def parseOutput(file):
	if os.path.exists(file):
		yesanswer = ('y','yes','Y','YES')
		noanswer = ('n','no','N','NO')
		answer = 'o'
		retries = 3
		while (not answer in yesanswer) and (not answer in noanswer) and (retries>0):
			answer = raw_input('This file [%s] is already exists,are you sure overwrite it!(y/n):' % file)
			if answer in noanswer:
				print 'No file has been generated!!'
				sys.exit(0)
			elif answer in yesanswer:
				return
			retries = retries - 1
			
		print 'Abort after 3 tries!!'
		sys.exit(0)
		
def parseInput(file):
	if not os.path.exists(file):
		print 'Input file is not exists!!'
		sys.exit(1)
			
	if os.path.isdir(file):
		print 'Input file is directory !!'
		sys.exit(1)
	
	return
	
def parseSearchPath(spath):
	paths = string.split(spath,';')
	return paths
	
class ParseSQL:
	GEN_HEADER = [ '----    Create By concatesql Tools    ----\n',
				'---- Copyright Cash 2003 all right reserved ---\n',
				'-----------------------------------------------\n']
	def __init__(self):
		self.ifile = ''
		self.ofile = ''
		self.recursive = False
		self.searchpath = ['.']
		self.ohandle = None
		self.ParsedFile = {}
		
	def __init__(self,ifile,ofile,recursive,searchpath):
		self.ifile = ifile
		self.ofile = ofile
		self.recursive = recursive
		self.searchpath = ['.'] + searchpath
		self.ParsedFile = {}
		self.ohandle = None
	
	def Parse(self):
		try:
			self.ohandle = open(self.ofile,'w+')
		except:
			print 'Cannot create output file %s !' % self.ofile
			sys.exit(2)
			
		for x in ParseSQL.GEN_HEADER:
			self.ohandle.write(x)
		
		self.ParsedFile = {}
		self.__ParseFile(self.ifile)
		
		self.ohandle.close()
		self.ohandle = None
			
	def __ParseFile(self,file):
		try:
			ihandle = open(file,'r')
		except:
			print 'Cannot open file %s !' % file
			return
		
		line = ihandle.readline()
		while line:
			m = re_include_file.search(line)
			if m:
				includefile = line[m.end():]
				includefile = includefile.strip(' \t\n')
				for x in self.searchpath:
					searchfile = os.path.join(x,includefile)
					if os.path.exists(searchfile) and os.path.isfile(searchfile) \
						and (not os.path.islink(searchfile)):
						if not self.ParsedFile.has_key(searchfile):
							self.ParsedFile[searchfile] = searchfile
							self.__writeBegin(includefile)
							self.__ParseFile(searchfile)
							self.__writeEnd(includefile)
			else:
				self.ohandle.write(line)
					
			line = ihandle.readline()
		self.ohandle.write('\n')
		
		ihandle.close()	
	
	def __writeBegin(self,filename):
		self.ohandle.write('-- Begin Include : File [%s] **--\n' % filename)
		
	def __writeEnd(self,filename):
		self.ohandle.write('--*** End Include File : [%s] **--\n' % filename)
		
		
def main():
	try:
		optlist , args = getopt.getopt(sys.argv[1:],'i:o:s:r')
	except getopt.GetoptError:
		print __doc__
		sys.exit(1)
	
	# input file name
	inputfile = ''
	# output file name
	outputfile = ''
	# donnot recursively
	recursive = False
	# current path
	searchpath = '.'
	
	#parse arguments	
	for p ,v in optlist:
		if p == '-i':
			inputfile = v
		elif p == '-o':
			outputfile = v
		elif p == '-r':
			recursive = True
		elif p == '-s':
			searchpath = v
		elif p == '-h':
			print __doc__
			sys.exit(0)
	
	parseInput(inputfile)
	parseOutput(outputfile)
	
	spath = parseSearchPath(searchpath)

	parser = ParseSQL(inputfile,outputfile,recursive,spath)
	parser.Parse()
	
if __name__ == "__main__":
	main()