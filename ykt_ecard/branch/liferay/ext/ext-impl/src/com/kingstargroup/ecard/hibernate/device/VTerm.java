package com.kingstargroup.ecard.hibernate.device;

/**
 * TDevice entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class VTerm extends AbstractVTerm implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public VTerm() {
	}

	/** minimal constructor */
	public VTerm(Long termid) {
		super(termid);
	}

	/** full constructor */
	public VTerm(Long termid, String termname) {
		super(termid, termname);
	}

}
