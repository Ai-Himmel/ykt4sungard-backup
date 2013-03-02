package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTInformListId entity provides the base persistence definition of the
 * TInformListId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTInformListId implements java.io.Serializable {

	// Fields

	private long custId;
	private long conId;

	// Constructors

	/** default constructor */
	public AbstractTInformListId() {
	}

	/** full constructor */
	public AbstractTInformListId(long custId, long conId) {
		this.custId = custId;
		this.conId = conId;
	}

	// Property accessors

	public long getCustId() {
		return this.custId;
	}

	public void setCustId(long custId) {
		this.custId = custId;
	}

	public long getConId() {
		return this.conId;
	}

	public void setConId(long conId) {
		this.conId = conId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTInformListId))
			return false;
		AbstractTInformListId castOther = (AbstractTInformListId) other;

		return (this.getCustId() == castOther.getCustId())
				&& (this.getConId() == castOther.getConId());
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getCustId();
		result = 37 * result + (int) this.getConId();
		return result;
	}

}