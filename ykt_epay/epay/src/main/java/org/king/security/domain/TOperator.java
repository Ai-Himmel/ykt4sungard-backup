package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TOperator entity. @author MyEclipse Persistence Tools
 */

public class TOperator implements java.io.Serializable {

	// Fields

	private static final long serialVersionUID = 1L;
	
	private String opercode;
	private String opertype;
	private BigDecimal branchno;
	private BigDecimal cardno;
	private String opername;
	private String tel;
	private String mobile;
	private String email;
	private String addr;
	private String zipcode;
	private String operpwd;
	private String status;
	private String lasttransdate;
	private String menuset;
	private String funcset;
	private String sitelimit;
	private String loginflag;
	private BigDecimal loginsiteno;
	private String logintime;
	private String logouttime;
	private BigDecimal failnumber;
	private String opendate;
	private String closedate;
	private boolean rightflag;

	// Constructors

	/** default constructor */
	public TOperator() {
	}

	/** minimal constructor */
	public TOperator(String opercode, String opername) {
		this.opercode = opercode;
		this.opername = opername;
	}

	/** full constructor */
	public TOperator(String opercode, String opertype, BigDecimal branchno,
			BigDecimal cardno, String opername, String tel, String mobile,
			String email, String addr, String zipcode, String operpwd,
			String status, String lasttransdate, String menuset,
			String funcset, String sitelimit, String loginflag,
			BigDecimal loginsiteno, String logintime, String logouttime,
			BigDecimal failnumber, String opendate, String closedate,
			boolean rightflag) {
		this.opercode = opercode;
		this.opertype = opertype;
		this.branchno = branchno;
		this.cardno = cardno;
		this.opername = opername;
		this.tel = tel;
		this.mobile = mobile;
		this.email = email;
		this.addr = addr;
		this.zipcode = zipcode;
		this.operpwd = operpwd;
		this.status = status;
		this.lasttransdate = lasttransdate;
		this.menuset = menuset;
		this.funcset = funcset;
		this.sitelimit = sitelimit;
		this.loginflag = loginflag;
		this.loginsiteno = loginsiteno;
		this.logintime = logintime;
		this.logouttime = logouttime;
		this.failnumber = failnumber;
		this.opendate = opendate;
		this.closedate = closedate;
		this.rightflag = rightflag;
	}

	public String getOpercode() {
		return opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

	public String getOpertype() {
		return opertype;
	}

	public void setOpertype(String opertype) {
		this.opertype = opertype;
	}

	public BigDecimal getBranchno() {
		return branchno;
	}

	public void setBranchno(BigDecimal branchno) {
		this.branchno = branchno;
	}

	public BigDecimal getCardno() {
		return cardno;
	}

	public void setCardno(BigDecimal cardno) {
		this.cardno = cardno;
	}

	public String getOpername() {
		return opername;
	}

	public void setOpername(String opername) {
		this.opername = opername;
	}

	public String getTel() {
		return tel;
	}

	public void setTel(String tel) {
		this.tel = tel;
	}

	public String getMobile() {
		return mobile;
	}

	public void setMobile(String mobile) {
		this.mobile = mobile;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getAddr() {
		return addr;
	}

	public void setAddr(String addr) {
		this.addr = addr;
	}

	public String getZipcode() {
		return zipcode;
	}

	public void setZipcode(String zipcode) {
		this.zipcode = zipcode;
	}

	public String getOperpwd() {
		return operpwd;
	}

	public void setOperpwd(String operpwd) {
		this.operpwd = operpwd;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getLasttransdate() {
		return lasttransdate;
	}

	public void setLasttransdate(String lasttransdate) {
		this.lasttransdate = lasttransdate;
	}

	public String getMenuset() {
		return menuset;
	}

	public void setMenuset(String menuset) {
		this.menuset = menuset;
	}

	public String getFuncset() {
		return funcset;
	}

	public void setFuncset(String funcset) {
		this.funcset = funcset;
	}

	public String getSitelimit() {
		return sitelimit;
	}

	public void setSitelimit(String sitelimit) {
		this.sitelimit = sitelimit;
	}

	public String getLoginflag() {
		return loginflag;
	}

	public void setLoginflag(String loginflag) {
		this.loginflag = loginflag;
	}

	public BigDecimal getLoginsiteno() {
		return loginsiteno;
	}

	public void setLoginsiteno(BigDecimal loginsiteno) {
		this.loginsiteno = loginsiteno;
	}

	public String getLogintime() {
		return logintime;
	}

	public void setLogintime(String logintime) {
		this.logintime = logintime;
	}

	public String getLogouttime() {
		return logouttime;
	}

	public void setLogouttime(String logouttime) {
		this.logouttime = logouttime;
	}

	public BigDecimal getFailnumber() {
		return failnumber;
	}

	public void setFailnumber(BigDecimal failnumber) {
		this.failnumber = failnumber;
	}

	public String getOpendate() {
		return opendate;
	}

	public void setOpendate(String opendate) {
		this.opendate = opendate;
	}

	public String getClosedate() {
		return closedate;
	}

	public void setClosedate(String closedate) {
		this.closedate = closedate;
	}

	public boolean isRightflag() {
		return rightflag;
	}

	public void setRightflag(boolean rightflag) {
		this.rightflag = rightflag;
	}


}