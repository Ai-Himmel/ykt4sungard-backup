/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.tracking.web.filter.Log4JUserFilter.java
 * �������ڣ� 2006-6-8 19:35:03
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-8 19:35:03      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.tracking.web.filter;

import javax.servlet.Filter;
import javax.servlet.http.HttpSession;

import org.king.tracking.web.BaseLog4JUserFilter;

/**
 * <p> Log4JUserFilter.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="Log4JUserFilter.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-8
 * 
 *
 */
public class Log4JUserFilter extends BaseLog4JUserFilter implements Filter {

	/* (non-Javadoc)
	 * @see org.king.tracking.web.BaseLog4JUserFilter#getUserId(javax.servlet.http.HttpSession)
	 */
	protected String getUserId(HttpSession session) {
		  String userId = (String)session.getAttribute("account");
	        if (userId == null)
	            return null;
	        else
	            return userId;

	}

}
