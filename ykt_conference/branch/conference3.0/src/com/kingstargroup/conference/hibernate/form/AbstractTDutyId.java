package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDutyId entity provides the base persistence definition of the
 * TDutyId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDutyId implements java.io.Serializable {

	// Fields

	private String stuempNo;
	private String oaAccount;

	// Constructors

	/** default constructor */
	public AbstractTDutyId() {
	}

	/** full constructor */
	public AbstractTDutyId(String stuempNo, String oaAccount) {
		this.stuempNo = stuempNo;
		this.oaAccount = oaAccount;
	}

	// Property accessors

	public String getStuempNo() {
		return this.stuempNo;
	}

	public void setStuempNo(String stuempNo) {
		this.stuempNo = stuempNo;
	}

	public String getOaAccount() {
		return this.oaAccount;
	}

	public void setOaAccount(String oaAccount) {
		this.oaAccount = oaAccount;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTDutyId))
			return false;
		AbstractTDutyId castOther = (AbstractTDutyId) other;

		return ((this.getStuempNo() == castOther.getStuempNo()) || (this
				.getStuempNo() != null
				&& castOther.getStuempNo() != null && this.getStuempNo()
				.equals(castOther.getStuempNo())))
				&& ((this.getOaAccount() == castOther.getOaAccount()) || (this
						.getOaAccount() != null
						&& castOther.getOaAccount() != null && this
						.getOaAccount().equals(castOther.getOaAccount())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getStuempNo() == null ? 0 : this.getStuempNo().hashCode());
		result = 37 * result
				+ (getOaAccount() == null ? 0 : this.getOaAccount().hashCode());
		return result;
	}

}