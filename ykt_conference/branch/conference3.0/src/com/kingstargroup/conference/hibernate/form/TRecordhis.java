package com.kingstargroup.conference.hibernate.form;

/**
 * TRecordhis entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TRecordhis extends AbstractTRecordhis implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TRecordhis() {
	}

	/** full constructor */
	public TRecordhis(long confid, String physicalNo, String checktime,
			String attendSign, String dealornot) {
		super(confid, physicalNo, checktime, attendSign, dealornot);
	}

}
