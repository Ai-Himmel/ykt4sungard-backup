/**
 * 
 */
package com.kingstargroup.ecard.exceptions;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: CardAlreadyLostException.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-10-3  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class BccException extends PortalException {

	/**
	 * 
	 */
	public BccException() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param msg
	 */
	public BccException(String msg) {
		super(msg);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param msg
	 * @param cause
	 */
	public BccException(String msg, Throwable cause) {
		super(msg, cause);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param cause
	 */
	public BccException(Throwable cause) {
		super(cause);
		// TODO Auto-generated constructor stub
	}

}
