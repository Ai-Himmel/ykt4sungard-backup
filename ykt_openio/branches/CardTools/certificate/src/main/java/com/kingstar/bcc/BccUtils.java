package com.kingstar.bcc;

import org.apache.log4j.Logger;
import org.xvolks.jnative.JNative;
import org.xvolks.jnative.Type;
import org.xvolks.jnative.exceptions.NativeException;

import java.io.File;


public class BccUtils {
    private static final Logger logger = Logger.getLogger(BccUtils.class);

    private static JNative bccclt = null;

    private static final String BCCCLT_DLL = "bccclt.dll";

    public static void loadLibrary() {
        String userDir = System.getProperty("user.dir");
        String dll = userDir + File.separator + BCCCLT_DLL;
        File dllFile = new File(dll);
        if (!dllFile.exists()) {
            throw new RuntimeException("无法加载动态库：" + dll);
        }
        System.load(dll);
        JNative.setLoggingEnabled(true);
        logger.info("加载动态库成功：" + dll);
    }

    public static boolean BCCCLTInit(int maxnodes) {
        boolean success = false;
        try {
            bccclt = new JNative(BCCCLT_DLL, "BCCCLTInit");
            //指定返回参数的类型
            bccclt.setRetVal(Type.INT);
            int i = 0;
            bccclt.setParameter(i++, Type.INT, String.valueOf(maxnodes));
            logger.debug("invoke method " + "BCCCLTInit");
            //调用方法
            bccclt.invoke();
            //获取返回值
            int returnValue = bccclt.getRetValAsInt();
            logger.debug("BCCCLTInit" + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    public static boolean XPackInit(int maxXPackDefs) {
        boolean success = false;
        try {
            bccclt = new JNative(BCCCLT_DLL, "XPackInit");
            //指定返回参数的类型
            bccclt.setRetVal(Type.INT);
            int i = 0;
            bccclt.setParameter(i++, Type.INT, String.valueOf(maxXPackDefs));
            logger.debug("invoke method " + "XPackInit");
            //调用方法
            bccclt.invoke();
            //获取返回值
            int returnValue = bccclt.getRetValAsInt();
            logger.debug("XPackInit" + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    public static boolean AddDrtpNode(String ip, int port) {
        boolean success = false;
        try {
            bccclt = new JNative(BCCCLT_DLL, "AddDrtpNode");
            //指定返回参数的类型
            bccclt.setRetVal(Type.INT);
            int i = 0;
            bccclt.setParameter(i++, Type.STRING, ip);
            bccclt.setParameter(i++, Type.INT, String.valueOf(port));
            logger.debug("invoke method " + "AddDrtpNode");
            //调用方法
            bccclt.invoke();
            //获取返回值
            int returnValue = bccclt.getRetValAsInt();
            logger.debug("AddDrtpNode" + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    public static boolean NewXpackHandle(String XpackDescribleFile) {
        boolean success = false;
        try {
            bccclt = new JNative(BCCCLT_DLL, "NewXpackHandle");
            //指定返回参数的类型
            bccclt.setRetVal(Type.INT);
            int i = 0;
            bccclt.setParameter(i++, Type.STRING, XpackDescribleFile.getBytes());
            logger.debug("invoke method " + "NewXpackHandle");
            //调用方法
            bccclt.invoke();
            //获取返回值
            int returnValue = bccclt.getRetValAsInt();
            logger.debug("NewXpackHandle" + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }
}
