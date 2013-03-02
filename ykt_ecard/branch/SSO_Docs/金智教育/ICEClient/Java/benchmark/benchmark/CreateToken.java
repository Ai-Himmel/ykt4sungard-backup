// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CreateToken.java

package benchmark;

import com.wiscom.is.*;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Date;

public class CreateToken
{

    public CreateToken()
    {
    }

    public static void usage()
    {
        System.out.println("CreateToken configfile user pass count");
    }

    public static void main(String args[])
        throws Exception
    {
        if(args.length != 4)
        {
            usage();
            return;
        }
        String configFile = args[0];
        IdentityManager im = IdentityFactory.createFactory(configFile).getIdentityManager();
        String user = args[1];
        String pass = args[2];
        System.out.println("CreateToken userid=" + im.createStoken(user, pass).getTokenValue());
        System.out.println("press any key to continue");
        System.in.read();
        int count = Integer.parseInt(args[3]);
        System.out.println(new Date());
        for(int i = 0; i < count; i++)
            im.createStoken(user, pass).getTokenValue();

        System.out.println(new Date());
        System.out.println("End");
    }
}
