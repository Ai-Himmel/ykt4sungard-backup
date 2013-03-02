package com.kingstargroup.ecard.hibernate.bank;

/**
 * TbankcardId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TbankcardId extends AbstractTbankcardId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TbankcardId() {
	}

	/** full constructor */
	public TbankcardId(Long custid, String bankcode) {
		super(custid, bankcode);
	}

}
