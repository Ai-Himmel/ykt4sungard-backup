/**
 * 
 */
package com.kingstargroup.ecard.hibernate.dictionary;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.card.TCardtype;
import com.liferay.portal.service.persistence.BasePersistence;

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
public class DictionaryPersistence extends BasePersistence {
	/**
	 * Description: 生成字典表主键
	 * @param dictNo 字典索引号
	 * @param dictValue 字典索引值
	 * @return TPifDictionaryKey主键对象
	 * Modify History:
	 */
	public TDictionaryId createPK(long dicttype, String dictval) {
		TDictionaryId key = new TDictionaryId();
		key.setDicttype(new Long(dicttype));
		key.setDictval(dictval);
		return key;
	}
	
	/**
	 * Description:根据字典表主键查询返回字典对象
	 * @param key 字典表主键
	 * @return TPifDictionary持久对象
	 * Modify History:
	 */
	public TDictionary getDictionaryByPK(TDictionaryId key) throws DBSystemException {
		TDictionary dictionary = null;
		Session s = null;
		try {			
			s = openSession();
			dictionary = (TDictionary) s.get(TDictionary.class, key);			
			return dictionary;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		} finally{
			closeSession(s);
		}
	}
	
	
	public TCardtype getCardTypebyPk(Long key)throws DBSystemException {
		TCardtype tcardtype = null;
		Session s = null;
		try {			
			s = openSession();
			tcardtype = (TCardtype) s.get(TCardtype.class, key);			
			return tcardtype;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		} finally{
			closeSession(s);
		}
	}
	
	private static final Log _log = LogFactory.getLog(DictionaryPersistence.class);
}
