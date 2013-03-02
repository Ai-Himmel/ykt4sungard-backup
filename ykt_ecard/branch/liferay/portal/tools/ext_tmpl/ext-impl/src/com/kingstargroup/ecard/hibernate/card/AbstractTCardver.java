package com.kingstargroup.ecard.hibernate.card;

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
	private Long termid;
	private Long termseqno;
	private Long cardno;
	private String cardphyid;
	private String stuempno;
	private Long cardvertype;
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
	public AbstractTCardver(String cardverno, String accdate, Long termid,
			Long termseqno, Long cardno, String cardphyid, String stuempno,
			Long cardvertype, String adddelflag, String status) {
		this.cardverno = cardverno;
		this.accdate = accdate;
		this.termid = termid;
		this.termseqno = termseqno;
		this.cardno = cardno;
		this.cardphyid = cardphyid;
		this.stuempno = stuempno;
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

	public Long getTermid() {
		return this.termid;
	}

	public void setTermid(Long termid) {
		this.termid = termid;
	}

	public Long getTermseqno() {
		return this.termseqno;
	}

	public void setTermseqno(Long termseqno) {
		this.termseqno = termseqno;
	}

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}

	public String getCardphyid() {
		return this.cardphyid;
	}

	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}

	public String getStuempno() {
		return this.stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public Long getCardvertype() {
		return this.cardvertype;
	}

	public void setCardvertype(Long cardvertype) {
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