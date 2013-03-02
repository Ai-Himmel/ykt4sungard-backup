package com.kingstargroup.ecard.hibernate.shop;

/**
 * StoreLimitId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class StoreLimitId extends AbstractStoreLimitId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public StoreLimitId() {
	}

	/** full constructor */
	public StoreLimitId(String operCode, String storeCode) {
		super(operCode, storeCode);
	}

}
