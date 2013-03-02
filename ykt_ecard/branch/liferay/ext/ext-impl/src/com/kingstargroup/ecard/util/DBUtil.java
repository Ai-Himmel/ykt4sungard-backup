/**
 * 
 */
package com.kingstargroup.ecard.util;

import com.liferay.util.SystemProperties;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: DBUtil.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-10-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DBUtil {
	public static String bool2string(boolean b) {
		return b == true ? "1" : "0";
	}
	
	public static String getSchemaName() {
		return SystemProperties.get("hibernate.default_schema") + ".";
	}

}
