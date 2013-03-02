package com.kingstargroup.ecard.hibernate.custype;

/**
 * tCusttype entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TCusttype extends AbstractTCusttype implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCusttype() {
	}

	/** minimal constructor */
	public TCusttype(Long custtype) {
		super(custtype);
	}

	/** full constructor */
	public TCusttype(Long custtype, String custtypename, Long feetype,
			String useflag) {
		super(custtype, custtypename, feetype, useflag);
	}

}
