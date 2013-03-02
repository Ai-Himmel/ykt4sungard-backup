package com.kingstargroup.conference.hibernate.form;

public class DeptCustForm {
	
	private String deptCode;
	private String deptName;
	private Integer custId;
	private String custName;
	
	
	public DeptCustForm() {
		super();
	}
	public DeptCustForm(String deptCode, String deptName, Integer custId, String custName) {
		super();
		this.deptCode = deptCode;
		this.deptName = deptName;
		this.custId = custId;
		this.custName = custName;
	}
	public Integer getCustId() {
		return custId;
	}
	public void setCustId(Integer custId) {
		this.custId = custId;
	}
	public String getCustName() {
		return custName;
	}
	public void setCustName(String custName) {
		this.custName = custName;
	}
	public String getDeptCode() {
		return deptCode;
	}
	public void setDeptCode(String deptCode) {
		this.deptCode = deptCode;
	}
	public String getDeptName() {
		return deptName;
	}
	public void setDeptName(String deptName) {
		this.deptName = deptName;
	}
	
	

}
