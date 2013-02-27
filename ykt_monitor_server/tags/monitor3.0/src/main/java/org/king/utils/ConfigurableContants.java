/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.utils.ConfigurableContants.java
 * 创建日期： 2006-6-15 17:02:10
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-15 17:02:10      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.utils;

import org.apache.log4j.Logger;


import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;


/**
 * <p> ConfigurableContants.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ConfigurableContants.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 * 
 *
 */
public class ConfigurableContants {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ConfigurableContants.class);

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
            if (in != null) {
                try {
                    in.close();
                } catch (IOException e) {
                }
            }
        }
    }

    protected static String getProperty(String key, String defaultValue) {
        return p.getProperty(key, defaultValue);
    }

}
