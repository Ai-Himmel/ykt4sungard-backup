package com.kingstargroup.fdykt.newform;

/**
 * AbstractStoreLimitId entity provides the base persistence definition of the
 * StoreLimitId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractStoreLimitId implements java.io.Serializable {

	// Fields

	private String operCode;
	private String storeCode;

	// Constructors

	/** default constructor */
	public AbstractStoreLimitId() {
	}

	/** full constructor */
	public AbstractStoreLimitId(String operCode, String storeCode) {
		this.operCode = operCode;
		this.storeCode = storeCode;
	}

	// Property accessors

	public String getOperCode() {
		return this.operCode;
	}

	public void setOperCode(String operCode) {
		this.operCode = operCode;
	}

	public String getStoreCode() {
		return this.storeCode;
	}

	public void setStoreCode(String storeCode) {
		this.storeCode = storeCode;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractStoreLimitId))
			return false;
		AbstractStoreLimitId castOther = (AbstractStoreLimitId) other;

		return ((this.getOperCode() == castOther.getOperCode()) || (this
				.getOperCode() != null
				&& castOther.getOperCode() != null && this.getOperCode()
				.equals(castOther.getOperCode())))
				&& ((this.getStoreCode() == castOther.getStoreCode()) || (this
						.getStoreCode() != null
						&& castOther.getStoreCode() != null && this
						.getStoreCode().equals(castOther.getStoreCode())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getOperCode() == null ? 0 : this.getOperCode().hashCode());
		result = 37 * result
				+ (getStoreCode() == null ? 0 : this.getStoreCode().hashCode());
		return result;
	}

}