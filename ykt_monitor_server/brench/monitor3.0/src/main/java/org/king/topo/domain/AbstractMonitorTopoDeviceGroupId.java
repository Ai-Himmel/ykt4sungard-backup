package org.king.topo.domain;

/**
 * AbstractMonitorTopoDeviceGroupId entity provides the base persistence
 * definition of the MonitorTopoDeviceGroupId entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorTopoDeviceGroupId extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer deviceid;
	private Integer devicegroupid;

	// Constructors

	/** default constructor */
	public AbstractMonitorTopoDeviceGroupId() {
	}

	/** full constructor */
	public AbstractMonitorTopoDeviceGroupId(Integer deviceid,
			Integer devicegroupid) {
		this.deviceid = deviceid;
		this.devicegroupid = devicegroupid;
	}

	// Property accessors

	public Integer getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Integer deviceid) {
		this.deviceid = deviceid;
	}

	public Integer getDevicegroupid() {
		return this.devicegroupid;
	}

	public void setDevicegroupid(Integer devicegroupid) {
		this.devicegroupid = devicegroupid;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMonitorTopoDeviceGroupId))
			return false;
		AbstractMonitorTopoDeviceGroupId castOther = (AbstractMonitorTopoDeviceGroupId) other;

		return ((this.getDeviceid() == castOther.getDeviceid()) || (this
				.getDeviceid() != null
				&& castOther.getDeviceid() != null && this.getDeviceid()
				.equals(castOther.getDeviceid())))
				&& ((this.getDevicegroupid() == castOther.getDevicegroupid()) || (this
						.getDevicegroupid() != null
						&& castOther.getDevicegroupid() != null && this
						.getDevicegroupid()
						.equals(castOther.getDevicegroupid())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getDeviceid() == null ? 0 : this.getDeviceid().hashCode());
		result = 37
				* result
				+ (getDevicegroupid() == null ? 0 : this.getDevicegroupid()
						.hashCode());
		return result;
	}

	@Override
	public String toString() {
		return "AbstractMonitorTopoDeviceGroupId [devicegroupid="
				+ devicegroupid + ", deviceid=" + deviceid + "]";
	}
}