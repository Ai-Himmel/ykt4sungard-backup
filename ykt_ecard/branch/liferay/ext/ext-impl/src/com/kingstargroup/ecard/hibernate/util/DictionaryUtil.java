/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.card.TCardtype;
import com.kingstargroup.ecard.hibernate.dictionary.DictionaryPersistence;
import com.kingstargroup.ecard.hibernate.dictionary.TDictionary;

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
public class DictionaryUtil {
	/**
	 * Description:
	 * @param dicNo
	 * @param dicValue
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TDictionary getDictionary(long dicttype, String dictval) throws PortalException {
		TDictionary dic = null;
		try {
			dic = getPersistence().getDictionaryByPK(getPersistence().createPK(dicttype, dictval));
		} catch (DBSystemException dbse) {
			throw dbse;
		}
		return dic;
	}	
	
	public static TCardtype getCardType(Long cardtype) throws PortalException {
		TCardtype tcardtype = null;
		try {
			tcardtype = getPersistence().getCardTypebyPk(cardtype);
		} catch (DBSystemException dbse) {
			throw dbse;
		}
		return tcardtype;
	}	
	
	
	public static DictionaryPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DictionaryPersistence persistence) {
		_persistence = persistence;
	}

	private static DictionaryUtil _getUtil() {
		if (_util == null) {
			_util = (DictionaryUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DictionaryUtil.class.getName();
	private static DictionaryUtil _util;
	private DictionaryPersistence _persistence;
}
