package org.king.dictionary;

import java.util.Map;

import org.king.framework.dao.BaseDAO;

public class baseDictonary implements YKTDictionEntry {

	public String getKey() {
		return "";
	}

	public boolean loadDiction(Map dict) {
			return true;
	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if(_serial != null)
			return _serial.get(key);
		return null;
	}

	private Map _serial = null;
}
