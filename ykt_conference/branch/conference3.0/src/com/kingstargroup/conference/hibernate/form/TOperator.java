package com.kingstargroup.conference.hibernate.form;

/**
 * TOperator entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TOperator extends AbstractTOperator implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TOperator() {
	}

	/** minimal constructor */
	public TOperator(String operCode) {
		super(operCode);
	}

	/** full constructor */
	public TOperator(String operCode, String operName, String operPwd,
			String deptId, String loginTime, String loginIp, String status) {
		super(operCode, operName, operPwd, deptId, loginTime, loginIp, status);
	}

}
