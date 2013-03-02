package com.kingstargroup.conference.hibernate.form;

/**
 * TDuty entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDuty extends AbstractTDuty implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDuty() {
	}

	/** minimal constructor */
	public TDuty(TDutyId id) {
		super(id);
	}

	/** full constructor */
	public TDuty(TDutyId id, String duty) {
		super(id, duty);
	}

}
