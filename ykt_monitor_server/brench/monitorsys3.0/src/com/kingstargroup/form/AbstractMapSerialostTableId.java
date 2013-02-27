package com.kingstargroup.form;

/**
 * AbstractMapSerialostTableId entity provides the base persistence definition
 * of the MapSerialostTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSerialostTableId implements
		java.io.Serializable {

	// Fields

	private String analysistime;
	private long serialNo;
	private String deviceId;

	// Constructors

	/** default constructor */
	public AbstractMapSerialostTableId() {
	}

	/** full constructor */
	public AbstractMapSerialostTableId(String analysistime, long serialNo,
			String deviceId) {
		this.analysistime = analysistime;
		this.serialNo = serialNo;
		this.deviceId = deviceId;
	}

	// Property accessors

	public String getAnalysistime() {
		return this.analysistime;
	}

	public void setAnalysistime(String analysistime) {
		this.analysistime = analysistime;
	}

	public long getSerialNo() {
		return this.serialNo;
	}

	public void setSerialNo(long serialNo) {
		this.serialNo = serialNo;
	}

	public String getDeviceId() {
		return this.deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMapSerialostTableId))
			return false;
		AbstractMapSerialostTableId castOther = (AbstractMapSerialostTableId) other;

		return ((this.getAnalysistime() == castOther.getAnalysistime()) || (this
				.getAnalysistime() != null
				&& castOther.getAnalysistime() != null && this
				.getAnalysistime().equals(castOther.getAnalysistime())))
				&& (this.getSerialNo() == castOther.getSerialNo())
				&& ((this.getDeviceId() == castOther.getDeviceId()) || (this
						.getDeviceId() != null
						&& castOther.getDeviceId() != null && this
						.getDeviceId().equals(castOther.getDeviceId())));
	}

	public int hashCode() {
		int result = 17;

		result = 37
				* result
				+ (getAnalysistime() == null ? 0 : this.getAnalysistime()
						.hashCode());
		result = 37 * result + (int) this.getSerialNo();
		result = 37 * result
				+ (getDeviceId() == null ? 0 : this.getDeviceId().hashCode());
		return result;
	}

}