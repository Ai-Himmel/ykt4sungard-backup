// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GetCurrentUser.java

import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;
import java.io.PrintStream;

public class GetCurrentUser
{

    public GetCurrentUser()
    {
    }

    public static void main(String args[])
        throws Exception
    {
        IdentityFactory identityfactory = IdentityFactory.createFactory(args[0]);
        IdentityManager identitymanager = identityfactory.getIdentityManager();
        System.out.println("GetCurrentUser: " + identitymanager.getCurrentUser(args[1]));
    }
}
