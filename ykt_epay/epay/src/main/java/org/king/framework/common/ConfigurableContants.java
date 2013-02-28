package org.king.framework.common;

import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class ConfigurableContants {
    private static final Logger logger = Logger.getLogger(ConfigurableContants.class);
    protected static Properties p = new Properties();

    protected static void init(String propertyFileName) {
        InputStream in = null;
        try {
            in = ClassLoader.getSystemResourceAsStream(propertyFileName);
            if (in != null)
                p.load(in);
        } catch (IOException e) {
            logger.error("load " + propertyFileName + " into Contants error");
        }
        finally {
            if (in != null)
                try {
                    in.close();
                }
                catch (IOException e) {
                }
        }
    }

    protected static String getProperty(String key, String defaultValue) {
        return p.getProperty(key, defaultValue);
    }
}