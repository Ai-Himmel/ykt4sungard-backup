package org.king.monitor.domain;

/**
 * AbstractMapDeviceTableId entity provides the base persistence definition of
 * the MapDeviceTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapDeviceTableId implements java.io.Serializable {

	// Fields

	private String analysistime;
	private long deviceid;

	// Constructors

	/** default constructor */
	public AbstractMapDeviceTableId() {
	}

	/** full constructor */
	public AbstractMapDeviceTableId(String analysistime, long deviceid) {
		this.analysistime = analysistime;
		this.deviceid = deviceid;
	}

	// Property accessors

	public String getAnalysistime() {
		return this.analysistime;
	}

	public void setAnalysistime(String analysistime) {
		this.analysistime = analysistime;
	}

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMapDeviceTableId))
			return false;
		AbstractMapDeviceTableId castOther = (AbstractMapDeviceTableId) other;

		return ((this.getAnalysistime() == castOther.getAnalysistime()) || (this
				.getAnalysistime() != null
				&& castOther.getAnalysistime() != null && this
				.getAnalysistime().equals(castOther.getAnalysistime())))
				&& (this.getDeviceid() == castOther.getDeviceid());
	}

	public int hashCode() {
		int result = 17;

		result = 37
				* result
				+ (getAnalysistime() == null ? 0 : this.getAnalysistime()
						.hashCode());
		result = 37 * result + (int) this.getDeviceid();
		return result;
	}

}