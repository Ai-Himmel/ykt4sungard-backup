package org.king.support.util;

import junit.framework.TestCase;

public class SimpleEncodingTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.SimpleEncoding.encode(byte[], byte[])'
	 */
	public void testEncode() {
		try {
			SimpleEncoding.debug=true;
			SimpleEncoding.encode("kingstar".getBytes(),"kingstar".getBytes());
			SimpleEncoding.decode(SimpleEncoding.hex2byte("609E95BC25EE54D57F1F9ADCB2769E53"),"kingstar".getBytes());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
