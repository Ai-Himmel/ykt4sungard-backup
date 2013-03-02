package org.king.dictionary;

import org.king.classmanage.service.StudentService;
import org.king.framework.dao.BaseDAO;

import junit.framework.TestCase;

public class YKTDictionaryTest extends TestCase {	
	/*
	 * Test method for 'org.king.dictionary.YKTDictionary.getDictionValue(String, String)'
	 */
	public void testGetDictionValue() {
		YKTDictionary test = YKTDictionary.getInstance();
		test.registeDictionary("org.king.dictionary.GenderDict");
		String gender = test.getDictionValue(DictionaryContants.GENDER,"1").toString();
		System.out.print(gender);
	}


}
