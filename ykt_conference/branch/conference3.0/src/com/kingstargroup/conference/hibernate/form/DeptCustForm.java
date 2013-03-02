package com.kingstargroup.conference.hibernate.form;

import java.util.ArrayList;
import java.util.List;

public class DeptCustForm {
	
	private String deptCode;
	private String deptName;
	private Integer custId;
	private String custName;
	private Integer plan;
	private Integer present;
	private String checkRate;
	private List confSignList = new ArrayList();
	private String stuempNo;
	
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
	public Integer getPlan() {
		return plan;
	}
	public void setPlan(Integer plan) {
		this.plan = plan;
	}
	public Integer getPresent() {
		return present;
	}
	public void setPresent(Integer present) {
		this.present = present;
	}
	public String getCheckRate() {
		return checkRate;
	}
	public void setCheckRate(String checkRate) {
		this.checkRate = checkRate;
	}
	public List getConfSignList() {
		return confSignList;
	}
	public void setConfSignList(List confSignList) {
		this.confSignList = confSignList;
	}
	public String getStuempNo() {
		return stuempNo;
	}
	public void setStuempNo(String stuempNo) {
		this.stuempNo = stuempNo;
	}
}
