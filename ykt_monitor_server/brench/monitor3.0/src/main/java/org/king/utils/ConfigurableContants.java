/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.utils.ConfigurableContants.java
 * �������ڣ� 2006-6-15 17:02:10
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-15 17:02:10      ljf        �����ļ���ʵ�ֻ�������
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
 * <p> {����˵��} </p>
 *
 * <p><a href="ConfigurableContants.java.html"><i>�鿴Դ����</i></a></p>  
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
