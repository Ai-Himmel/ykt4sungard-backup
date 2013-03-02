package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDeptLimit entity provides the base persistence definition of the
 * TDeptLimit entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDeptLimit implements java.io.Serializable {

	// Fields

	private TDeptLimitId id;

	// Constructors

	/** default constructor */
	public AbstractTDeptLimit() {
	}

	/** full constructor */
	public AbstractTDeptLimit(TDeptLimitId id) {
		this.id = id;
	}

	// Property accessors

	public TDeptLimitId getId() {
		return this.id;
	}

	public void setId(TDeptLimitId id) {
		this.id = id;
	}

}