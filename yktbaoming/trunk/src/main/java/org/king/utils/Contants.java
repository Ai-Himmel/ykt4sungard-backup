/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.utils.ContantsUtil.java
 * 创建日期： 2006-6-15 16:45:14
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-15 16:45:14      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="ContantsUtil.java.html"><i>查看源代码</i></a></p>  
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
