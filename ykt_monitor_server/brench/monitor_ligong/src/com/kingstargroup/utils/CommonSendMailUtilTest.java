package com.kingstargroup.utils;

import junit.framework.TestCase;

public class CommonSendMailUtilTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.utils.CommonSendMailUtil.sendMail(String, String, String, String)'
	 */
	public void testSendMail() {
		CommonSendMailUtil.sendMail("上海理工大学一卡通监控系统","测试中文的最大长度是多少","chenww@usst.edu.cn","陈巍巍（先生/女士）您好！");
		System.out.print("aaa");

	}

}
