package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.util.HashMap;

import com.kingstargroup.fdykt.YKTException;

public class YKTDictionary {
	static private class DictEntry {
		private YKTDictionEntry _entry;

		private long _timeTick;

		private HashMap _dict;

		public boolean releaseDict() {
			_entry.releaseDiction();
			_dict.clear();
			return true;
		}

		public void updateTimeTick() {
			_timeTick = System.currentTimeMillis();
		}

		DictEntry() {
			_dict = new HashMap();
			_entry = null;
			updateTimeTick();
		}

		DictEntry(YKTDictionEntry entry) {
			this();
			_entry = entry;
		}
	}

	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(YKTDictionary.class);

	private static YKTDictionary _instance = null;

	private static Object _mutex = new Object();

	private HashMap _dicts;

	private long _timeInterval;

	private YKTDictionary() {
		// dummy
		_dicts = new HashMap();
		_timeInterval = 8640000L;
	}

	public static YKTDictionary getInstance() {
		synchronized (_mutex) {
			if (_instance == null) {
				_instance = new YKTDictionary();
			}
		}
		return _instance;
	}

	public boolean registeDictionary(YKTDictionEntry entry) {
		return registeDictionary(entry, true);
	}

	public boolean registeDictionary(YKTDictionEntry entry, boolean loaded) {
		DictEntry e = (DictEntry) _dicts.get(entry.getKey());
		if (e != null) {
			if (e._entry == entry) {
				return true;
			}
			e.releaseDict();
			_dicts.remove(entry.getKey());
		} else {
			e = new DictEntry();
			e._entry = entry;
		}
		e.updateTimeTick();
		_dicts.put(entry.getKey(), e);
		if (loaded) {
			return entry.loadDiction(e._dict);
		}
		return true;
	}

	public boolean registeDictionary(String entryClass) {
		try {
			Class clazz = this.getClass().getClassLoader()
					.loadClass(entryClass);
			YKTDictionEntry entry = (YKTDictionEntry) clazz.newInstance();
			return registeDictionary(entry);
		} catch (Exception e) {
			logger.error("¼ÓÔØ×ÖµäÀàÊ§°Ü[" + entryClass + "]" + e.getMessage());
			e.printStackTrace();
			return false;
		}
	}

	public boolean unregisteDictionary(String dict) {
		DictEntry entry = (DictEntry) _dicts.get(dict);
		if (entry != null) {
			entry.releaseDict();
		}
		return (_dicts.remove(dict) != null);
	}

	public YKTDictionEntry getDictionEntry(String dict) throws YKTException {
		DictEntry entry = (DictEntry) _dicts.get(dict);
		if (null == entry) {
			return null;
		}
		long currTick = System.currentTimeMillis();
		if (currTick - entry._timeTick > _timeInterval) {
			entry._dict.clear();
			if (!entry._entry.loadDiction(entry._dict)) {
				throw new YKTException("¼ÓÔØ×Öµä[" + dict + "]Ê§°Ü");
			}
			entry.updateTimeTick();
		}
		return entry._entry;
	}

	private DictEntry getDictEntry(String dict) throws YKTException {
		DictEntry entry = (DictEntry) _dicts.get(dict);
		if (null == entry) {
			return null;
		}
		long currTick = System.currentTimeMillis();
		if (currTick - entry._timeTick > _timeInterval) {
			entry._dict.clear();
			if (!entry._entry.loadDiction(entry._dict)) {
				throw new YKTException("¼ÓÔØ×Öµä[" + dict + "]Ê§°Ü");
			}
			entry.updateTimeTick();
		}
		return entry;
	}

	public Object getDictionValue(String dict, String key) {
		DictEntry entry;
		try {
			entry = getDictEntry(dict);
			if (entry != null) {
				return entry._dict.get(key);
			}
			return null;
		} catch (YKTException e) {
			logger.error("¶ÁÈ¡×Öµäkey[" + key + "]" + e.getMessage());
			e.printStackTrace();
			return null;
		}
	}
}
