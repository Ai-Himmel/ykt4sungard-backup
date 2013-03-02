/**
 * 
 */
package com.kingstargroup.ecard.exceptions;

import com.liferay.portal.PortalException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ValidAuthCodeException.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-30  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ValidAuthCodeException extends PortalException {

	/**
	 * 
	 */
	public ValidAuthCodeException() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param msg
	 */
	public ValidAuthCodeException(String msg) {
		super(msg);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param msg
	 * @param cause
	 */
	public ValidAuthCodeException(String msg, Throwable cause) {
		super(msg, cause);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param cause
	 */
	public ValidAuthCodeException(Throwable cause) {
		super(cause);
		// TODO Auto-generated constructor stub
	}

}
