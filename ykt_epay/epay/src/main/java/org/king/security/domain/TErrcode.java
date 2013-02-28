package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TErrcode entity. @author MyEclipse Persistence Tools
 */

public class TErrcode implements java.io.Serializable {

	// Fields

	private BigDecimal errcode;
	private String errmsg;

	// Constructors

	/** default constructor */
	public TErrcode() {
	}

	/** full constructor */
	public TErrcode(String errmsg) {
		this.errmsg = errmsg;
	}

	// Property accessors

	public BigDecimal getErrcode() {
		return this.errcode;
	}

	public void setErrcode(BigDecimal errcode) {
		this.errcode = errcode;
	}

	public String getErrmsg() {
		return this.errmsg;
	}

	public void setErrmsg(String errmsg) {
		this.errmsg = errmsg;
	}

}