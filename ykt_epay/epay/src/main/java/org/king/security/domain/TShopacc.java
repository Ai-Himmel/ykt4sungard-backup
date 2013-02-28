package org.king.security.domain;


/**
 * TShopacc entity. @author MyEclipse Persistence Tools
 */

public class TShopacc  implements java.io.Serializable {

	// Fields

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String accno;
	private Long shopid;
	private String accname;
	private String subjno;
	private String accpwd;
	private String status;
	private double ydaybal;
	private double balance;
	private double availbal;
	private double frozebal;
	private String lasttransdate;
	private String lastaccdate;
	private String opendate;
	private String closedate;

	// Constructors

	/** default constructor */
	public TShopacc() {
	}

	/** minimal constructor */
	public TShopacc(String accno, Long shopid) {
		this.accno = accno;
		this.shopid = shopid;
	}

	/** full constructor */
	public TShopacc(String accno, Long shopid, String accname,
			String subjno, String accpwd, String status, double ydaybal,
			double balance, double availbal, double frozebal,
			String lasttransdate, String lastaccdate, String opendate,
			String closedate) {
		this.accno = accno;
		this.shopid = shopid;
		this.accname = accname;
		this.subjno = subjno;
		this.accpwd = accpwd;
		this.status = status;
		this.ydaybal = ydaybal;
		this.balance = balance;
		this.availbal = availbal;
		this.frozebal = frozebal;
		this.lasttransdate = lasttransdate;
		this.lastaccdate = lastaccdate;
		this.opendate = opendate;
		this.closedate = closedate;
	}

	// Property accessors

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public Long getShopid() {
		return this.shopid;
	}

	public void setShopid(Long shopid) {
		this.shopid = shopid;
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

}