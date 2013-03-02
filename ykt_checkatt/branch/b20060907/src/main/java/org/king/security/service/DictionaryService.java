/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.DictionaryService.java
 * �������ڣ� 2006-6-20 13:19:11
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-20 13:19:11      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.util.List;

import org.king.framework.service.Service;

/**
 * <p> DictionaryService.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="DictionaryService.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-20
 * 
 *
 */
public interface DictionaryService extends Service {

	/**
	 * ͨ���ֵ��Ų����ֵ�
	 * @param dictNo
	 * @return
	 */
	public List findDictionaryByNo(String dictNo);
}
