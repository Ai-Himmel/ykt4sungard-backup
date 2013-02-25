#! /usr/bin/env python

""" This tools can change the CVS/Root with specified value
such like :pserver:cash@cvs.yrtech.com:/home/cvspub
Usage : chcvsroot.py options [directory] ...
Options :
-r [cvsroot] : specify the new CVSROOT
-R : process non-recursivly on the specified dirs.Default is true
-v : Process verbosly.
"""
# Author: cash <cash@km666.net>
# $Id: chcvsroot.py 2 2003-11-12 06:06:13Z cash $

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
                    cvsdir = os.path.join(fullname,'Root')
                else:
                    subdirs.append(fullname) # save all sub dir

    if cvsdir:
        changeroot(cvsdir)              # change the CVS/Root
        
    global recursive
    if recursive == 1:                  # do it recursivly
        for sub in subdirs:
            process(sub)


def changeroot(cvsroot):
    try:
        rootfile = open(cvsroot , "w")
    except getopt.error:
        print "Error: can't open file : %s" % cvsroot
        return 1

    rootfile.truncate(0)
    global newroot , verbose
    rootfile.write(newroot)
    rootfile.write('\n')
    if verbose == 1:
        print "Change the CVS/Root : %s" % cvsroot

    rootfile.close()

sys.exit(main())
