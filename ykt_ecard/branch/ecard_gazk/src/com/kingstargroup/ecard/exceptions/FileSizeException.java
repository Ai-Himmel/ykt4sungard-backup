package com.kingstargroup.ecard.exceptions;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: FileSizeException.java
 * Description: 
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-14  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class FileSizeException extends PortalException {

	public FileSizeException() {
		super();
	}

	public FileSizeException(String msg) {
		super(msg);
	}

	public FileSizeException(String msg, Throwable cause) {
		super(msg, cause);
	}

	public FileSizeException(Throwable cause) {
		super(cause);
	}

}