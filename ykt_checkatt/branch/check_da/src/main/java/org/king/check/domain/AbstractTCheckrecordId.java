package org.king.check.domain;

import java.math.BigDecimal;

/**
 * AbstractTCheckrecordId entity provides the base persistence definition of the
 * TCheckrecordId entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckrecordId  implements  	java.io.Serializable {

	// Fields

	private Integer serialno;
	private Integer deviceid;
	private String punchdate;

	// Constructors

	/** default constructor */
	public AbstractTCheckrecordId() {
	}

	/** full constructor */
	public AbstractTCheckrecordId(Integer serialno, Integer deviceid,
			String punchdate) {
		this.serialno = serialno;
		this.deviceid = deviceid;
		this.punchdate = punchdate;
	}

	// Property accessors

	public Integer getSerialno() {
		return this.serialno;
	}

	public void setSerialno(Integer serialno) {
		this.serialno = serialno;
	}

	public Integer getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Integer deviceid) {
		this.deviceid = deviceid;
	}

	public String getPunchdate() {
		return this.punchdate;
	}

	public void setPunchdate(String punchdate) {
		this.punchdate = punchdate;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTCheckrecordId))
			return false;
		AbstractTCheckrecordId castOther = (AbstractTCheckrecordId) other;

		return ((this.getSerialno() == castOther.getSerialno()) || (this
				.getSerialno() != null
				&& castOther.getSerialno() != null && this.getSerialno()
				.equals(castOther.getSerialno())))
				&& ((this.getDeviceid() == castOther.getDeviceid()) || (this
						.getDeviceid() != null
						&& castOther.getDeviceid() != null && this
						.getDeviceid().equals(castOther.getDeviceid())))
				&& ((this.getPunchdate() == castOther.getPunchdate()) || (this
						.getPunchdate() != null
						&& castOther.getPunchdate() != null && this
						.getPunchdate().equals(castOther.getPunchdate())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getSerialno() == null ? 0 : this.getSerialno().hashCode());
		result = 37 * result
				+ (getDeviceid() == null ? 0 : this.getDeviceid().hashCode());
		result = 37 * result
				+ (getPunchdate() == null ? 0 : this.getPunchdate().hashCode());
		return result;
	}

}