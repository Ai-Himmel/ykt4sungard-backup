/**
 * 
 */
package com.kingstargroup.ecard.util;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import com.liferay.counter.service.persistence.CounterUtil;
import com.liferay.portal.SystemException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: WebCountUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-18  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class WebCountUtil {
	public static synchronized String getCount(HttpServletRequest req) {
		try {
			HttpSession s = req.getSession();
			String value = (String) s.getAttribute(EcardConstants.WEB_COUNTER_NAME);
			if (value == null) {
				value = String.valueOf(CounterUtil.increment(EcardConstants.WEB_COUNTER_NAME));
				s.setAttribute(EcardConstants.WEB_COUNTER_NAME, value);
				return value;
			} else {
				return value;
			}
		} catch (SystemException se) {
			return "0";
		}
	}
}
