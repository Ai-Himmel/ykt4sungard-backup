package com.kingstargroup.form;

/**
 * AbstractTAccount entity provides the base persistence definition of the
 * TAccount entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTAccount implements java.io.Serializable {

	// Fields

	private String accno;
	private String accname;
	private String subjno;
	private String accpwd;
	private long custid;
	private long cardno;
	private long purseno;
	private double singlemaxamt;
	private double daycostmaxamt;
	private double cardmaxbal;
	private String status;
	private double ydaybal;
	private double balance;
	private double availbal;
	private double frozebal;
	private double subsidybal;
	private double foregift;
	private long lastcardcnt;
	private double lastcardbal;
	private long subsidyno;
	private double lastsubsidyamt;
	private long lastsubsidyno;
	private double daycostamt;
	private String lasttransdate;
	private String lastaccdate;
	private String opendate;
	private String closedate;

	// Constructors

	/** default constructor */
	public AbstractTAccount() {
	}

	/** minimal constructor */
	public AbstractTAccount(String accno) {
		this.accno = accno;
	}

	/** full constructor */
	public AbstractTAccount(String accno, String accname, String subjno,
			String accpwd, long custid, long cardno, long purseno,
			double singlemaxamt, double daycostmaxamt, double cardmaxbal,
			String status, double ydaybal, double balance, double availbal,
			double frozebal, double subsidybal, double foregift,
			long lastcardcnt, double lastcardbal, long subsidyno,
			double lastsubsidyamt, long lastsubsidyno, double daycostamt,
			String lasttransdate, String lastaccdate, String opendate,
			String closedate) {
		this.accno = accno;
		this.accname = accname;
		this.subjno = subjno;
		this.accpwd = accpwd;
		this.custid = custid;
		this.cardno = cardno;
		this.purseno = purseno;
		this.singlemaxamt = singlemaxamt;
		this.daycostmaxamt = daycostmaxamt;
		this.cardmaxbal = cardmaxbal;
		this.status = status;
		this.ydaybal = ydaybal;
		this.balance = balance;
		this.availbal = availbal;
		this.frozebal = frozebal;
		this.subsidybal = subsidybal;
		this.foregift = foregift;
		this.lastcardcnt = lastcardcnt;
		this.lastcardbal = lastcardbal;
		this.subsidyno = subsidyno;
		this.lastsubsidyamt = lastsubsidyamt;
		this.lastsubsidyno = lastsubsidyno;
		this.daycostamt = daycostamt;
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

	public long getCustid() {
		return this.custid;
	}

	public void setCustid(long custid) {
		this.custid = custid;
	}

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
		this.cardno = cardno;
	}

	public long getPurseno() {
		return this.purseno;
	}

	public void setPurseno(long purseno) {
		this.purseno = purseno;
	}

	public double getSinglemaxamt() {
		return this.singlemaxamt;
	}

	public void setSinglemaxamt(double singlemaxamt) {
		this.singlemaxamt = singlemaxamt;
	}

	public double getDaycostmaxamt() {
		return this.daycostmaxamt;
	}

	public void setDaycostmaxamt(double daycostmaxamt) {
		this.daycostmaxamt = daycostmaxamt;
	}

	public double getCardmaxbal() {
		return this.cardmaxbal;
	}

	public void setCardmaxbal(double cardmaxbal) {
		this.cardmaxbal = cardmaxbal;
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

	public double getSubsidybal() {
		return this.subsidybal;
	}

	public void setSubsidybal(double subsidybal) {
		this.subsidybal = subsidybal;
	}

	public double getForegift() {
		return this.foregift;
	}

	public void setForegift(double foregift) {
		this.foregift = foregift;
	}

	public long getLastcardcnt() {
		return this.lastcardcnt;
	}

	public void setLastcardcnt(long lastcardcnt) {
		this.lastcardcnt = lastcardcnt;
	}

	public double getLastcardbal() {
		return this.lastcardbal;
	}

	public void setLastcardbal(double lastcardbal) {
		this.lastcardbal = lastcardbal;
	}

	public long getSubsidyno() {
		return this.subsidyno;
	}

	public void setSubsidyno(long subsidyno) {
		this.subsidyno = subsidyno;
	}

	public double getLastsubsidyamt() {
		return this.lastsubsidyamt;
	}

	public void setLastsubsidyamt(double lastsubsidyamt) {
		this.lastsubsidyamt = lastsubsidyamt;
	}

	public long getLastsubsidyno() {
		return this.lastsubsidyno;
	}

	public void setLastsubsidyno(long lastsubsidyno) {
		this.lastsubsidyno = lastsubsidyno;
	}

	public double getDaycostamt() {
		return this.daycostamt;
	}

	public void setDaycostamt(double daycostamt) {
		this.daycostamt = daycostamt;
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