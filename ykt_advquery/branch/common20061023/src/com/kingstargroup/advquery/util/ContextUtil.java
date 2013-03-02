/**
 * 
 */
package com.kingstargroup.advquery.util;

import javax.servlet.http.HttpServletRequest;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ContextUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-11-15  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ContextUtil {

	public static String getCtxPath(HttpServletRequest req) {
		return req.getContextPath();
	}

}
