package com.kingstargroup.fdykt.form;

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
	private Long custid;
	private Long cardno;
	private Long purseno;
	private Double daycostmaxamt;
	private Double cardmaxbal;
	private String stoppayflag;
	private String status;
	private Double ydaybal;
	private Double ydayavailbal;
	private Double ydayfrozebal;
	private Double balance;
	private Double availbal;
	private Double frozebal;
	private Double subsidybal;
	private Double foregift;
	private Long lastcardcnt;
	private Double lastcardbal;
	private Double daycostamt;
	private String lasttransdate;
	private String lastaccdate;
	private Long subsidyno;
	private String opendate;
	private String closedate;
	private Long acctype;

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
			String accpwd, Long custid, Long cardno, Long purseno,
			Double daycostmaxamt, Double cardmaxbal, String stoppayflag,
			String status, Double ydaybal, Double ydayavailbal,
			Double ydayfrozebal, Double balance, Double availbal,
			Double frozebal, Double subsidybal, Double foregift,
			Long lastcardcnt, Double lastcardbal, Double daycostamt,
			String lasttransdate, String lastaccdate, Long subsidyno,
			String opendate, String closedate, Long acctype) {
		this.accno = accno;
		this.accname = accname;
		this.subjno = subjno;
		this.accpwd = accpwd;
		this.custid = custid;
		this.cardno = cardno;
		this.purseno = purseno;
		this.daycostmaxamt = daycostmaxamt;
		this.cardmaxbal = cardmaxbal;
		this.stoppayflag = stoppayflag;
		this.status = status;
		this.ydaybal = ydaybal;
		this.ydayavailbal = ydayavailbal;
		this.ydayfrozebal = ydayfrozebal;
		this.balance = balance;
		this.availbal = availbal;
		this.frozebal = frozebal;
		this.subsidybal = subsidybal;
		this.foregift = foregift;
		this.lastcardcnt = lastcardcnt;
		this.lastcardbal = lastcardbal;
		this.daycostamt = daycostamt;
		this.lasttransdate = lasttransdate;
		this.lastaccdate = lastaccdate;
		this.subsidyno = subsidyno;
		this.opendate = opendate;
		this.closedate = closedate;
		this.acctype = acctype;
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

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}

	public Long getPurseno() {
		return this.purseno;
	}

	public void setPurseno(Long purseno) {
		this.purseno = purseno;
	}

	public Double getDaycostmaxamt() {
		return this.daycostmaxamt;
	}

	public void setDaycostmaxamt(Double daycostmaxamt) {
		this.daycostmaxamt = daycostmaxamt;
	}

	public Double getCardmaxbal() {
		return this.cardmaxbal;
	}

	public void setCardmaxbal(Double cardmaxbal) {
		this.cardmaxbal = cardmaxbal;
	}

	public String getStoppayflag() {
		return this.stoppayflag;
	}

	public void setStoppayflag(String stoppayflag) {
		this.stoppayflag = stoppayflag;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public Double getYdaybal() {
		return this.ydaybal;
	}

	public void setYdaybal(Double ydaybal) {
		this.ydaybal = ydaybal;
	}

	public Double getYdayavailbal() {
		return this.ydayavailbal;
	}

	public void setYdayavailbal(Double ydayavailbal) {
		this.ydayavailbal = ydayavailbal;
	}

	public Double getYdayfrozebal() {
		return this.ydayfrozebal;
	}

	public void setYdayfrozebal(Double ydayfrozebal) {
		this.ydayfrozebal = ydayfrozebal;
	}

	public Double getBalance() {
		return this.balance;
	}

	public void setBalance(Double balance) {
		this.balance = balance;
	}

	public Double getAvailbal() {
		return this.availbal;
	}

	public void setAvailbal(Double availbal) {
		this.availbal = availbal;
	}

	public Double getFrozebal() {
		return this.frozebal;
	}

	public void setFrozebal(Double frozebal) {
		this.frozebal = frozebal;
	}

	public Double getSubsidybal() {
		return this.subsidybal;
	}

	public void setSubsidybal(Double subsidybal) {
		this.subsidybal = subsidybal;
	}

	public Double getForegift() {
		return this.foregift;
	}

	public void setForegift(Double foregift) {
		this.foregift = foregift;
	}

	public Long getLastcardcnt() {
		return this.lastcardcnt;
	}

	public void setLastcardcnt(Long lastcardcnt) {
		this.lastcardcnt = lastcardcnt;
	}

	public Double getLastcardbal() {
		return this.lastcardbal;
	}

	public void setLastcardbal(Double lastcardbal) {
		this.lastcardbal = lastcardbal;
	}

	public Double getDaycostamt() {
		return this.daycostamt;
	}

	public void setDaycostamt(Double daycostamt) {
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

	public Long getSubsidyno() {
		return this.subsidyno;
	}

	public void setSubsidyno(Long subsidyno) {
		this.subsidyno = subsidyno;
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

	public Long getAcctype() {
		return this.acctype;
	}

	public void setAcctype(Long acctype) {
		this.acctype = acctype;
	}

}