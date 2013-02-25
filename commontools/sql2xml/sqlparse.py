#! /usr/bin/env python
# -*- coding: utf-8 -*-
#$Id: sqlparse.py 24 2006-11-30 05:41:27Z cheng.tang $	

# import section
import re, sys, string

from elements import Table , Field

# global section
# there are some regular express

re_table = re.compile(r'create[ \t]+(or|replace| |\t)*table[^(]*',re.I)
re_table_start = re.compile(r'create[ \t]+(or|replace| |\t)*table',re.I);

re_field = re.compile('[\w \t]*(\)|,|\n)?',re.I)

re_table_comment_start = re.compile(r'[\t ]*/\*\*[\t ]*',re.I)
re_table_comment_content = re.compile(r'[\t ]*\*',re.I)
re_table_comment_end = re.compile(r'[\t ]*\*/',re.I)

re_field_comment = re.compile(r'\-\-@\W*',re.I)
re_field_not_null = re.compile(r'not[ \t]+null',re.I)
re_field_primary_key = re.compile(r'primary[ \t]+key',re.I)
re_field_default = re.compile(r'default[.]*',re.I)
re_field_length_str = re.compile(r'[^,0-9]')

#re_c_like_comment = re.compile(r'/\*([^*]+|\*+[^/]\n)*(\*+/)?',re.I)
re_c_like_comment = re.compile(r'/\*([^\*]|\*+/)',re.I)
re_ansi_comment = re.compile(r'\-\-[^@]*',re.I)

p_prog = [re_table , re_field]
p_ignores = [re_c_like_comment,re_ansi_comment]


# code section
class SQLParse:
    
    def __init__(self,fileName):
        """ constructor """
        self.fileName = fileName
        self.handle = None
        self.tables = []
        self.tblcomments = []
        self.currPrimaryKeys = []

    def parse(self):
        """use this method to parse a file."""
        try:
            self.handle = open(self.fileName,'r')
        except:
            print 'Open file error : %s.' % self.fileName
            return

        line = self.handle.readline()
        lineno = 1
        while line :
            self.parseLine(line,lineno)
            line = self.handle.readline()
            lineno = lineno + 1

        self.handle.close()

    def parseLine(self , line , lineno):
        """Parse each line."""
        # ignore empty line
        if line.strip(' ') == '': return
        # ignore common comment line
        for ignore in p_ignores:
            m = ignore.match(line)
            if m:
                # ignore it
                return
        # if it is table start
        m = re_table_comment_start.match(line)
        if m:
            self.parseTableComment(line)
            return
        # if it is table
        m = re_table.match(line)
        if m:
            self.parseTable(m.group())

    def parseTableComment(self ,line):
        """parse table comment line"""
        comm = ''
        # if it's not '*/' the return
        line = self.handle.readline()
        line = line.strip(' \t\n')
        while line and (line<>'*/'):
            comm = comm + '\n' +line.strip('*')
            line = self.handle.readline()
            line = line.strip(' \t\n')
        # if we parse to the end of table comment ,we push it to a stack.
        self.tblcomments.append(comm.strip('\n'))
        
    def parseTable(self ,line):
        """parse table definition."""
        # get table name
        m = re_table_start.search(line)
        if m :
        	tblname = line[m.end():]
        	tblname = tblname.strip(' (\t')
        tbl = Table()
        tbl.name = tblname
        if len(self.tblcomments) > 0:
            tbl.comment = self.tblcomments.pop()
        # parse each field step by step.
        li = self.handle.readline()
        while li:
            # if it's the end of create table
            if li.strip(' \t\n') == ');': break
            if not self.parseField(tbl,li): return
            li = self.handle.readline()
        # save table
        for p in self.currPrimaryKeys:
            if tbl.getFields()[p]:
                tbl.getFields()[p].setPrimaryKey(True)

        self.currPrimaryKeys = []
        self.tables.append(tbl)

    def parseField(self ,tbl,line):
        """ field"""
        line = line.strip(' \t')
        # if it's the primary key
        m = re_field_primary_key.match(line)
        
        if m:
            defines = line[line.find('(')+1:line.find(')')]
            self.currPrimaryKeys = self.splitString(defines,' ','\t',',')
            return True
        
        m = re_field_comment.search(line)
        fld = Field('','',-1)
        try:
            if m:
                fieldDefine = line[:m.start()]
            else:
                fieldDefine = line
                
            lwords = self.splitString(fieldDefine,' ','\t',')','(',',')
            if len(lwords) >= 2:
                fld.name = lwords[0]
                fld.type = lwords[1]
               
                m = re_field_not_null.search(line)
                if m:
                    fld.notnull = True

                m = re_field_primary_key.search(line)
                if m:
                    fld.setPrimaryKey(True)

                # find the field length
                pos = fieldDefine.rfind(fld.type)
                if pos > -1:
                    pos = pos + len(fld.type)
                    for i in range(pos,len(fieldDefine)):
                        if fieldDefine[i] == ' ' or fieldDefine[i] == '\t':
                            continue
                        elif fieldDefine[i] == '(':
                            break
                        else:
                            pos = -1
                            break
                if pos > -1 and pos < len(fieldDefine):
                    fld.length = fieldDefine[pos+1:fieldDefine.find(')',pos+1)]

                # get default value
                m = re_field_default.search(fieldDefine)
                if m:
                    fld.default = fieldDefine[m.start() + 7:].strip(' \t,')
                        
                # find the comment of this field
                m = re_field_comment.search(line)
                if m:
                    c = m.group()
                    fld.comment = line[m.start()+3:].strip(' \t\n')

                tbl.addField(fld)
            # if not found just return true
            return True
        except Exception,ex:
            print ex
            return False

        

    def splitString(self ,str,*sep):
        """ splite a str to a list which contains each words."""
        words = []
        word = ''
        foundSep = False
        # strip the heading and trailing spaces and tabs
        str = str.strip(' \t\n')
        for i in range(len(str)):
            if str[i] == ' ' or str[i] == '\t':
                if word <> '' : words.append(word)
                word = ''
                continue
            for s in sep:
                if str[i] == s:
                    if word <> '': words.append(word)
                    word = ''
                    foundSep = True
                    break
            if foundSep:
                foundSep = False
                continue
            word = word + str[i]

        if word <> '': words.append(word)
        return words

