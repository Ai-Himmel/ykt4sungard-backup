package org.king.common;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.util.Properties;

/**
 * read properties from file,it should be initialized by calling static load method before you use it
 * User: Yiming.You
 * Date: 2011-7-06
 */
public class Configuration {
    private static final Logger logger = Logger.getLogger(Configuration.class);

    protected static Properties properties = new Properties();

    public static void load() {
        InputStream inputStream = null;
        try {
            logger.info("loading properties:" + Constant.PROPERTY_FILE_NAME + "......");
            inputStream = Configuration.class.getClassLoader().getResourceAsStream(Constant.PROPERTY_FILE_NAME);
            properties.load(inputStream);
            logger.info("succeed in loading properties:" + Constant.PROPERTY_FILE_NAME);
        } catch (IOException e) {
            logger.info("fail in loading properties:" + Constant.PROPERTY_FILE_NAME);
        } finally {
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException e) {
                }
            }
        }
    }

    public static String getProperty(String key) {
        String value = properties.getProperty(key);
        if (StringUtils.isNotBlank(value)) {
            try {
                value = new String(value.getBytes("ISO8859-1"), "UTF-8");
            } catch (UnsupportedEncodingException e) {
                logger.warn("转换字符失败[ISO8859-1-----UTF-8]");
            }
        }
        return value;
    }

    public static String getProperty(String key, String defaultValue) {
        String value = properties.getProperty(key);
        if (StringUtils.isNotBlank(value)) {
            try {
                value = new String(value.getBytes("ISO8859-1"), "UTF-8");
            } catch (UnsupportedEncodingException e) {
                logger.warn("转换字符失败[ISO8859-1-----UTF-8]");
            }
        } else {
            value = defaultValue;
        }
        return value;
    }

    public static int getIntProperty(String key, int defaultValue) {
        String value = properties.getProperty(key);
        int returnValue = defaultValue;
        try {
            if (StringUtils.isNotBlank(value)) {
                returnValue = Integer.valueOf(value);
            }
        } catch (NumberFormatException e) {
            logger.error("Int类型转换失败：[" + key + "]");
        }
        return returnValue;
    }
}
