package com.kingstargroup.fdykt.newform;

/**
 * AbstractTCardtype entity provides the base persistence definition of the
 * TCardtype entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCardtype implements java.io.Serializable {

	// Fields

	private Long cardtype;
	private String cardtypename;
	private String anonymflag;
	private Long feetype;
	private Double cardcostfee;
	private String reuseable;
	private String renewable;
	private String multipurse;
	private String fixdayflag;
	private Long fixdaycnt;
	private String useflag;
	private String purpose;

	// Constructors

	/** default constructor */
	public AbstractTCardtype() {
	}

	/** minimal constructor */
	public AbstractTCardtype(Long cardtype) {
		this.cardtype = cardtype;
	}

	/** full constructor */
	public AbstractTCardtype(Long cardtype, String cardtypename,
			String anonymflag, Long feetype, Double cardcostfee,
			String reuseable, String renewable, String multipurse,
			String fixdayflag, Long fixdaycnt, String useflag, String purpose) {
		this.cardtype = cardtype;
		this.cardtypename = cardtypename;
		this.anonymflag = anonymflag;
		this.feetype = feetype;
		this.cardcostfee = cardcostfee;
		this.reuseable = reuseable;
		this.renewable = renewable;
		this.multipurse = multipurse;
		this.fixdayflag = fixdayflag;
		this.fixdaycnt = fixdaycnt;
		this.useflag = useflag;
		this.purpose = purpose;
	}

	// Property accessors

	public Long getCardtype() {
		return this.cardtype;
	}

	public void setCardtype(Long cardtype) {
		this.cardtype = cardtype;
	}

	public String getCardtypename() {
		return this.cardtypename;
	}

	public void setCardtypename(String cardtypename) {
		this.cardtypename = cardtypename;
	}

	public String getAnonymflag() {
		return this.anonymflag;
	}

	public void setAnonymflag(String anonymflag) {
		this.anonymflag = anonymflag;
	}

	public Long getFeetype() {
		return this.feetype;
	}

	public void setFeetype(Long feetype) {
		this.feetype = feetype;
	}

	public Double getCardcostfee() {
		return this.cardcostfee;
	}

	public void setCardcostfee(Double cardcostfee) {
		this.cardcostfee = cardcostfee;
	}

	public String getReuseable() {
		return this.reuseable;
	}

	public void setReuseable(String reuseable) {
		this.reuseable = reuseable;
	}

	public String getRenewable() {
		return this.renewable;
	}

	public void setRenewable(String renewable) {
		this.renewable = renewable;
	}

	public String getMultipurse() {
		return this.multipurse;
	}

	public void setMultipurse(String multipurse) {
		this.multipurse = multipurse;
	}

	public String getFixdayflag() {
		return this.fixdayflag;
	}

	public void setFixdayflag(String fixdayflag) {
		this.fixdayflag = fixdayflag;
	}

	public Long getFixdaycnt() {
		return this.fixdaycnt;
	}

	public void setFixdaycnt(Long fixdaycnt) {
		this.fixdaycnt = fixdaycnt;
	}

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

	public String getPurpose() {
		return this.purpose;
	}

	public void setPurpose(String purpose) {
		this.purpose = purpose;
	}

}