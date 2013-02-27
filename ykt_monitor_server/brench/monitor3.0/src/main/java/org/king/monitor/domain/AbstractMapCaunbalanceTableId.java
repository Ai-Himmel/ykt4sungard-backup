package org.king.monitor.domain;

/**
 * AbstractMapCaunbalanceTableId entity provides the base persistence definition
 * of the MapCaunbalanceTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapCaunbalanceTableId implements
		java.io.Serializable {

	// Fields

	private String accno;
	private String analysistime;

	// Constructors

	/** default constructor */
	public AbstractMapCaunbalanceTableId() {
	}

	/** full constructor */
	public AbstractMapCaunbalanceTableId(String accno, String analysistime) {
		this.accno = accno;
		this.analysistime = analysistime;
	}

	// Property accessors

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public String getAnalysistime() {
		return this.analysistime;
	}

	public void setAnalysistime(String analysistime) {
		this.analysistime = analysistime;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMapCaunbalanceTableId))
			return false;
		AbstractMapCaunbalanceTableId castOther = (AbstractMapCaunbalanceTableId) other;

		return ((this.getAccno() == castOther.getAccno()) || (this.getAccno() != null
				&& castOther.getAccno() != null && this.getAccno().equals(
				castOther.getAccno())))
				&& ((this.getAnalysistime() == castOther.getAnalysistime()) || (this
						.getAnalysistime() != null
						&& castOther.getAnalysistime() != null && this
						.getAnalysistime().equals(castOther.getAnalysistime())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getAccno() == null ? 0 : this.getAccno().hashCode());
		result = 37
				* result
				+ (getAnalysistime() == null ? 0 : this.getAnalysistime()
						.hashCode());
		return result;
	}

}