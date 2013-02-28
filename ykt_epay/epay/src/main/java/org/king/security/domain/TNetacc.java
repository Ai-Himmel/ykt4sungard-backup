package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TNetacc entity. @author MyEclipse Persistence Tools
 */

public class TNetacc implements java.io.Serializable {

	// Fields

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private String accno;
	private String accname;
	private String subjno;
	private String accpwd;
	private Long custid;
	private Long stoppayflag;
	private String status;
	private double ydaybal;
	private double balance;
	private double availbal;
	private double frozebal;
	private String lasttransdate;
	private String lastaccdate;
	private String opendate;
	private String closedate;
	private String paypwd;
	private Long failedcnt;
	private String lastlogintime;
	private String lastblocktime;
	private String lastunblocktime;

	// Constructors

	/** default constructor */
	public TNetacc() {
	}

	/** full constructor */
	public TNetacc(String accname, String subjno, String accpwd,
			Long custid, Long stoppayflag, String status,
			double ydaybal, double balance, double availbal, double frozebal,
			String lasttransdate, String lastaccdate, String opendate,
			String closedate, String paypwd, Long failedcnt,
			String lastlogintime, String lastblocktime, String lastunblocktime) {
		this.accname = accname;
		this.subjno = subjno;
		this.accpwd = accpwd;
		this.custid = custid;
		this.stoppayflag = stoppayflag;
		this.status = status;
		this.ydaybal = ydaybal;
		this.balance = balance;
		this.availbal = availbal;
		this.frozebal = frozebal;
		this.lasttransdate = lasttransdate;
		this.lastaccdate = lastaccdate;
		this.opendate = opendate;
		this.closedate = closedate;
		this.paypwd = paypwd;
		this.failedcnt = failedcnt;
		this.lastlogintime = lastlogintime;
		this.lastblocktime = lastblocktime;
		this.lastunblocktime = lastunblocktime;
	}

	// Property accessors

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public String getAccname() {
		return this.accname;
	}

	public void setAccname(String accname) {
		this.accname = accname;
	}

	public String getSubjno() {
		return this.subjno;
	}

	public void setSubjno(String subjno) {
		this.subjno = subjno;
	}

	public String getAccpwd() {
		return this.accpwd;
	}

	public void setAccpwd(String accpwd) {
		this.accpwd = accpwd;
	}

	public Long getCustid() {
		return this.custid;
	}

	public void setCustid(Long custid) {
		this.custid = custid;
	}

	public Long getStoppayflag() {
		return this.stoppayflag;
	}

	public void setStoppayflag(Long stoppayflag) {
		this.stoppayflag = stoppayflag;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public double getYdaybal() {
		return this.ydaybal;
	}

	public void setYdaybal(double ydaybal) {
		this.ydaybal = ydaybal;
	}

	public double getBalance() {
		return this.balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}

	public double getAvailbal() {
		return this.availbal;
	}

	public void setAvailbal(double availbal) {
		this.availbal = availbal;
	}

	public double getFrozebal() {
		return this.frozebal;
	}

	public void setFrozebal(double frozebal) {
		this.frozebal = frozebal;
	}

	public String getLasttransdate() {
		return this.lasttransdate;
	}

	public void setLasttransdate(String lasttransdate) {
		this.lasttransdate = lasttransdate;
	}

	public String getLastaccdate() {
		return this.lastaccdate;
	}

	public void setLastaccdate(String lastaccdate) {
		this.lastaccdate = lastaccdate;
	}

	public String getOpendate() {
		return this.opendate;
	}

	public void setOpendate(String opendate) {
		this.opendate = opendate;
	}

	public String getClosedate() {
		return this.closedate;
	}

	public void setClosedate(String closedate) {
		this.closedate = closedate;
	}

	public String getPaypwd() {
		return this.paypwd;
	}

	public void setPaypwd(String paypwd) {
		this.paypwd = paypwd;
	}

	public Long getFailedcnt() {
		return this.failedcnt;
	}

	public void setFailedcnt(Long failedcnt) {
		this.failedcnt = failedcnt;
	}

	public String getLastlogintime() {
		return this.lastlogintime;
	}

	public void setLastlogintime(String lastlogintime) {
		this.lastlogintime = lastlogintime;
	}

	public String getLastblocktime() {
		return this.lastblocktime;
	}

	public void setLastblocktime(String lastblocktime) {
		this.lastblocktime = lastblocktime;
	}

	public String getLastunblocktime() {
		return this.lastunblocktime;
	}

	public void setLastunblocktime(String lastunblocktime) {
		this.lastunblocktime = lastunblocktime;
	}

}