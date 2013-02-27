package com.kingstargroup.utils;

import junit.framework.TestCase;

public class SimpleEncodingTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.SimpleEncoding.encode(byte[], byte[])'
	 */
	public void testEncode() {
		try {
			for(int i=0;i<1;i++){
				SimpleEncoding.debug=true;
				SimpleEncoding.encode("3sblqtw".getBytes(),"kingstar".getBytes());
				SimpleEncoding.decode(SimpleEncoding.hex2byte("32CE697D049D6221"),"kingstar".getBytes());
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
