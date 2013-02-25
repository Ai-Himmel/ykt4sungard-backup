/*
 * BccServer.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	BccServer.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Modifier;
import java.net.URL;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Properties;
import java.util.Set;

import javax.annotation.PreDestroy;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.kingstar.bcc.bccsvr;
import com.opensymphony.xwork2.util.ResolverUtil;
import com.sungard.smartcard.annotation.SmartCardFunction;

/**
 * 服务器端服务类. 负责建立通迅服务.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public class BccServer {

    private Logger logger = LoggerFactory.getLogger(BccServer.class);

    /**
     * 全局静态成员
     */
    // private static BccServer self;
    private BccServer self;
    /*
     * 以下为成员
     */
    /*
     * 内部本地方法类对象
     */
    private bccsvr resource = null;

    /*
     * 配置文件参数
     */
    private Properties properties = null;

    /*
     * 内建服务号.
     */
    private int svrID = -1;

    /*
     * 会话对象集合
     */
    private Map<String, BccServerThread> SessionMap = null;
    private ThreadGroup threadGroup;

    /*
     * 默认的XPack定义文件名，
     */
    private String XpackFileName = null;
    private String basePath;
    private String serverInfo;

    /*
     * 初始标记，一般只允许做一次初始操作
     */
    private boolean initFlag = false;

    // ///////////////////////////////////////////////////////////

    /**
     * 构造方法
     */
    public BccServer() {
        logger.info("new BccServer");
        // System.out.println("new BccServer");
        resource = new bccsvr();
        SessionMap = new HashMap<String, BccServerThread>();
        threadGroup = new ThreadGroup("smartCardThreadGroup");
        XpackFileName = new String("cpack.dat");
        properties = new Properties();
        /*
         * 加载配置，并进行初始环境
         */
        if (LoadConfig()) {
            InitEnv();
        } else {
            System.out.println("LoadConfig Error:Check smartServer.conf");
        }
    }

    /**
     * 获取唯一实例的方法
     * 
     * @return
     */
    // public static BccServer GetInstance() {
    // if (null == self)
    // self = new BccServer();
    // return self;
    // }

    /**
     * 获取本地资源对象
     * 
     * @return
     */
    public bccsvr GetResource() {
        if (null == resource) {
            System.out.println("resource is null");
        }
        return resource;
    }

    /**
     * 获取XPack定义文件名
     * 
     * @return
     */
    public String GetXpackFileName() {
        return XpackFileName;
    }

    /**
     * 设置XPack定义文件名
     * 
     * @param name
     */
    public void SetXpackFileName(String name) {
        XpackFileName = new String(name);
    }

    public String getBasePath() {
        return basePath;
    }

    public String getServerInfo() {
        return serverInfo;
    }

    public void setServerInfo(String serverInfo) {
        this.serverInfo = serverInfo;
    }

    /**
     * 初始化环境数据
     * 
     * @param XpackCount
     * @param ServerCount
     * @return
     */
    private boolean InitEnv() {
        if (initFlag) {
            return true;
        }

        initFlag = true;
        return true;
    }

    /**
     * 创建服务线程.<br/>
     * 
     * @return BccServerThread
     * @since v1.00
     * @see #CreateSession(String, String);
     */
    public BccServerThread CreateSession() {
        return CreateSession(null, null);
    }

    /**
     * 创建服务线程.<br/>
     * 
     * @param key
     * @return BccServerThread
     * @since v1.00
     * @see #CreateSession(String, String);
     */
    public BccServerThread CreateSession(String key) {
        return CreateSession(key, null);
    }

    /**
     * 创建会话对象，创建资源句柄 可以将句柄放入集合进行管理，也可以不管
     * 
     * @param key
     * @param XpackFile
     * @return
     */
    public BccServerThread CreateSession(String key, String XpackFile) {
        long handle = 0;
        if (null == XpackFile) {
            handle = GetResource().NewXpackHandle(XpackFileName.getBytes());
            logger.info("XpackFileName={}",XpackFileName);
            if (0 == handle) {
                System.out.println("NewXpackHandle1 is null :" + XpackFileName);
                return null;
            }
        } else {
            System.out.println(XpackFile);
            handle = GetResource().NewXpackHandle(XpackFile.getBytes());
            if (0 == handle) {
                System.out.println("NewXpackHandle2 is null :" + XpackFile);
                return null;
            }
        }
        // System.out.println("NewXpackHandle() :" + handle);
        logger.info("NewXpackHandle() :{} XpackFile={}", handle,XpackFile);
        if (null == key) {
            return new BccServerThread(GetResource(), handle);
        } else {
            SessionMap.put(key, new BccServerThread(GetResource(), handle));
            return (BccServerThread) SessionMap.get(key);
        }
    }

    // /**
    // * 获取资源句柄
    // */
    // public ClientSession GetSession(String key) {
    // return (ClientSession) SessionMap.get(key);
    // }

    /**
     * 按照键来删除会话
     * 
     * @param key
     */
    public void RemoveSession(String key) {
        SessionMap.remove(key);
    }

    /**
     * 加载配置文件，这样便于管理
     * 
     * @return
     */
    public boolean LoadConfig() {
        ClassLoader loader = null;
        try {
            loader = Thread.currentThread().getContextClassLoader();
        } catch (SecurityException e) {
            e.printStackTrace();
            return false;
        }
        if (null == loader)
            return false;

        URL url = null;
        /**
         * 注意这里的文件位置，可以放在CLASSPATH下
         */
        url = loader.getResource("conf/smartServer.conf");
        if (null == url) {
            System.out.println("not get resource smartServer.conf");
            return false;
        }
        String path = url.getPath();
        path = path.substring(1, path.indexOf("conf/smartServer.conf"));
        basePath = path;
        logger.info("url={}", path);
        XpackFileName = path + "lib/cpack.dat";

        InputStream in = null;

        try {
            in = url.openStream();
        } catch (Exception urlex) {
            urlex.printStackTrace();
            return false;
        }

        if (null == in)
            return false;
        try {
            properties.load(in);
            in.close();
        } catch (IOException ioex) {
            ioex.printStackTrace();
            return false;
        } finally {
        }
        return true;
    }

    /**
     * 获取配置参数的数值
     * 
     * @param key
     * @param defaultValue
     * @return
     */
    public String GetConfig(String key, String defaultValue) {
        return properties.getProperty(key, defaultValue);
    }

    /**
     * 另一种获取方法
     * 
     * @param key
     * @param defaultValue
     * @return
     */
    public int GetConfig(String key, int defaultValue) {
        String value = GetConfig(key, "" + defaultValue);
        try {
            return Integer.valueOf(value).intValue();
        } catch (Exception ex) {
            ex.printStackTrace();
            return defaultValue;
        }
    }

    // static {
    // self = null;
    // }

    public boolean startService() {
        logger.info(" ------------ start service {}, {}", SessionMap.size(), BccServer.class.getClassLoader());

        if (null == FunctionSet.getFunctionSet()) {

            String DEFAULT_PACKAGE = "com.sungard.smartcard";
            String[] entityPackage = { DEFAULT_PACKAGE };

            /*
             * 扫描自定义annotation
             */
            ResolverUtil<Object> resolver = new ResolverUtil<Object>();
            resolver.findAnnotated(SmartCardFunction.class, entityPackage);
            Set<Class<? extends Object>> valueObjectSet = resolver.getClasses();
            Set<Class<? extends Object>> functionSet = new HashSet<Class<? extends Object>>();
            logger.info("AutoLoadAnnotation SmartCardFunction - Set<Class<? extends Object>> voSet=" + valueObjectSet);
            Class<? extends Object> item;
            for (Iterator<Class<? extends Object>> iterator = valueObjectSet.iterator(); iterator.hasNext();) {
                item = iterator.next();
                // SmartCardFunction temp =
                // item.getAnnotation(SmartCardFunction.class);
                if (!Modifier.isInterface(item.getModifiers()) && !Modifier.isAbstract(item.getModifiers())) {
                    functionSet.add(item);
                    logger.info("add model is {}", item.getName());
                }
            }
            FunctionSet.setFunctionSet(functionSet);// 设计全局静态方法

            HashMap<Integer, Function> map = new HashMap<Integer, Function>();
            for (Iterator<Class<? extends Object>> iterator = functionSet.iterator(); iterator.hasNext();) {
                @SuppressWarnings("unchecked")
                Class<? extends ServiceI> class1 = (Class<? extends ServiceI>) iterator.next();
                SmartCardFunction temp = class1.getAnnotation(SmartCardFunction.class);
                logger.info("class1={}", class1);
                try {
                    map.put(temp.funcnum(), new Function(temp.infotype(), temp.funcnum(), class1.newInstance()));
                } catch (InstantiationException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
            BccServerThread.setProcesses(map);// 设置全部方法理类.
        }

        if (SessionMap.size() > 0) {

            String[] svrInfos = StringUtils.split(getServerInfo(), ":");

            String ip = svrInfos[0];
            int port = Integer.parseInt(svrInfos[1]);
            int branchno = Integer.parseInt(svrInfos[2]);

            int funcno = GetConfig("bcc.drtp.funcno", 600);
            int funcount = GetConfig("bcc.xpack.count", 2);
            // int offset = GetConfig("bcc.xpack.offset", 1);

            // int branchno = GetConfig("bcc.drtp.branchno", 400);
            // String ip = GetConfig("bcc.drtp.ip", "10.253.42.200");
            // int port = GetConfig("bcc.drtp.port", 4000);
            // int funcno = GetConfig("bcc.drtp.funcno", 6000);
            // int funcount = GetConfig("bcc.xpack.count", 2);
            // int offset = GetConfig("bcc.xpack.offset", 1);

            String logpath = GetConfig("bcc.smartcard.logpath", basePath + "logs");
            String logflag = GetConfig("bcc.smartcard.logflag", "true");

            if ("true".equals(logflag)) {
                if ("".equals(logpath)) {
                    logpath = basePath + "logs";
                }
                logger.info("logpath= {}", logpath);
                GetResource().KLGOpen(logpath.getBytes());
            }

            int[] funclist = new int[funcount];
            funclist[0] = Integer.parseInt(svrInfos[3]);
            // funclist[0] = funcno + offset;
            funclist[1] = funcno;
            svrID = GetResource().AddService(branchno, ip.getBytes(), port, funclist, funcount, true);

            String[] a = new String[SessionMap.size()];
            SessionMap.keySet().toArray(a);
            for (int i = 0; i < a.length; i++) {
                SessionMap.get(a[i]).Start(threadGroup, svrID);
            }
            return true;
        }

        return false;
    }

    /**
     * 
     * 移除服务.<br/>
     * 
     * @return
     * @since v1.00
     * @see com.kingstar.bcc#RemoveService(int svrID)
     */
    @PreDestroy
    public boolean stopService() {
        logger.info(" ------------ stop service {}, {}", SessionMap.size(), BccServer.class.getClassLoader());
        if (SessionMap.size() > 0) {
            String[] a = new String[SessionMap.size()];
            SessionMap.keySet().toArray(a);
            for (int i = 0; i < a.length; i++) {
                SessionMap.get(a[i]).setFlag(false);
            }
        }
        //
        // Thread shutdownThread = new Thread("stop_thread") {
        // public void run() {
        // logger.info("stop_thread...===========");
        // try {
        // sleep(10000);
        // } catch (InterruptedException e) {
        // e.printStackTrace();
        // }
        // }
        // };
        // shutdownThread.setDaemon(true);
        // shutdownThread.start();

        int loop = 5;

        while (threadGroup.activeCount() > 0) {
            logger.info(" threadGroup.activeCount()  {}", threadGroup.activeCount());

            // Thread thrds[] = new Thread[threadGroup.activeCount()];
            // threadGroup.enumerate(thrds);
            // for (Thread t : thrds)
            // logger.info(" t.getName() {}", t.getName());

            try {
                loop--;
                if (loop < 0) {
                    Thread.currentThread().stop();
                    System.exit(0);
                }

                // shutdownThread.sleep(1000);
                // logger.info(" already has active thread, wait 1 sec  {}",
                // shutdownThread.getName());
                Thread.currentThread().sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // try {
        // shutdownThread.join(1000);
        // } catch (InterruptedException e) {
        // e.printStackTrace();
        // }

        return GetResource().RemoveService(svrID);
    }

    public int getSvrID() {
        return svrID;
    }

    @Override
    protected void finalize() throws Throwable {
        stopService();
        logger.info(" ------------ finalize stop service ");
        super.finalize();
    }

}
