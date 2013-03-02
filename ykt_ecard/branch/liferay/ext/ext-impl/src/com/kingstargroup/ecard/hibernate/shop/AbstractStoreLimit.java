package com.kingstargroup.ecard.hibernate.shop;

/**
 * AbstractStoreLimit entity provides the base persistence definition of the
 * StoreLimit entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractStoreLimit implements java.io.Serializable {

	// Fields

	private StoreLimitId id;

	// Constructors

	/** default constructor */
	public AbstractStoreLimit() {
	}

	/** full constructor */
	public AbstractStoreLimit(StoreLimitId id) {
		this.id = id;
	}

	// Property accessors

	public StoreLimitId getId() {
		return this.id;
	}

	public void setId(StoreLimitId id) {
		this.id = id;
	}

}