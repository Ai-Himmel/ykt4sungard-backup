package com.sungard.ticketsys.component;

import javax.swing.JTextField;

/**
 * 输入框
 * @author Xuan.Zhou
 *
 */
public class InputTextField extends JTextField{
	
	private static final long serialVersionUID = 1L;

	//是否允许为空的标志
	private boolean notNull = false;
	
	//验证的类型
	private String validateType;

	public boolean isNotNull() {
		return notNull;
	}

	public void setNotNull(boolean notNull) {
		this.notNull = notNull;
	}

	public String getValidateType() {
		return validateType;
	}

	public void setValidateType(String validateType) {
		this.validateType = validateType;
	}
	
	
	

}
