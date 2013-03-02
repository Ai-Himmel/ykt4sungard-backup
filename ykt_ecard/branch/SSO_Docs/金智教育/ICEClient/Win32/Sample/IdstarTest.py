#!/usr/bin/env python

import win32com.client
import time
import msvcrt

idstar = win32com.client.Dispatch("Idstar.IdentityManager")

def check_GetLoginURL():
    print "Check GetLoginURL()"
    print idstar.GetLoginURL()
    for i in range(0,200) :
        idstar.GetLoginURL()

def check_GetLogoutURL():
    print "Check GetLogoutURL()"
    print idstar.GetLogoutURL()
    for i in range(0,200) :
        idstar.GetLogoutURL()

def check_GetUserName():
    print "Check GetUserName"
    print idstar.GetUserNameById("amAdmin");
    for i in range(0,200) :
        idstar.GetUserNameById("amAdmin");

def check_GetUserAttribute():
    print "Check GetUserAttribute"
    print idstar.GetUserAttribute("amAdmin","userPassword")
    for i in range(0,200) :
        idstar.GetUserAttribute("amAdmin","userPassword")

    
def check_GetUserGroups():
    print "Check GetUserGroups"
    print idstar.GetUserGroup("amAdmin")
    for i in range(0,200) :
        idstar.GetUserGroup("amAdmin")

def check_CheckPassord():
    print "Check CheckPassword"
    print idstar.CheckPassword("amAdmin", "doremifa")
    print idstar.CheckPassword("amAdmin", "doremifa1")
    for i in range(0,200):
            idstar.CheckPassword("amAdmin", "doremifa")
    
def check_GetRootGroup():
    print "Check GetRootGroup"
    print idstar.GetRootGroup()
    for i in range(0,200):
        idstar.GetRootGroup()

def check_GetSubGroups():
    print "Check GetSubGroups"
    g = idstar.GetRootGroup();
    id = g[0]
    print idstar.GetSubGroups( id )
    for i in range(0,200):
        idstar.GetSubGroups( id )

def check_GetUserNameByGroup():
    print "Check GetUserNameByGroup"
    g = idstar.GetRootGroup();
    id = g[0]
    print idstar.GetUserNameByGroup(id)
    for i in range(0,200):
        idstar.GetUserNameByGroup(id)

def check_GetUserByGroup():
    print "Check GetUserByGroup"
    g = idstar.GetRootGroup();
    id = g[0]
    print idstar.GetUseByGroup(id)
    for i in range(0,200):
        idstar.GetUserByGroup(id)
        
def check_GetAllGroups():
    print "Check GetAllGroups"
    g = idstar.GetAllGroups()
    print "return ", len(g)," g[0]=", g[0]
    for i in range(0,200):
        idstar.GetAllGroups()

def check_IsUserExist():
    print "Check IsUserExist"
    print "1==", idstar.IsUserExist("amAdmin"),"   0==",idstar.IsUserExist("1q1q")
    for i in range(0,200):
        idstar.IsUserExist("amAdmin")


def check_GetEntryAttribute():
    print "check GetEntryAttribute"
    dn = "o=fudan.edu.cn"
    print dn," objectClass=" , idstar.GetEntryAttribute(dn,"objectClass")
    for i in range(0,200):
        idstar.GetEntryAttribute(dn,"objectClass")
    
if __name__=="__main__":
    raw_input("begin, press any key ")
    check_IsUserExist()
    raw_input("next...")
    check_GetLogoutURL()
    raw_input("next...")
    check_GetLoginURL()
    raw_input("next...")
    check_GetUserName()
    raw_input("next...")
    check_GetUserAttribute()
    raw_input("next...")
    check_GetUserGroups()
    raw_input("next...")
    check_CheckPassord()
    raw_input("next...")
    check_GetRootGroup()
    raw_input("next...")
    #check_GetSubGroups()
    raw_input("next...")
    check_GetUserNameByGroup()
    raw_input("next...")
    check_GetUserByGroup()
    raw_input("next...")
    check_GetAllGroups()
    raw_input("next...")
    check_GetEntryAttribute()
    raw_input("finished.")



