/**
 * 
 */
package com.kingstargroup.conference.common;

import javax.servlet.http.HttpServletRequest;

public class ContextUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ContextUtil<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-3-30  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getCtxPath(HttpServletRequest req) {
		return req.getContextPath();
	}

}
