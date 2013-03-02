/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.framework.dao.BaseDAOTestCase.java
 * 创建日期： 2006-4-17 11:21:34
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-17 11:21:34      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.framework.dao;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.MissingResourceException;
import java.util.ResourceBundle;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.test.AbstractTransactionalDataSourceSpringContextTests;
  
/**
 * <p> BaseDAOTestCase.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="BaseDAOTestCase.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-17
 * 
 *
 */
public abstract class BaseDaoTestCase extends
		AbstractTransactionalDataSourceSpringContextTests {

	
	protected final Log log = LogFactory.getLog(getClass());
	protected ResourceBundle rb;
	
	/* (non-Javadoc)
	 * @see org.springframework.test.AbstractDependencyInjectionSpringContextTests#getConfigLocations()
	 */
	protected String[] getConfigLocations() {
		setAutowireMode(AUTOWIRE_BY_NAME);
        return new String [] {"classpath*:/WEB-INF/spring/*.xml"
                              };
	}
	
    public BaseDaoTestCase() {
        // Since a ResourceBundle is not required for each class, just
        // do a simple check to see if one exists
        String className = this.getClass().getName();

        try {
            rb = ResourceBundle.getBundle(className);
        } catch (MissingResourceException mre) {
            //log.warn("No resource bundle found for: " + className);
        }
    }
    
    /**
     * Utility method to populate a javabean-style object with values
     * from a Properties file
     * @param obj
     * @return Object populated object
     * @throws Exception
     */
    protected Object populate(Object obj) throws Exception {
        // loop through all the beans methods and set its properties from
        // its .properties file
        Map map = new HashMap();

        for (Enumeration keys = rb.getKeys(); keys.hasMoreElements();) {
            String key = (String) keys.nextElement();
            map.put(key, rb.getString(key));
        }

        BeanUtils.copyProperties(obj, map);

        return obj;
    }
}
