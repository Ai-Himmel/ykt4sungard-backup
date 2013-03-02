/**
 * 
 */
package com.kingstargroup.ecard.hibernate.dictionary;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: DictionaryPersistence.java
 * Description: �ֵ��־ò�������
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DictionaryPersistence extends BasicPersistence {
	/**
	 * Description: �����ֵ������
	 * @param dictNo �ֵ�������
	 * @param dictValue �ֵ�����ֵ
	 * @return TPifDictionaryKey��������
	 * Modify History:
	 */
	public TPifDictionaryKey createPK(int dictNo, String dictValue) {
		TPifDictionaryKey key = new TPifDictionaryKey();
		key.setDictNo(new Integer(dictNo));
		key.setDictValue(dictValue);
		return key;
	}
	
	/**
	 * Description:�����ֵ��������ѯ�����ֵ����
	 * @param key �ֵ������
	 * @return TPifDictionary�־ö���
	 * Modify History:
	 */
	public TPifDictionary getDictionaryByPK(TPifDictionaryKey key) throws DBSystemException {
		TPifDictionary dictionary = null;
		Session s = getSession();
		try {			
			dictionary = (TPifDictionary) s.get(TPifDictionary.class, key);			
			return dictionary;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(DictionaryPersistence.class);
}
