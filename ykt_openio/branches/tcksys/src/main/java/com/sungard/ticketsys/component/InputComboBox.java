package com.sungard.ticketsys.component;

import javax.swing.JComboBox;

public class InputComboBox extends JComboBox{

	private static final long serialVersionUID = 1L;

	//�Ƿ�����Ϊ�յı�־
	private boolean notNull = false;
	
	//��֤������
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
