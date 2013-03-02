package org.king.dictionary;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.king.classmanage.domain.Department;
import org.king.framework.dao.BaseDAO;

public class CompanyDict extends baseDictonary {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(CompanyDict.class);

	private BaseDAO baseDAO;

	/**
	 * @param baseDAO
	 *            The baseDAO to set.
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public String getKey() {
		return DictionaryContants.COMPANY;
	}

	public boolean loadDiction(Map dict) {

		try {
			_serial = dict;
			List list = baseDAO.findEntity("from Department");
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				Department department = (Department) iter.next();
				dict.put(department.getDeptCode(), department.getDeptName());
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
