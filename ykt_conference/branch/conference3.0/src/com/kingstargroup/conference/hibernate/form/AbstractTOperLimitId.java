package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTOperLimitId entity provides the base persistence definition of the
 * TOperLimitId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTOperLimitId implements java.io.Serializable {

	// Fields

	private String operCode;
	private String funcCode;

	// Constructors

	/** default constructor */
	public AbstractTOperLimitId() {
	}

	/** full constructor */
	public AbstractTOperLimitId(String operCode, String funcCode) {
		this.operCode = operCode;
		this.funcCode = funcCode;
	}

	// Property accessors

	public String getOperCode() {
		return this.operCode;
	}

	public void setOperCode(String operCode) {
		this.operCode = operCode;
	}

	public String getFuncCode() {
		return this.funcCode;
	}

	public void setFuncCode(String funcCode) {
		this.funcCode = funcCode;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractTOperLimitId))
			return false;
		AbstractTOperLimitId castOther = (AbstractTOperLimitId) other;

		return ((this.getOperCode() == castOther.getOperCode()) || (this
				.getOperCode() != null
				&& castOther.getOperCode() != null && this.getOperCode()
				.equals(castOther.getOperCode())))
				&& ((this.getFuncCode() == castOther.getFuncCode()) || (this
						.getFuncCode() != null
						&& castOther.getFuncCode() != null && this
						.getFuncCode().equals(castOther.getFuncCode())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getOperCode() == null ? 0 : this.getOperCode().hashCode());
		result = 37 * result
				+ (getFuncCode() == null ? 0 : this.getFuncCode().hashCode());
		return result;
	}

}