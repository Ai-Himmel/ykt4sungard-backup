/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.utils.ContantsUtil.java
 * �������ڣ� 2006-6-15 16:45:14
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-15 16:45:14      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.utils;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import org.apache.log4j.Logger;

/**
 * <p> ContantsUtil.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="ContantsUtil.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 * 
 *
 */
public class Contants extends ConfigurableContants{
	
    static {
        init("oneks.properties");
    }
    
    
    public final static String LDAP_PATH = getProperty("constant.ldap.path", "/");
	
    

    
    
    

    
}