class Table2Xml:
    GENERATE_VERSION = ['<!-- Generate by sql2xml tools V 0.1 -->\n',
                        '<!-- Author : Cash  Copyright 2000-2003 -->\n',
                        '<!-- $' + 'Id$ -->\n']
    XML_VERSION = '<?xml version="1.0" encoding="%s"?>\n'
    
    def __init__(self,output,encoding='GB2312'):
        self.parse = None
        self.encoding = encoding
        self.output = output
        self.fp = None
        try:
            self.fp = open(output,'w+')
        except:
            print "Error on create output file : %s" % output
        
    def writeHeader(self):
    	self.fp.truncate();
    	self.fp.write(Table2Xml.XML_VERSION % self.encoding)
        for v in Table2Xml.GENERATE_VERSION:
            self.fp.write(v)
        self.fp.write('<tables>\n')
        
    def writeTail(self):
    	self.fp.write('</tables>')
        self.fp.close()

    def write(self,parse):    
    	self.parse = parse
        self._writeNode(self.fp)       

    def _writeNode(self,fp):
        for x in self.parse.tables:
            fp.write('\t<table>\n')
            fp.write('\t\t<name>')
            fp.write(x.name)
            fp.write('</name>\n')
            fp.write('\t\t<comment>')
            fp.write(x.comment)
            fp.write('</comment>\n')
            for t ,f in x.getFields().items():
                fp.write('\t\t<field>\n')
                # name
                fp.write('\t\t\t<name>%s</name>\n' % f.name)
                # type
                fp.write('\t\t\t<type>%s</type>\n' % f.type)
                # length
                if f.length <> -1:
                    fp.write('\t\t\t<length>%s</length>\n' % f.length)
                #primary key
                if f.primarykey :
                    fp.write('\t\t\t<primarykey>%s</primarykey>\n' % 'True')
                #not null
                if not f.primarykey and f.notnull:
                    fp.write('\t\t\t<notnull>%s</notnull>\n' % 'True')
                # default
                if f.default <> '':
                    fp.write('\t\t\t<default>%s</default>\n' % f.default)
                # comment
                if f.comment <> '':
                    fp.write('\t\t\t<comment>%s</comment>\n' % f.comment)
                    
                fp.write('\t\t</field>\n')
                
            fp.write('\t</table>\n')

    def read(self, input):
        tables = {}
        return tables
    
def test():
    parse = SQLParse('')
    v = parse.splitString('id varchar(3)default getvalue(ffd)',' ' ,'\t' ,')')
    print v
    v = parse.splitString('; fim',' ','\t',';')
    print v

    testFld = 'id integer primary key, --@ ÖÐ¹ú'

    table = Table('table1')
    parse.parseField(table,testFld)
    for n,t in table.getFields().items():
        print t.name
        print t.type
        print t.length
        print t.comment

if __name__ == "__main__":
    test()
    
            
            
