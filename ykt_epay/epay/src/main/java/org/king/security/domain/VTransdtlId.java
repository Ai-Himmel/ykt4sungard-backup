package org.king.security.domain;

import java.math.BigDecimal;

/**
 * VTransdtlId entity. @author MyEclipse Persistence Tools
 */

public class VTransdtlId implements java.io.Serializable {

	// Fields

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String accdate;
	private BigDecimal termid;
	private BigDecimal termseqno;
	

	// Constructors

	/** default constructor */
	public VTransdtlId() {
	}

	/** minimal constructor */
	public VTransdtlId(String accdate, BigDecimal termid, BigDecimal termseqno) {
		this.accdate = accdate;
		this.termid = termid;
		this.termseqno = termseqno;
	}

	public String getAccdate() {
		return accdate;
	}

	public void setAccdate(String accdate) {
		this.accdate = accdate;
	}

	public BigDecimal getTermid() {
		return termid;
	}

	public void setTermid(BigDecimal termid) {
		this.termid = termid;
	}

	public BigDecimal getTermseqno() {
		return termseqno;
	}

	public void setTermseqno(BigDecimal termseqno) {
		this.termseqno = termseqno;
	}

}