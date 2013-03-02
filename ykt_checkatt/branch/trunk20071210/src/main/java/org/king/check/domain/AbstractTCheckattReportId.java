package org.king.check.domain;

/**
 * AbstractTCheckattReportId entity provides the base persistence definition of
 * the TCheckattReportId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckattReportId extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private long custId;
	private String checkDate;

	// Constructors

	/** default constructor */
	public AbstractTCheckattReportId() {
	}

	/** full constructor */
	public AbstractTCheckattReportId(long custId, String checkDate) {
		this.custId = custId;
		this.checkDate = checkDate;
	}

	// Property accessors

	public long getCustId() {
		return this.custId;
	}

	public void setCustId(long custId) {
		this.custId = custId;
	}

	public String getCheckDate() {
		return this.checkDate;
	}

	public void setCheckDate(String checkDate) {
		this.checkDate = checkDate;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTCheckattReportId))
			return false;
		AbstractTCheckattReportId castOther = (AbstractTCheckattReportId) other;

		return (this.getCustId() == castOther.getCustId())
				&& ((this.getCheckDate() == castOther.getCheckDate()) || (this
						.getCheckDate() != null
						&& castOther.getCheckDate() != null && this
						.getCheckDate().equals(castOther.getCheckDate())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (int) this.getCustId();
		result = 37 * result
				+ (getCheckDate() == null ? 0 : this.getCheckDate().hashCode());
		return result;
	}

}