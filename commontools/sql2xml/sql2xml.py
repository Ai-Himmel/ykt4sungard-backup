#! /usr/bin/env python
"""This is a tools that can parse SQL scripts to
XML document.
Usage :
   sql2xml.py [options] -f [inputfile] -o [outputfile]
   options:
      -e encoding : Use the <encoding> to generate XML.
      -h help : print this screen.
"""
#$Id: sql2xml.py 8 2004-01-01 06:06:53Z cash $	

import getopt,string,sys,os

from sqlparse import SQLParse,Table2Xml

inputfile = ''
outputfile = ''

def getOutputPath(outputPath,inputFile):
	result = '';
	if inputFile.rfind('.') > -1:
		result = inputFile[:inputFile.rfind('.')] + '.xml'
	else:
		result = inputFile + '.xml'
	return os.path.join(outputPath,result)
	
def isCanParse(filePath):
	if os.path.isdir(filePath) or os.path.islink(filePath):
		return False
	ext = ''
	if filePath.rfind('.') > -1:
		ext = filePath[filePath.rfind('.'):]
		return (string.lower(ext) == '.sql')
	else:
		return False
	
def main():
    try:
        optlist ,args = getopt.getopt(sys.argv[1:],'f:o:e:')
    except getopt.GetoptError:
        print __doc__
        sys.exit(1)

    global inputfile, outputfile
    encoding = 'GB2312'
    for p,v in optlist:
        if p == '-f':
            inputfile = v
        elif p == '-o':
            outputfile = v
        elif p == '-e':
            encoding = v
        elif p == '-h':
            print __doc__
            return
            
    #convert windows path separator to unix style.
    inputfile = inputfile.replace('\\','/')
    if inputfile == '':
        print __doc__
        return
    
    
    if outputfile == '':
    		
		if os.path.isfile(inputfile):
			if inputfile.rfind('.') > -1:
			    outputfile = inputfile[:inputfile.rfind('.')] + '.xml'
			else:
			    outputfile = inputfile + '.xml'
		else:
			outputfile = inputfile
	
    try:  	
    	if os.path.isdir(inputfile):
    		files = os.listdir(inputfile)
    		if os.path.isdir(outputfile):
	    		for subfile in files:
	    			if not isCanParse(os.path.join(inputfile,subfile)):
	    				continue
	    			outpath = getOutputPath(outputfile,subfile)
	    			print outpath
    				t2x = Table2Xml(outpath,encoding)
	    			parse = SQLParse(os.path.join(inputfile,subfile))
	    			parse.parse()
	    			t2x.writeHeader()
	    			t2x.write(parse)
    				t2x.writeTail()
    		else:
    			t2x = Table2Xml(outputfile,encoding)
    			t2x.writeHeader()
    			for subfile in files:
    				if not isCanParse(os.path.join(inputfile,subfile)):
	    				continue 
	    			parse = SQLParse(os.path.join(inputfile,subfile))
	    			parse.parse()
	    			t2x.write(parse)
    			t2x.writeTail()    		
    	else:
    		t2x = Table2Xml(outputfile,encoding)
        	parse = SQLParse(inputfile)
        	parse.parse()
	        t2x.writeHeader()
	        t2x.write(parse)
	        t2x.writeTail()	        
    except Exception ,ex:
        print __doc__
        print "Error: %s" % ex
        sys.exit(1)

def test():
    try:
        parse = SQLParse('test/testscript.sql')
        parse.parse()
        for v in parse.tables:
            print "name %s , comment[%s]:" % (v.name,v.comment)
            i = 0
            for t , f in v.getFields().items():
                print "Field %d: name[%s], type [%s],length[%s],default[%s], comment[%s],pri [%s]" \
                      %(i , f.name,f.type, f.length,f.default, f.comment, f.primarykey)
                i = i + 1
            print '\n'
    except:
        print __doc__
        exit(1)

    
if __name__ == "__main__":
    main()
