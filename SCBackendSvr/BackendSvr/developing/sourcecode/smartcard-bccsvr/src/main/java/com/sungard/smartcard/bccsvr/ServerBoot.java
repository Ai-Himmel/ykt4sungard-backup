/*
 * ServerBoot.java  v1.00  2011-12-17
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	ServerBoot.java  v1.00 2011-12-17
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Properties;
import java.util.Scanner;
import java.util.Set;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
//import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.sungard.modules.utils.PropertiesHelper;

/**
 * 服务启动.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-17
 * 
 */
public class ServerBoot {

    private static Logger logger = LoggerFactory.getLogger(ServerBoot.class);

    private final static String CONFIG_FILE = "conf/smartServer.conf";
    private final static String SERVER_PRE = "bcc.drtp.server";
    private static SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss S");

    private static Set<BccServer> bccset = new HashSet<BccServer>();

    // private static ClassPathXmlApplicationContext applicationContext = null;

    private static void startServer(String[] args) {
        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }

        URL url = ServerBoot.class.getClassLoader().getResource(CONFIG_FILE);
        System.out.println("path = " + url.getPath());
        if (null == url) {
            System.out.println("not get resource smartServer.conf");
            System.exit(0);
        }
        Properties properties = new Properties();
        InputStream in = null;
        try {
            in = url.openStream();
        } catch (Exception urlex) {
            urlex.printStackTrace();
        }

        if (null == in) {
            System.exit(0);
        }

        try {
            properties.load(in);
        } catch (IOException ioex) {
            ioex.printStackTrace();
        } finally {
            if (in != null) {
                try {
                    in.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        List<String> svrList = new ArrayList<String>();
        Set<Object> set = properties.keySet();
        for (Object object : set) {
            String valueString = (String) properties.get(object);
            logger.info("{}={}", object, valueString);
            if (((String)object).startsWith(SERVER_PRE)) {
                svrList.add(valueString);
            }
        }

        logger.info("boot svrList {}", svrList.size());
        for (String string : svrList) {
            String[] parms = StringUtils.split(string, ":");
            int threadNum = Integer.parseInt(parms[4]);
            BccServer bccServer = new BccServer();
            bccset.add(bccServer);
            bccServer.setServerInfo(string);
            for (int i = 0; i < threadNum; i++) {
                bccServer.CreateSession(parms[0] + "_" + i);
            }
            bccServer.startService();
        }

        // int threadNum =
        // BccServer.GetInstance().GetConfig("bcc.smartcard.threadNum", 1);
        // for (int i = 0; i < threadNum; i++) {
        // BccServer.GetInstance().CreateSession("thread_" + i);
        // }

        // BccServer.GetInstance().startService();

        Thread shutdownThread = new Thread("genliang") {
            public void run() {
                logger.info("shutdownThread...===========");
                // BccServer.GetInstance().stopService();
                // applicationContext.destroy();
                for (BccServer bccServer : bccset) {
                    bccServer.stopService();
                }

            }
        };
        shutdownThread.setDaemon(true);
        Runtime.getRuntime().addShutdownHook(shutdownThread);

    }

    public static void main(String[] args) {
        logger.info("---->>>--bccsvr starting in... {}", sdf.format(new Date()));
        System.out.println("---->>>--bccsvr starting in... " + sdf.format(new Date()));

        // ApplicationContext applicationContext = new
        // ClassPathXmlApplicationContext("");
        // applicationContext = new
        // ClassPathXmlApplicationContext("/conf/applicationContext.xml");

        startServer(args);

        // Scanner scanner = new Scanner(System.in);
        // String cmdString;
        // while (scanner.hasNextLine()) {
        // cmdString = scanner.next();
        // logger.info("{}", cmdString);
        // if ("quit".equals(cmdString)) {
        // break;
        // // System.exit(0);
        // } else if ("stop".equals(cmdString)) {
        // break;
        // }
        // }
        // BccServer.GetInstance().stopService();

        if (false) {
            String className = System.getProperty("class");
            if (null == className || "".equals(className) || "null".equals(className)) {
                Scanner sc = new Scanner(System.in);
                while (sc.hasNextLine()) {
                    className = sc.next();
                    if ("quit".equals(className)) {
                        System.exit(0);
                    } else {
                        System.out.println("className is:{" + className + "}");
                        break;
                    }
                }
            }
            // String className = "com.sungard.smartcard.bccsvr.FunctionOne";

            try {
                Class<?> clazz = Class.forName(className);
                Method method = clazz.getDeclaredMethod("doService");
                method.invoke(clazz.newInstance());
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } catch (SecurityException e) {
                e.printStackTrace();
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            } catch (InstantiationException e) {
                e.printStackTrace();
            }
        }

    }

}
