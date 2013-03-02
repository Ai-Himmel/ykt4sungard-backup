package com.kingstargroup.fdykt.newform;

/**
 * tCusttype entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class tCusttype extends AbstracttCusttype implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public tCusttype() {
	}

	/** minimal constructor */
	public tCusttype(Long custtype) {
		super(custtype);
	}

	/** full constructor */
	public tCusttype(Long custtype, String custtypename, Long feetype,
			String useflag) {
		super(custtype, custtypename, feetype, useflag);
	}

}
