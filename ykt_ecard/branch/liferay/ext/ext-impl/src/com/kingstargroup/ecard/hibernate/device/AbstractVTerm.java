package com.kingstargroup.ecard.hibernate.device;

/**
 * AbstractTDevice entity provides the base persistence definition of the
 * TDevice entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVTerm implements java.io.Serializable {

	// Fields

	private Long termid;
	private String termname;


	// Constructors

	/** default constructor */
	public AbstractVTerm() {
	}

	/** minimal constructor */
	public AbstractVTerm(Long termid) {
		this.termid = termid;
	}

	/** full constructor */
	public AbstractVTerm(Long termid, String termname) {
		this.termid = termid;
		this.termname = termname;
	
	}

	public Long getTermid() {
		return termid;
	}

	public void setTermid(Long termid) {
		this.termid = termid;
	}

	public String getTermname() {
		return termname;
	}

	public void setTermname(String termname) {
		this.termname = termname;
	}



	// Property accessors

	

}