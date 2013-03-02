package org.king.check.domain;

import java.math.BigDecimal;

/**
 * AbstractTClassteacherId entity provides the base persistence definition of
 * the TClassteacherId entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTClassteacherId  implements java.io.Serializable {

	// Fields

	private String classid;
	private BigDecimal custid;

	// Constructors

	/** default constructor */
	public AbstractTClassteacherId() {
	}

	/** full constructor */
	public AbstractTClassteacherId(String classid, BigDecimal custid) {
		this.classid = classid;
		this.custid = custid;
	}

	// Property accessors

	public String getClassid() {
		return this.classid;
	}

	public void setClassid(String classid) {
		this.classid = classid;
	}

	public BigDecimal getCustid() {
		return this.custid;
	}

	public void setCustid(BigDecimal custid) {
		this.custid = custid;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTClassteacherId))
			return false;
		AbstractTClassteacherId castOther = (AbstractTClassteacherId) other;

		return ((this.getClassid() == castOther.getClassid()) || (this
				.getClassid() != null
				&& castOther.getClassid() != null && this.getClassid().equals(
				castOther.getClassid())))
				&& ((this.getCustid() == castOther.getCustid()) || (this
						.getCustid() != null
						&& castOther.getCustid() != null && this.getCustid()
						.equals(castOther.getCustid())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getClassid() == null ? 0 : this.getClassid().hashCode());
		result = 37 * result
				+ (getCustid() == null ? 0 : this.getCustid().hashCode());
		return result;
	}

}