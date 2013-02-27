package com.kingstargroup.form;

/**
 * AbstractTCardver entity provides the base persistence definition of the
 * TCardver entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCardver implements java.io.Serializable {

	// Fields

	private String cardverno;
	private String accdate;
	private long termid;
	private long termseqno;
	private long cardno;
	private String cardphyid;
	private long cardvertype;
	private String adddelflag;
	private String status;

	// Constructors

	/** default constructor */
	public AbstractTCardver() {
	}

	/** minimal constructor */
	public AbstractTCardver(String cardverno) {
		this.cardverno = cardverno;
	}

	/** full constructor */
	public AbstractTCardver(String cardverno, String accdate, long termid,
			long termseqno, long cardno, String cardphyid, long cardvertype,
			String adddelflag, String status) {
		this.cardverno = cardverno;
		this.accdate = accdate;
		this.termid = termid;
		this.termseqno = termseqno;
		this.cardno = cardno;
		this.cardphyid = cardphyid;
		this.cardvertype = cardvertype;
		this.adddelflag = adddelflag;
		this.status = status;
	}

	// Property accessors

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public String getAccdate() {
		return this.accdate;
	}

	public void setAccdate(String accdate) {
		this.accdate = accdate;
	}

	public long getTermid() {
		return this.termid;
	}

	public void setTermid(long termid) {
		this.termid = termid;
	}

	public long getTermseqno() {
		return this.termseqno;
	}

	public void setTermseqno(long termseqno) {
		this.termseqno = termseqno;
	}

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
		this.cardno = cardno;
	}

	public String getCardphyid() {
		return this.cardphyid;
	}

	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}

	public long getCardvertype() {
		return this.cardvertype;
	}

	public void setCardvertype(long cardvertype) {
		this.cardvertype = cardvertype;
	}

	public String getAdddelflag() {
		return this.adddelflag;
	}

	public void setAdddelflag(String adddelflag) {
		this.adddelflag = adddelflag;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

}