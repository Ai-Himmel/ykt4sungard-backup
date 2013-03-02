package com.kingstargroup.fdykt.newform;

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
	private Double singlemaxamt;
	private Double daycostmaxamt;
	private Double cardmaxbal;
	private String status;
	private Double ydaybal;
	private Double balance;
	private Double availbal;
	private Double frozebal;
	private Double subsidybal;
	private Double foregift;
	private Long lastcardcnt;
	private Double lastcardbal;
	private Long subsidyno;
	private Double lastsubsidyamt;
	private Long lastsubsidyno;
	private Double daycostamt;
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
			String accpwd, Long custid, Long cardno, Long purseno,
			Double singlemaxamt, Double daycostmaxamt, Double cardmaxbal,
			String status, Double ydaybal, Double balance, Double availbal,
			Double frozebal, Double subsidybal, Double foregift,
			Long lastcardcnt, Double lastcardbal, Long subsidyno,
			Double lastsubsidyamt, Long lastsubsidyno, Double daycostamt,
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

	public Double getSinglemaxamt() {
		return this.singlemaxamt;
	}

	public void setSinglemaxamt(Double singlemaxamt) {
		this.singlemaxamt = singlemaxamt;
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

	public Long getSubsidyno() {
		return this.subsidyno;
	}

	public void setSubsidyno(Long subsidyno) {
		this.subsidyno = subsidyno;
	}

	public Double getLastsubsidyamt() {
		return this.lastsubsidyamt;
	}

	public void setLastsubsidyamt(Double lastsubsidyamt) {
		this.lastsubsidyamt = lastsubsidyamt;
	}

	public Long getLastsubsidyno() {
		return this.lastsubsidyno;
	}

	public void setLastsubsidyno(Long lastsubsidyno) {
		this.lastsubsidyno = lastsubsidyno;
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