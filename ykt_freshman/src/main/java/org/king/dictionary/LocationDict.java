package org.king.dictionary;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.king.classmanage.domain.Dictionary;
import org.king.framework.dao.BaseDAO;

public class LocationDict extends baseDictonary {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LocationDict.class);

	private BaseDAO baseDAO;

	/**
	 * @param baseDAO
	 *            The baseDAO to set.
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public String getKey() {
		return DictionaryContants.LOCATION;
	}

	public boolean loadDiction(Map dict) {

		try {
			_serial = dict;
			List list = baseDAO
					.findEntity("from Dictionary a where a.id.dictNo=6");
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				Dictionary dictionary = (Dictionary) iter.next();
				dict.put(dictionary.getId().getDictValue(), dictionary
						.getDictCaption());
			}
			return true;
		} catch (Exception e) {
			logger.error("读取交易代码字典失败", e);
		}
		return false;
	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if (_serial != null)
			return _serial.get(key);
		return null;
	}

	private Map _serial = null;
}
