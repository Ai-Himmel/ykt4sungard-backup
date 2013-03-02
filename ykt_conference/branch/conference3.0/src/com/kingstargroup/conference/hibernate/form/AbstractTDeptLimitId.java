package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDeptLimitId entity provides the base persistence definition of the
 * TDeptLimitId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDeptLimitId implements java.io.Serializable {

	// Fields

	private String operCode;
	private String deptId;

	// Constructors

	/** default constructor */
	public AbstractTDeptLimitId() {
	}

	/** full constructor */
	public AbstractTDeptLimitId(String operCode, String deptId) {
		this.operCode = operCode;
		this.deptId = deptId;
	}

	// Property accessors

	public String getOperCode() {
		return this.operCode;
	}

	public void setOperCode(String operCode) {
		this.operCode = operCode;
	}

	public String getDeptId() {
		return this.deptId;
	}

	public void setDeptId(String deptId) {
		this.deptId = deptId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTDeptLimitId))
			return false;
		AbstractTDeptLimitId castOther = (AbstractTDeptLimitId) other;

		return ((this.getOperCode() == castOther.getOperCode()) || (this
				.getOperCode() != null
				&& castOther.getOperCode() != null && this.getOperCode()
				.equals(castOther.getOperCode())))
				&& ((this.getDeptId() == castOther.getDeptId()) || (this
						.getDeptId() != null
						&& castOther.getDeptId() != null && this.getDeptId()
						.equals(castOther.getDeptId())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getOperCode() == null ? 0 : this.getOperCode().hashCode());
		result = 37 * result
				+ (getDeptId() == null ? 0 : this.getDeptId().hashCode());
		return result;
	}

}