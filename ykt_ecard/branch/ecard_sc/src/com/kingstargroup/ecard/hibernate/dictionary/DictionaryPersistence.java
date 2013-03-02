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
 * Description: 字典表持久操作对象
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DictionaryPersistence extends BasicPersistence {
	/**
	 * Description: 生成字典表主键
	 * @param dictNo 字典索引号
	 * @param dictValue 字典索引值
	 * @return TPifDictionaryKey主键对象
	 * Modify History:
	 */
	public TPifDictionaryKey createPK(int dictNo, String dictValue) {
		TPifDictionaryKey key = new TPifDictionaryKey();
		key.setDictNo(new Integer(dictNo));
		key.setDictValue(dictValue);
		return key;
	}
	
	/**
	 * Description:根据字典表主键查询返回字典对象
	 * @param key 字典表主键
	 * @return TPifDictionary持久对象
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
