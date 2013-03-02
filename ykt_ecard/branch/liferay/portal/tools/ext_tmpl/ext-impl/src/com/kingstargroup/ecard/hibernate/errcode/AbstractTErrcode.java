package com.kingstargroup.ecard.hibernate.errcode;

/**
 * AbstractTErrcode entity provides the base persistence definition of the
 * TErrcode entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTErrcode implements java.io.Serializable {

	// Fields

	private Long errcode;
	private String errmsg;

	// Constructors

	/** default constructor */
	public AbstractTErrcode() {
	}

	/** minimal constructor */
	public AbstractTErrcode(Long errcode) {
		this.errcode = errcode;
	}

	/** full constructor */
	public AbstractTErrcode(Long errcode, String errmsg) {
		this.errcode = errcode;
		this.errmsg = errmsg;
	}

	// Property accessors

	public Long getErrcode() {
		return this.errcode;
	}

	public void setErrcode(Long errcode) {
		this.errcode = errcode;
	}

	public String getErrmsg() {
		return this.errmsg;
	}

	public void setErrmsg(String errmsg) {
		this.errmsg = errmsg;
	}

}