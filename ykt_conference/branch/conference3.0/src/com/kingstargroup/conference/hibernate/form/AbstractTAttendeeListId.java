package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTAttendeeListId entity provides the base persistence definition of
 * the TAttendeeListId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTAttendeeListId implements java.io.Serializable {

	// Fields

	private long conId;
	private long custId;

	// Constructors

	/** default constructor */
	public AbstractTAttendeeListId() {
	}

	/** full constructor */
	public AbstractTAttendeeListId(long conId, long custId) {
		this.conId = conId;
		this.custId = custId;
	}

	// Property accessors

	public long getConId() {
		return this.conId;
	}

	public void setConId(long conId) {
		this.conId = conId;
	}

	public long getCustId() {
		return this.custId;
	}

	public void setCustId(long custId) {
		this.custId = custId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTAttendeeListId))
			return false;
		AbstractTAttendeeListId castOther = (AbstractTAttendeeListId) other;

		return (this.getConId() == castOther.getConId())
				&& (this.getCustId() == castOther.getCustId());
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getConId();
		result = 37 * result + (int) this.getCustId();
		return result;
	}

}