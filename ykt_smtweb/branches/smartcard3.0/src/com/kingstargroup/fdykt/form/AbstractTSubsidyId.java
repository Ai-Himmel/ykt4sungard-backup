package com.kingstargroup.fdykt.form;

/**
 * AbstractTSubsidyId entity provides the base persistence definition of the
 * TSubsidyId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTSubsidyId implements java.io.Serializable {

	// Fields

	private String batchno;
	private Long seqno;

	// Constructors

	/** default constructor */
	public AbstractTSubsidyId() {
	}

	/** full constructor */
	public AbstractTSubsidyId(String batchno, Long seqno) {
		this.batchno = batchno;
		this.seqno = seqno;
	}

	// Property accessors

	public String getBatchno() {
		return this.batchno;
	}

	public void setBatchno(String batchno) {
		this.batchno = batchno;
	}

	public Long getSeqno() {
		return this.seqno;
	}

	public void setSeqno(Long seqno) {
		this.seqno = seqno;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTSubsidyId))
			return false;
		AbstractTSubsidyId castOther = (AbstractTSubsidyId) other;

		return ((this.getBatchno() == castOther.getBatchno()) || (this
				.getBatchno() != null
				&& castOther.getBatchno() != null && this.getBatchno().equals(
				castOther.getBatchno())))
				&& ((this.getSeqno() == castOther.getSeqno()) || (this
						.getSeqno() != null
						&& castOther.getSeqno() != null && this.getSeqno()
						.equals(castOther.getSeqno())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getBatchno() == null ? 0 : this.getBatchno().hashCode());
		result = 37 * result
				+ (getSeqno() == null ? 0 : this.getSeqno().hashCode());
		return result;
	}

}