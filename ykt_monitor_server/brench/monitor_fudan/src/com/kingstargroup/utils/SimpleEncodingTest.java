package com.kingstargroup.utils;

import junit.framework.TestCase;

public class SimpleEncodingTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.SimpleEncoding.encode(byte[], byte[])'
	 */
	public void testEncode() {
		try {
			for(int i=0;i<1;i++){
				SimpleEncoding.encode("888888".getBytes(),"kingstar".getBytes());
				SimpleEncoding.decode(SimpleEncoding.hex2byte("4D8480032938B6CE"),"kingstar".getBytes());
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
