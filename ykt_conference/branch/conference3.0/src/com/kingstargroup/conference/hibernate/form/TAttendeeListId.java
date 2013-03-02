package com.kingstargroup.conference.hibernate.form;

/**
 * TAttendeeListId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TAttendeeListId extends AbstractTAttendeeListId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TAttendeeListId() {
	}

	/** full constructor */
	public TAttendeeListId(long conId, long custId) {
		super(conId, custId);
	}

}
