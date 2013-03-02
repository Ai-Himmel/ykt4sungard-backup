// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GetCurrentUser.java

package benchmark;

import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Date;

public class GetCurrentUser
{

    public GetCurrentUser()
    {
    }

    public static void usage()
    {
        System.out.println("ValidateToken configfile token times");
    }

    public static void main(String args[])
        throws Exception
    {
        if(args.length != 3)
        {
            usage();
            return;
        }
        String configFile = args[0];
        String tokenValue = args[1];
        System.out.println(tokenValue);
        IdentityManager im = IdentityFactory.createFactory(configFile).getIdentityManager();
        System.out.println("GetCurrentUser userid=" + im.getCurrentUser(tokenValue));
        System.out.println("press any key to continue");
        System.in.read();
        int count = Integer.parseInt(args[2]);
        System.out.println(new Date());
        for(int i = 0; i < count; i++)
        {
            if(i % 1000 == 0)
                System.out.println("" + i + " " + System.currentTimeMillis() / 1000L + " " + im.getCurrentUser(tokenValue));
            im.getCurrentUser(tokenValue);
        }

        System.out.println(new Date());
        System.out.println("End");
    }
}
