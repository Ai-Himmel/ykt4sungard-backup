/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.dictionary.DictionaryPersistence;
import com.kingstargroup.ecard.hibernate.dictionary.TPifDictionary;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: DictionaryUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DictionaryUtil extends BasicUtil {
	/**
	 * Description:
	 * @param dicNo
	 * @param dicValue
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TPifDictionary getDictionary(int dicNo, String dicValue) throws PortalException {
		DictionaryPersistence persistence = (DictionaryPersistence) getPersistence(DictionaryPersistence.class.getName());
		Transaction t = beginTransaction();
		TPifDictionary dic = null;
		try {
			dic = persistence.getDictionaryByPK(persistence.createPK(dicNo, dicValue));
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
		return dic;
	}	
}
