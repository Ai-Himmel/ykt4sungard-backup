package com.kingstargroup.utils;

import junit.framework.TestCase;

public class StringUtilTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.StringUtil.split(String)'
	 */
	public void testSplitString() {
		String [] a = StringUtil.split("abc[bbc]","[");
//		int i=0;
		String[] b = StringUtil.split(a[1],"]");
		System.out.print(b[0]);
		
	}

	/*
	 * Test method for 'com.kingstargroup.utils.StringUtil.split(String, String)'
	 */
	public void testSplitStringString() {

	}

	/*
	 * Test method for 'com.kingstargroup.utils.StringUtil.wrap(String)'
	 */
	public void testWrapString() {

	}

	/*
	 * Test method for 'com.kingstargroup.utils.StringUtil.wrap(String, int, String)'
	 */
	public void testWrapStringIntString() {

	}

}
