package com.kingstargroup.utils;

import junit.framework.TestCase;

public class MD5encodingTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.MD5encoding.byteArrayToHexString(byte[])'
	 */
	public void testByteArrayToHexString() {

	}

	/*
	 * Test method for 'com.kingstargroup.utils.MD5encoding.MD5Encode(String)'
	 */
	public void testMD5Encode() {
		
		//ecard@usst.edu.cn;  888888
		String psw = MD5encoding.MD5Encode("abc123");
		System.out.print(psw);
	}

}
