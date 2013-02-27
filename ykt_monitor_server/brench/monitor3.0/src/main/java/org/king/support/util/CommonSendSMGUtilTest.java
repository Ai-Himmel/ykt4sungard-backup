package org.king.support.util;

import junit.framework.TestCase;

public class CommonSendSMGUtilTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.CommonSendSMGUtil.sendSMG(String, String)'
	 */
	public void testSendSMG() {
		CommonSendSMGUtil.sendSMG("13916393067","监控系统测试短信平台,连通短信测试！");
		System.out.print("发送成功");
	}

}
