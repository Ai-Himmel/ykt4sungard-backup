package com.kingstargroup.form;

/**
 * AbstractMapServiceExceptionId entity provides the base persistence definition
 * of the MapServiceExceptionId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapServiceExceptionId implements
		java.io.Serializable {

	// Fields

	private String analysistime;
	private long serviceId;

	// Constructors

	/** default constructor */
	public AbstractMapServiceExceptionId() {
	}

	/** full constructor */
	public AbstractMapServiceExceptionId(String analysistime, long serviceId) {
		this.analysistime = analysistime;
		this.serviceId = serviceId;
	}

	// Property accessors

	public String getAnalysistime() {
		return this.analysistime;
	}

	public void setAnalysistime(String analysistime) {
		this.analysistime = analysistime;
	}

	public long getServiceId() {
		return this.serviceId;
	}

	public void setServiceId(long serviceId) {
		this.serviceId = serviceId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMapServiceExceptionId))
			return false;
		AbstractMapServiceExceptionId castOther = (AbstractMapServiceExceptionId) other;

		return ((this.getAnalysistime() == castOther.getAnalysistime()) || (this
				.getAnalysistime() != null
				&& castOther.getAnalysistime() != null && this
				.getAnalysistime().equals(castOther.getAnalysistime())))
				&& (this.getServiceId() == castOther.getServiceId());
	}

	public int hashCode() {
		int result = 17;

		result = 37
				* result
				+ (getAnalysistime() == null ? 0 : this.getAnalysistime()
						.hashCode());
		result = 37 * result + (int) this.getServiceId();
		return result;
	}

}