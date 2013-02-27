package com.kingstargroup.utils;

import java.util.ArrayList;
import java.util.List;

import junit.framework.TestCase;

public class CheckLostSeriUitlTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.CheckLostSeriUitl.SequenceCheckLostSerial(List)'
	 */
	public void testSequenceCheckLostSerial() {
		List list = new ArrayList();
		list.add("111");
		list.add("113");
		List list1 = CheckLostSeriUitl.sequenceCheckLostSerial(list);
		for(int i=0; i<list1.size(); i++){
			System.out.println(list1.get(i));
		}
		
	}

}
