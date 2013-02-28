package org.king.utils;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import java.io.File;
import java.io.UnsupportedEncodingException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-10-18
 */
public class BccUtil {
    private static final Logger logger = Logger.getLogger(BccUtil.class);

    public static String getStringFromByte(byte[] inStr) {
        int t;
        for (t = 0; t < inStr.length; t++) {
            if (inStr[t] == 0) {
                break;
            }
        }
        String ret;
        try {
            ret = new String(inStr, 0, t, "GBK");
        } catch (UnsupportedEncodingException e) {
            logger.error(e.getMessage());
            ret = new String(inStr, 0, t);
        }
        return ret;
    }

    public static boolean isWindowsOS() {
        boolean isWindowsOS = false;
        String osName = System.getProperty("os.name");
        if (osName.toLowerCase().indexOf("windows") > -1) {
            isWindowsOS = true;
        }
        return isWindowsOS;
    }

    public static String getLibrary(String libraryDir) {
        if (StringUtils.isBlank(libraryDir)) {
            throw new RuntimeException("library dir can't not be null");
        }
        if (!libraryDir.endsWith("/") && !libraryDir.endsWith("\\")) {
            libraryDir += File.separator;
        }
        if (isWindowsOS()) {
            return libraryDir + "bccclt.dll";
        } else {
            return libraryDir + "libbccclt.so";
        }
    }

    public static String getCpack(String libraryDir) {
        if (StringUtils.isBlank(libraryDir)) {
            throw new RuntimeException("library dir can't not be null");
        }
        if (!libraryDir.endsWith("/") && !libraryDir.endsWith("\\")) {
            libraryDir += File.separator;
        }
        return libraryDir + "cpack.dat";
    }
}
