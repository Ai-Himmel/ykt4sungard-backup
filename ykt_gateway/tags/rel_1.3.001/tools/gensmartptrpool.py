#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- python -*-

import os
import sys

def _genconstruct(handle,args):
    typedefstr = "<"
    argsstr = "("
    constargstr = "("
    paramstr = ""
    for i in range(args):
        typedefstr += "typename T%d," % i
        argsstr += "T%d& arg%d," % (i,i)
        constargstr += "const T%d& arg%d," % (i,i)
        paramstr += "arg%d," % i
    typedefstr = typedefstr[:-1] + '>'
    argsstr = argsstr[:-1] + ')'
    constargstr = constargstr[:-1] + ')'
    paramstr = paramstr[:-1]

    handle.write("template")
    handle.write(typedefstr + "\n")
    handle.write("SmartPtr Alloc" + argsstr + "\n{\n")
    handle.write("return CreateNewObject(this,_alloc.construct(" + paramstr + "));\n")
    handle.write("\n}\n")

    handle.write("template")
    handle.write(typedefstr + "\n")
    handle.write("SmartPtr Alloc" + constargstr + "\n{\n")
    handle.write("return CreateNewObject(this,_alloc.construct(" + paramstr + "));\n")
    handle.write("\n}\n")

def _outputfile(handle):
    license = "// this file is auto-generated. DO NOT modify this file manually.\n \
            // Copyright Kingstargroup 2006 \n\
            // Author: люЁи \n"
    handle.write(license)
    for i in range(6):
        if i == 0 : continue
        _genconstruct(handle,i)

def genfile(filename):
    basepath = os.path.dirname(os.path.abspath(sys.argv[0]))
    fullpath = os.path.join(basepath,'../include/detail/')
    fullpath = os.path.join(fullpath,filename)
    print "generate file [" + os.path.basename(fullpath) + "]"
    handle = None
    try:
        handle = open(fullpath,"w+")
    except:
        print "create output file error"
        sys.exit(1)
    _outputfile(handle)
    handle.close()
    

if __name__ == "__main__":
    genfile('smart_ptr_pool_construct.inc')
