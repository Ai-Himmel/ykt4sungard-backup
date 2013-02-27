package com.kingstargroup.utils;

import junit.framework.TestCase;

public class SimpleEncodingTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.SimpleEncoding.encode(byte[], byte[])'
	 */
	public void testEncode() {
		try {
			for(int i=0;i<100000;i++){
				SimpleEncoding.decode(SimpleEncoding.hex2byte("D3E95B1B3A5064B1"),"kingstar".getBytes());
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
