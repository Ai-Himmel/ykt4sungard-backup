package org.king.dictionary;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletContext;

import org.apache.log4j.Logger;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.service.StudentService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ApplicationObjectSupport;
import org.springframework.web.context.support.ServletContextAwareProcessor;

public class GenderDict implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GenderDict.class);
	
	private StudentService studentService = null;
	
	

	public String getKey() {
		return DictionaryContants.GENDER;
	}

	public boolean loadDiction(Map dict) {

		try {
			_serial = dict;
//			List list = baseDAO
//					.findEntity("from Dictionary a where a.id.dictNo=1");
			
			List list = studentService.getDiction("1");
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
