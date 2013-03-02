package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDuty entity provides the base persistence definition of the TDuty
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDuty implements java.io.Serializable {

	// Fields

	private TDutyId id;
	private String duty;

	// Constructors

	/** default constructor */
	public AbstractTDuty() {
	}

	/** minimal constructor */
	public AbstractTDuty(TDutyId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTDuty(TDutyId id, String duty) {
		this.id = id;
		this.duty = duty;
	}

	// Property accessors

	public TDutyId getId() {
		return this.id;
	}

	public void setId(TDutyId id) {
		this.id = id;
	}

	public String getDuty() {
		return this.duty;
	}

	public void setDuty(String duty) {
		this.duty = duty;
	}

}