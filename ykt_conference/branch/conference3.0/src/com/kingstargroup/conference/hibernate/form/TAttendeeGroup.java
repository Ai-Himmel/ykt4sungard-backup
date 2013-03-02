package com.kingstargroup.conference.hibernate.form;

/**
 * TAttendeeGroup entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TAttendeeGroup extends AbstractTAttendeeGroup implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TAttendeeGroup() {
	}

	/** minimal constructor */
	public TAttendeeGroup(TAttendeeGroupId id) {
		super(id);
	}

	/** full constructor */
	public TAttendeeGroup(TAttendeeGroupId id, String comments) {
		super(id, comments);
	}

}
