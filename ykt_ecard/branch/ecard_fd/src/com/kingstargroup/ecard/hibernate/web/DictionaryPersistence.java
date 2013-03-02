/**
 * 
 */
package com.kingstargroup.ecard.hibernate.web;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.equipment.Maintain;

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
	
	

	
	public WebDictionaryKey createPK(String dicNo, String dicValue) {
		WebDictionaryKey key = new WebDictionaryKey();
		key.setDicNo(dicNo);
		key.setDicValue(dicValue);
		return key;
	}
	
	public void  delete(WebDictionary dic)  throws DBSystemException {
		Session s = getSession();
		try {			
		   s.delete(dic);
		}catch(HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:�����ֵ��������ѯ�����ֵ����
	 * @param key �ֵ������
	 * @return WebDicitionaryKey�־ö���
	 * Modify History:
	 */
	public WebDictionary getDictionaryByPK(WebDictionaryKey key) throws DBSystemException {
		WebDictionary dictionary = null;
		Session s = getSession();
		try {			
			dictionary = (WebDictionary) s.get(WebDictionary.class, key);			
			return dictionary;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public  List getDictionaryByDicNo(String  dicNo) throws DBSystemException {
		Session s = getSession();
		try{
			StringBuffer Hql = new StringBuffer(" from WebDictionary  d  where d.id.dicNo= '"+dicNo+"'");
			Query query = s.createQuery(Hql.toString());
			return  query.list();
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}

	
	private static final Log _log = LogFactory.getLog(DictionaryPersistence.class);
}
