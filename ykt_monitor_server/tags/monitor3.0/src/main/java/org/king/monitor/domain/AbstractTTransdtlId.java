package org.king.monitor.domain;

/**
 * AbstractTTransdtlId entity provides the base persistence definition of the
 * TTransdtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTransdtlId implements java.io.Serializable {

	// Fields

	private String accdate;
	private long termid;
	private long termseqno;

	// Constructors

	/** default constructor */
	public AbstractTTransdtlId() {
	}

	/** full constructor */
	public AbstractTTransdtlId(String accdate, long termid, long termseqno) {
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

	public long getTermid() {
		return this.termid;
	}

	public void setTermid(long termid) {
		this.termid = termid;
	}

	public long getTermseqno() {
		return this.termseqno;
	}

	public void setTermseqno(long termseqno) {
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
				&& (this.getTermid() == castOther.getTermid())
				&& (this.getTermseqno() == castOther.getTermseqno());
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getAccdate() == null ? 0 : this.getAccdate().hashCode());
		result = 37 * result + (int) this.getTermid();
		result = 37 * result + (int) this.getTermseqno();
		return result;
	}

}