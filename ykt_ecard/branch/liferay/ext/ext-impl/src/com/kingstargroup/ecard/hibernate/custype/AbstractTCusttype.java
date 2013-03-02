package com.kingstargroup.ecard.hibernate.custype;

/**
 * AbstracttCusttype entity provides the base persistence definition of the
 * tCusttype entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCusttype implements java.io.Serializable {

	// Fields

	private Long custtype;
	private String custtypename;
	private Long feetype;
	private String useflag;

	// Constructors

	/** default constructor */
	public AbstractTCusttype() {
	}

	/** minimal constructor */
	public AbstractTCusttype(Long custtype) {
		this.custtype = custtype;
	}

	/** full constructor */
	public AbstractTCusttype(Long custtype, String custtypename, Long feetype,
			String useflag) {
		this.custtype = custtype;
		this.custtypename = custtypename;
		this.feetype = feetype;
		this.useflag = useflag;
	}

	// Property accessors

	public Long getCusttype() {
		return this.custtype;
	}

	public void setCusttype(Long custtype) {
		this.custtype = custtype;
	}

	public String getCusttypename() {
		return this.custtypename;
	}

	public void setCusttypename(String custtypename) {
		this.custtypename = custtypename;
	}

	public Long getFeetype() {
		return this.feetype;
	}

	public void setFeetype(Long feetype) {
		this.feetype = feetype;
	}

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

}