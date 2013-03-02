package com.kingstargroup.fdykt.newform;

/**
 * AbstractTbankcardId entity provides the base persistence definition of the
 * TbankcardId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTbankcardId implements java.io.Serializable {

	// Fields

	private Long custid;
	private String bankcode;

	// Constructors

	/** default constructor */
	public AbstractTbankcardId() {
	}

	/** full constructor */
	public AbstractTbankcardId(Long custid, String bankcode) {
		this.custid = custid;
		this.bankcode = bankcode;
	}

	// Property accessors

	public Long getCustid() {
		return this.custid;
	}

	public void setCustid(Long custid) {
		this.custid = custid;
	}

	public String getBankcode() {
		return this.bankcode;
	}

	public void setBankcode(String bankcode) {
		this.bankcode = bankcode;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTbankcardId))
			return false;
		AbstractTbankcardId castOther = (AbstractTbankcardId) other;

		return ((this.getCustid() == castOther.getCustid()) || (this
				.getCustid() != null
				&& castOther.getCustid() != null && this.getCustid().equals(
				castOther.getCustid())))
				&& ((this.getBankcode() == castOther.getBankcode()) || (this
						.getBankcode() != null
						&& castOther.getBankcode() != null && this
						.getBankcode().equals(castOther.getBankcode())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getCustid() == null ? 0 : this.getCustid().hashCode());
		result = 37 * result
				+ (getBankcode() == null ? 0 : this.getBankcode().hashCode());
		return result;
	}

}