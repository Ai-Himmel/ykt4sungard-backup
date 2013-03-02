// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ValidateToken.java

package benchmark;

import com.wiscom.is.*;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Date;

public class ValidateToken
{

    public ValidateToken()
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
        IdentityManager im = IdentityFactory.createFactory(configFile).getIdentityManager();
        SSOToken token = im.validateToken(tokenValue);
        System.out.println("validate token userid=" + token.getUserId());
        System.out.println("press any key to continue");
        System.in.read();
        int count = Integer.parseInt(args[2]);
        System.out.println(new Date());
        for(int i = 0; i < count; i++)
        {
            if(i % 1000 == 0)
                System.out.println("" + i + " " + System.currentTimeMillis() + " " + im.validateToken(tokenValue).getUserId());
            token = im.validateToken(tokenValue);
        }

        System.out.println(new Date());
        System.out.println("End");
    }
}
