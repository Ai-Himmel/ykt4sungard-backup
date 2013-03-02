package com.kingstargroup.ecard.hibernate.bras;

/**
 * AbstractTBrastransdtl entity provides the base persistence definition of the
 * TBrastransdtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTBrastransdtl implements java.io.Serializable {

	// Fields

	private String refno;
	private Long cardno;
	private String stuempno;
	private String custname;
	private String oppaccno;
	private String oppaccname;
	private String transdate;
	private String transtime;
	private Long transtype;
	private String summary;
	private Double transamt;
	private Long status;
	private String remark;
	private Long chkflag;

	// Constructors

	/** default constructor */
	public AbstractTBrastransdtl() {
	}

	/** minimal constructor */
	public AbstractTBrastransdtl(String refno) {
		this.refno = refno;
	}

	/** full constructor */
	public AbstractTBrastransdtl(String refno, Long cardno, String stuempno, String custname,
			String oppaccno, String oppaccname, String transdate,
			String transtime, Long transtype, String summary, Double transamt,
			Long status, String remark,Long chkflag) {
		this.refno = refno;
		this.cardno = cardno;
		this.stuempno = stuempno;
		this.custname = custname;
		this.oppaccno = oppaccno;
		this.oppaccname = oppaccname;
		this.transdate = transdate;
		this.transtime = transtime;
		this.transtype = transtype;
		this.summary = summary;
		this.transamt = transamt;
		this.status = status;
		this.remark = remark;
		this.chkflag = chkflag;
	}

	// Property accessors

	public String getRefno() {
		return this.refno;
	}

	public void setRefno(String refno) {
		this.refno = refno;
	}

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}


	public String getStuempno() {
		return stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public String getCustname() {
		return this.custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public String getOppaccno() {
		return this.oppaccno;
	}

	public void setOppaccno(String oppaccno) {
		this.oppaccno = oppaccno;
	}

	public String getOppaccname() {
		return this.oppaccname;
	}

	public void setOppaccname(String oppaccname) {
		this.oppaccname = oppaccname;
	}

	public String getTransdate() {
		return this.transdate;
	}

	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}

	public String getTranstime() {
		return this.transtime;
	}

	public void setTranstime(String transtime) {
		this.transtime = transtime;
	}

	public Long getTranstype() {
		return this.transtype;
	}

	public void setTranstype(Long transtype) {
		this.transtype = transtype;
	}

	public String getSummary() {
		return this.summary;
	}

	public void setSummary(String summary) {
		this.summary = summary;
	}

	public Double getTransamt() {
		return this.transamt;
	}

	public void setTransamt(Double transamt) {
		this.transamt = transamt;
	}

	public Long getStatus() {
		return this.status;
	}

	public void setStatus(Long status) {
		this.status = status;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	public Long getChkflag() {
		return chkflag;
	}

	public void setChkflag(Long chkflag) {
		this.chkflag = chkflag;
	}

}