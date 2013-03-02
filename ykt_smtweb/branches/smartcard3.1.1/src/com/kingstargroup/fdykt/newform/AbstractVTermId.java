package com.kingstargroup.fdykt.newform;

/**
 * AbstractVTermId entity provides the base persistence definition of the
 * VTermId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVTermId implements java.io.Serializable {

	// Fields

	private Long termid;
	private String termname;

	// Constructors

	/** default constructor */
	public AbstractVTermId() {
	}

	/** full constructor */
	public AbstractVTermId(Long termid, String termname) {
		this.termid = termid;
		this.termname = termname;
	}

	// Property accessors

	public Long getTermid() {
		return this.termid;
	}

	public void setTermid(Long termid) {
		this.termid = termid;
	}

	public String getTermname() {
		return this.termname;
	}

	public void setTermname(String termname) {
		this.termname = termname;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractVTermId))
			return false;
		AbstractVTermId castOther = (AbstractVTermId) other;

		return ((this.getTermid() == castOther.getTermid()) || (this
				.getTermid() != null
				&& castOther.getTermid() != null && this.getTermid().equals(
				castOther.getTermid())))
				&& ((this.getTermname() == castOther.getTermname()) || (this
						.getTermname() != null
						&& castOther.getTermname() != null && this
						.getTermname().equals(castOther.getTermname())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getTermid() == null ? 0 : this.getTermid().hashCode());
		result = 37 * result
				+ (getTermname() == null ? 0 : this.getTermname().hashCode());
		return result;
	}

}