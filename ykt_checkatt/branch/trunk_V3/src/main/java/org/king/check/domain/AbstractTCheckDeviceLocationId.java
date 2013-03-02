package org.king.check.domain;


/**
 * AbstractTCheckDeviceLocationId entity provides the base persistence
 * definition of the TCheckDeviceLocationId entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractTCheckDeviceLocationId implements
		java.io.Serializable {

	// Fields

	private Integer deviceId;
	private String locationId;

	// Constructors

	/** default constructor */
	public AbstractTCheckDeviceLocationId() {
	}

	/** full constructor */
	public AbstractTCheckDeviceLocationId(Integer deviceId, String locationId) {
		this.deviceId = deviceId;
		this.locationId = locationId;
	}

	// Property accessors

	public Integer getDeviceId() {
		return this.deviceId;
	}

	public void setDeviceId(Integer deviceId) {
		this.deviceId = deviceId;
	}

	public String getLocationId() {
		return this.locationId;
	}

	public void setLocationId(String locationId) {
		this.locationId = locationId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTCheckDeviceLocationId))
			return false;
		AbstractTCheckDeviceLocationId castOther = (AbstractTCheckDeviceLocationId) other;

		return ((this.getDeviceId() == castOther.getDeviceId()) || (this
				.getDeviceId() != null
				&& castOther.getDeviceId() != null && this.getDeviceId()
				.equals(castOther.getDeviceId())))
				&& ((this.getLocationId() == castOther.getLocationId()) || (this
						.getLocationId() != null
						&& castOther.getLocationId() != null && this
						.getLocationId().equals(castOther.getLocationId())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getDeviceId() == null ? 0 : this.getDeviceId().hashCode());
		result = 37
				* result
				+ (getLocationId() == null ? 0 : this.getLocationId()
						.hashCode());
		return result;
	}

}