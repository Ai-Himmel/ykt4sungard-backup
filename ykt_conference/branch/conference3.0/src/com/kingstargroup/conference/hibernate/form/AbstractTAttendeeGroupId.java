package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTAttendeeGroupId entity provides the base persistence definition of
 * the TAttendeeGroupId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTAttendeeGroupId implements java.io.Serializable {

	// Fields

	private long custId;
	private long groupId;

	// Constructors

	/** default constructor */
	public AbstractTAttendeeGroupId() {
	}

	/** full constructor */
	public AbstractTAttendeeGroupId(long custId, long groupId) {
		this.custId = custId;
		this.groupId = groupId;
	}

	// Property accessors

	public long getCustId() {
		return this.custId;
	}

	public void setCustId(long custId) {
		this.custId = custId;
	}

	public long getGroupId() {
		return this.groupId;
	}

	public void setGroupId(long groupId) {
		this.groupId = groupId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTAttendeeGroupId))
			return false;
		AbstractTAttendeeGroupId castOther = (AbstractTAttendeeGroupId) other;

		return (this.getCustId() == castOther.getCustId())
				&& (this.getGroupId() == castOther.getGroupId());
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getCustId();
		result = 37 * result + (int) this.getGroupId();
		return result;
	}

}