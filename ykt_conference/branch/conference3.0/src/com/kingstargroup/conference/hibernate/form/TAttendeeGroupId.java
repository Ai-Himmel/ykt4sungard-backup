package com.kingstargroup.conference.hibernate.form;

/**
 * TAttendeeGroupId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TAttendeeGroupId extends AbstractTAttendeeGroupId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TAttendeeGroupId() {
	}

	/** full constructor */
	public TAttendeeGroupId(long custId, long groupId) {
		super(custId, groupId);
	}

}
