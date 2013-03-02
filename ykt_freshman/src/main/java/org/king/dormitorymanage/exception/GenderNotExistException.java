/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DormitoryNotEnoughException.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-22     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.dormitorymanage.exception;

import org.king.framework.exception.BaseException;

public class GenderNotExistException extends BaseException {


	public GenderNotExistException() {
		super();
	}

	public GenderNotExistException(String arg0, Throwable arg1) {
		super(arg0, arg1);
	}

	public GenderNotExistException(String arg0) {
		super(arg0);
	}

	public GenderNotExistException(Throwable arg0) {
		super(arg0);
	}
	
	

}
