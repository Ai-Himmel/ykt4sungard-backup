/**
 * 
 */
package com.kingstargroup.ecard.util;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: CardListPool.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-8  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */

import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.SystemProperties;
import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

public class EcardInformationPool{
	
	public static void clear() {
		_instance._clear();
	}

	public static EcardInformation get(String infoId) {
		return _instance._get(infoId);
	}

	public static EcardInformation put(String infoId, EcardInformation obj) {
		return _instance._put(infoId, obj);
	}

	public static EcardInformation remove(String infoId) {
		return _instance._remove(infoId);
	}

	private EcardInformationPool() {
		_cacheable = EcardConstants.INFO_CACHEABLE;

		int maxSize = EcardConstants.INFO_CACHE_MAXSIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
//		CacheRegistry.register(this);
		GlobalPool.registerPool(EcardInformationPool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private EcardInformation _get(String infoId) {
		if (!_cacheable) {
			return null;
		}
		else if (infoId == null) {
			return null;
		}
		else {
			EcardInformation obj = null;
			String key = infoId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (EcardInformation)_cache.getFromCache(key);
			}
			catch (NeedsRefreshException nfe) {
			}
			finally {
				if (obj == null) {
					_cache.cancelUpdate(key);
				}
			}

			return obj;
		}
	}

	private EcardInformation _put(String infoId, EcardInformation obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (infoId == null) {
			return obj;
		}
		else {
			String key = infoId.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private EcardInformation _remove(String infoId) {
		if (!_cacheable) {
			return null;
		}
		else if (infoId == null) {
			return null;
		}
		else {
			EcardInformation obj = null;
			String key = infoId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (EcardInformation)_cache.getFromCache(key);
				_cache.flushEntry(key);
			}
			catch (NeedsRefreshException nfe) {
			}
			finally {
				if (obj == null) {
					_cache.cancelUpdate(key);
				}
			}

			return obj;
		}
	}

	private static EcardInformationPool _instance = new EcardInformationPool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
