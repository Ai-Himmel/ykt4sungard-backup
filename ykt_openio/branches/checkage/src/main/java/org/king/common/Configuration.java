package org.king.common;

import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * read properties from file,it should be initialized by calling static load method.before you use it
 * User: Yiming.You
 * Date: 2011-4-27
 */
public class Configuration {
    private static final Logger logger = Logger.getLogger(Configuration.class);

    protected static Properties properties = new Properties();

    public static void load() {
        InputStream inputStream = null;
        try {
            logger.info("loading properties:" + Constant.PROPERTY_FILE_NAME + "......");
            inputStream = ClassLoader.getSystemResourceAsStream(Constant.PROPERTY_FILE_NAME);
            properties.load(inputStream);
            logger.info("succeed to load properties:" + Constant.PROPERTY_FILE_NAME);
        } catch (IOException e) {
            logger.info("fail to load properties:" + Constant.PROPERTY_FILE_NAME);
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
        return properties.getProperty(key);
    }

    public static String getProperty(String key, String defaultValue) {
        return properties.getProperty(key, defaultValue);
    }
}
