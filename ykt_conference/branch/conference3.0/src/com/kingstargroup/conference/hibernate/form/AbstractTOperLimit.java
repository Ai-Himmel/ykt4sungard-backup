package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTOperLimit entity provides the base persistence definition of the
 * TOperLimit entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTOperLimit implements java.io.Serializable {

	// Fields

	private TOperLimitId id;

	// Constructors

	/** default constructor */
	public AbstractTOperLimit() {
	}

	/** full constructor */
	public AbstractTOperLimit(TOperLimitId id) {
		this.id = id;
	}

	// Property accessors

	public TOperLimitId getId() {
		return this.id;
	}

	public void setId(TOperLimitId id) {
		this.id = id;
	}

}