package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTAttendeeGroup entity provides the base persistence definition of the
 * TAttendeeGroup entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTAttendeeGroup implements java.io.Serializable {

	// Fields

	private TAttendeeGroupId id;
	private String comments;

	// Constructors

	/** default constructor */
	public AbstractTAttendeeGroup() {
	}

	/** minimal constructor */
	public AbstractTAttendeeGroup(TAttendeeGroupId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTAttendeeGroup(TAttendeeGroupId id, String comments) {
		this.id = id;
		this.comments = comments;
	}

	// Property accessors

	public TAttendeeGroupId getId() {
		return this.id;
	}

	public void setId(TAttendeeGroupId id) {
		this.id = id;
	}

	public String getComments() {
		return this.comments;
	}

	public void setComments(String comments) {
		this.comments = comments;
	}

}