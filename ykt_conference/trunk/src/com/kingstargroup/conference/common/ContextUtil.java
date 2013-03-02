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
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-3-30  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static String getCtxPath(HttpServletRequest req) {
		return req.getContextPath();
	}

}
