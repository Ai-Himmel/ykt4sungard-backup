package com.kingstargroup.fdykt.newform;

/**
 * AbstractTPosdtlId entity provides the base persistence definition of the
 * TPosdtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTPosdtlId implements java.io.Serializable {

	// Fields

	private String transdate;
	private String devphyid;
	private Long devseqno;

	// Constructors

	/** default constructor */
	public AbstractTPosdtlId() {
	}

	/** full constructor */
	public AbstractTPosdtlId(String transdate, String devphyid, Long devseqno) {
		this.transdate = transdate;
		this.devphyid = devphyid;
		this.devseqno = devseqno;
	}

	// Property accessors

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

	public Long getDevseqno() {
		return this.devseqno;
	}

	public void setDevseqno(Long devseqno) {
		this.devseqno = devseqno;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTPosdtlId))
			return false;
		AbstractTPosdtlId castOther = (AbstractTPosdtlId) other;

		return ((this.getTransdate() == castOther.getTransdate()) || (this
				.getTransdate() != null
				&& castOther.getTransdate() != null && this.getTransdate()
				.equals(castOther.getTransdate())))
				&& ((this.getDevphyid() == castOther.getDevphyid()) || (this
						.getDevphyid() != null
						&& castOther.getDevphyid() != null && this
						.getDevphyid().equals(castOther.getDevphyid())))
				&& ((this.getDevseqno() == castOther.getDevseqno()) || (this
						.getDevseqno() != null
						&& castOther.getDevseqno() != null && this
						.getDevseqno().equals(castOther.getDevseqno())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getTransdate() == null ? 0 : this.getTransdate().hashCode());
		result = 37 * result
				+ (getDevphyid() == null ? 0 : this.getDevphyid().hashCode());
		result = 37 * result
				+ (getDevseqno() == null ? 0 : this.getDevseqno().hashCode());
		return result;
	}

}