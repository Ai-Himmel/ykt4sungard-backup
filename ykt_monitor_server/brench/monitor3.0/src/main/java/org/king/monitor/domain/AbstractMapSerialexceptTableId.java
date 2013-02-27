package org.king.monitor.domain;

/**
 * AbstractMapSerialexceptTableId entity provides the base persistence
 * definition of the MapSerialexceptTableId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSerialexceptTableId implements
		java.io.Serializable {

	// Fields

	private String analysistime;
	private String transdate;
	private String devphyid;
	private long devseqno;

	// Constructors

	/** default constructor */
	public AbstractMapSerialexceptTableId() {
	}

	/** full constructor */
	public AbstractMapSerialexceptTableId(String analysistime,
			String transdate, String devphyid, long devseqno) {
		this.analysistime = analysistime;
		this.transdate = transdate;
		this.devphyid = devphyid;
		this.devseqno = devseqno;
	}

	// Property accessors

	public String getAnalysistime() {
		return this.analysistime;
	}

	public void setAnalysistime(String analysistime) {
		this.analysistime = analysistime;
	}

	public String getTransdate() {
		return this.transdate;
	}

	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}

	public String getDevphyid() {
		return this.devphyid;
	}

	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}

	public long getDevseqno() {
		return this.devseqno;
	}

	public void setDevseqno(long devseqno) {
		this.devseqno = devseqno;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractMapSerialexceptTableId))
			return false;
		AbstractMapSerialexceptTableId castOther = (AbstractMapSerialexceptTableId) other;

		return ((this.getAnalysistime() == castOther.getAnalysistime()) || (this
				.getAnalysistime() != null
				&& castOther.getAnalysistime() != null && this
				.getAnalysistime().equals(castOther.getAnalysistime())))
				&& ((this.getTransdate() == castOther.getTransdate()) || (this
						.getTransdate() != null
						&& castOther.getTransdate() != null && this
						.getTransdate().equals(castOther.getTransdate())))
				&& ((this.getDevphyid() == castOther.getDevphyid()) || (this
						.getDevphyid() != null
						&& castOther.getDevphyid() != null && this
						.getDevphyid().equals(castOther.getDevphyid())))
				&& (this.getDevseqno() == castOther.getDevseqno());
	}

	public int hashCode() {
		int result = 17;

		result = 37
				* result
				+ (getAnalysistime() == null ? 0 : this.getAnalysistime()
						.hashCode());
		result = 37 * result
				+ (getTransdate() == null ? 0 : this.getTransdate().hashCode());
		result = 37 * result
				+ (getDevphyid() == null ? 0 : this.getDevphyid().hashCode());
		result = 37 * result + (int) this.getDevseqno();
		return result;
	}

}