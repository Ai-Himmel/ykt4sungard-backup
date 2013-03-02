/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.Acl.java
 * �������ڣ� 2006-4-19 22:56:56
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-19 22:56:56      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.util.Collection;
import java.util.Map;

import org.king.security.domain.Account;

/**
 * <p> Acl.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="Acl.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 *
 */
public interface Acl {
   
	/**
	 * �ж��Ƿ����ܱ�������Դ
	 * @param url
	 * @return
	 */
	public boolean isProtectedResource(String url);

    /**
     * �õ������ܱ�������Դ
     * @return
     */
	public Collection getProtectedResources();

   /**
    * ���ñ�����Դ
    * @param map
    */
	public void setProtectedResourcesMap(Map map);

	/**
	 * �ж��Ƿ���Ȩ��
	 * @param url
	 * @param account
	 * @return
	 */
	public boolean hasRight(String url, Account account);
}
