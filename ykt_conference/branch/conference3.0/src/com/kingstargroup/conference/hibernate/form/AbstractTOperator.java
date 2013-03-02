package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTOperator entity provides the base persistence definition of the
 * TOperator entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTOperator implements java.io.Serializable {

	// Fields

	private String operCode;
	private String operName;
	private String operPwd;
	private String deptId;
	private String loginTime;
	private String loginIp;
	private String status;

	// Constructors

	/** default constructor */
	public AbstractTOperator() {
	}

	/** minimal constructor */
	public AbstractTOperator(String operCode) {
		this.operCode = operCode;
	}

	/** full constructor */
	public AbstractTOperator(String operCode, String operName, String operPwd,
			String deptId, String loginTime, String loginIp, String status) {
		this.operCode = operCode;
		this.operName = operName;
		this.operPwd = operPwd;
		this.deptId = deptId;
		this.loginTime = loginTime;
		this.loginIp = loginIp;
		this.status = status;
	}

	// Property accessors

	public String getOperCode() {
		return this.operCode;
	}

	public void setOperCode(String operCode) {
		this.operCode = operCode;
	}

	public String getOperName() {
		return this.operName;
	}

	public void setOperName(String operName) {
		this.operName = operName;
	}

	public String getOperPwd() {
		return this.operPwd;
	}

	public void setOperPwd(String operPwd) {
		this.operPwd = operPwd;
	}

	public String getDeptId() {
		return this.deptId;
	}

	public void setDeptId(String deptId) {
		this.deptId = deptId;
	}

	public String getLoginTime() {
		return this.loginTime;
	}

	public void setLoginTime(String loginTime) {
		this.loginTime = loginTime;
	}

	public String getLoginIp() {
		return this.loginIp;
	}

	public void setLoginIp(String loginIp) {
		this.loginIp = loginIp;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

}