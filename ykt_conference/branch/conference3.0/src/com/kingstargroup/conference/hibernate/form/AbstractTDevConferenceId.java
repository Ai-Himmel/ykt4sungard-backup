package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDevConferenceId entity provides the base persistence definition of
 * the TDevConferenceId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevConferenceId implements java.io.Serializable {

	// Fields

	private long conId;
	private long deviceId;

	// Constructors

	/** default constructor */
	public AbstractTDevConferenceId() {
	}

	/** full constructor */
	public AbstractTDevConferenceId(long conId, long deviceId) {
		this.conId = conId;
		this.deviceId = deviceId;
	}

	// Property accessors

	public long getConId() {
		return this.conId;
	}

	public void setConId(long conId) {
		this.conId = conId;
	}

	public long getDeviceId() {
		return this.deviceId;
	}

	public void setDeviceId(long deviceId) {
		this.deviceId = deviceId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTDevConferenceId))
			return false;
		AbstractTDevConferenceId castOther = (AbstractTDevConferenceId) other;

		return (this.getConId() == castOther.getConId())
				&& (this.getDeviceId() == castOther.getDeviceId());
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getConId();
		result = 37 * result + (int) this.getDeviceId();
		return result;
	}

}