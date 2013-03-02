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
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-15  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ContextUtil {

	public static String getCtxPath(HttpServletRequest req) {
		return req.getContextPath();
	}

}
