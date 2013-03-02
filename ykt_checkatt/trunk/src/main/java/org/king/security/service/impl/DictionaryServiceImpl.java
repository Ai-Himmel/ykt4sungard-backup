/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.impl.DictionaryServiceImpl.java
 * �������ڣ� 2006-6-20 13:23:44
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-20 13:23:44      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service.impl;

import java.util.List;

import org.king.security.dao.DictionaryDAO;
import org.king.security.service.DictionaryService;

/**
 * <p> DictionaryServiceImpl.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="DictionaryServiceImpl.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-20
 * 
 *
 */
public class DictionaryServiceImpl implements DictionaryService {

	private DictionaryDAO dictionaryDAO;
	
	
	public void setDictionaryDAO(DictionaryDAO dictionaryDAO) {
		this.dictionaryDAO = dictionaryDAO;
	}


	/* (non-Javadoc)
	 * @see org.king.security.service.DictionaryService#findDictionaryByNo(java.lang.String)
	 */
	public List findDictionaryByNo(String dictNo) {
		String hql = "from Dictionary d where d.id.dictNo = "+dictNo+" order by d.dictOrder";
		return dictionaryDAO.find(hql);
	}

}
