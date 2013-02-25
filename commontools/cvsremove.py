#! /usr/bin/env python

""" This tools can remove the CVS/Root with specified value
Usage : cvsremove.py options [directory] ...
Options :
-r [cvsroot] : specify the new CVSROOT
-R : process non-recursivly on the specified dirs.Default is true
-v : Process verbosly.
"""
# Author: cash <cash@km666.net>
# $Id: cvsremove.py 23 2005-06-17 07:41:01Z cash $

import os , sys , getopt

newroot = ''
verbose = 0
recursive = 1

def main():
    try:
        opt , args = getopt.getopt(sys.argv[1:] , 'Rvr:')
    except getopt.error , msg:
        print __doc__
        return 1

    global newroot , verbose , recursive
    for o , v in opt:
        if o == '-r':
            newroot = v
        elif o == '-v':
            verbose = 1
        elif o == '-R':
            recursive = 0

    if args :
        for arg in args :
            process(arg)
    else:
        process(".")

    return 0


def process(dir):
    subdirs = []
    cvsdir = ''
    names = os.listdir(dir)
    for name in names:
        fullname = os.path.join(dir,name)
        if os.path.isdir(fullname):     # test if it is a dir
            if not os.path.islink(fullname): # test if it is not a link
                if name == 'CVS':       # test if is a CVS dir then change it
                    cvsdir = fullname
                else:
                    subdirs.append(fullname) # save all sub dir

    if cvsdir:
        removecvsdir(cvsdir)              # change the CVS/Root
        
    global recursive
    if recursive == 1:                  # do it recursivly
        for sub in subdirs:
            process(sub)


def removecvsdir(cvsroot):
    subdirs = []
    names = os.listdir(cvsroot)
    for name in names:
    	fullname = os.path.join(cvsroot,name)
    	if os.path.isdir(fullname):
    		subdirs.append(fullname)
    	else:
    		os.remove(fullname)
    
    for sub in subdirs:
    	removecvsdir(sub)
    os.removedirs(cvsroot)

sys.exit(main())
