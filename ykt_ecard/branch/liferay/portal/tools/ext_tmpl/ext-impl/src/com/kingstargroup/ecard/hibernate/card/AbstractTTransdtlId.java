package com.kingstargroup.ecard.hibernate.card;

/**
 * AbstractTTransdtlId entity provides the base persistence definition of the
 * TTransdtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTransdtlId implements java.io.Serializable {

	// Fields

	private String accdate;
	private Long termid;
	private Long termseqno;

	// Constructors

	/** default constructor */
	public AbstractTTransdtlId() {
	}

	/** full constructor */
	public AbstractTTransdtlId(String accdate, Long termid, Long termseqno) {
		this.accdate = accdate;
		this.termid = termid;
		this.termseqno = termseqno;
	}

	// Property accessors

	public String getAccdate() {
		return this.accdate;
	}

	public void setAccdate(String accdate) {
		this.accdate = accdate;
	}

	public Long getTermid() {
		return this.termid;
	}

	public void setTermid(Long termid) {
		this.termid = termid;
	}

	public Long getTermseqno() {
		return this.termseqno;
	}

	public void setTermseqno(Long termseqno) {
		this.termseqno = termseqno;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTTransdtlId))
			return false;
		AbstractTTransdtlId castOther = (AbstractTTransdtlId) other;

		return ((this.getAccdate() == castOther.getAccdate()) || (this
				.getAccdate() != null
				&& castOther.getAccdate() != null && this.getAccdate().equals(
				castOther.getAccdate())))
				&& ((this.getTermid() == castOther.getTermid()) || (this
						.getTermid() != null
						&& castOther.getTermid() != null && this.getTermid()
						.equals(castOther.getTermid())))
				&& ((this.getTermseqno() == castOther.getTermseqno()) || (this
						.getTermseqno() != null
						&& castOther.getTermseqno() != null && this
						.getTermseqno().equals(castOther.getTermseqno())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getAccdate() == null ? 0 : this.getAccdate().hashCode());
		result = 37 * result
				+ (getTermid() == null ? 0 : this.getTermid().hashCode());
		result = 37 * result
				+ (getTermseqno() == null ? 0 : this.getTermseqno().hashCode());
		return result;
	}

}