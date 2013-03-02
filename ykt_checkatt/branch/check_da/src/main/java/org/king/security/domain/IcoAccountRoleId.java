package org.king.security.domain;

/**
 * IcoAccountRoleId entity. @author MyEclipse Persistence Tools
 */

public class IcoAccountRoleId  implements
		java.io.Serializable {

	// Fields

	private String accountId;
	private String roleId;

	// Constructors

	/** default constructor */
	public IcoAccountRoleId() {
	}

	/** full constructor */
	public IcoAccountRoleId(String accountId, String roleId) {
		this.accountId = accountId;
		this.roleId = roleId;
	}

	// Property accessors

	public String getAccountId() {
		return this.accountId;
	}

	public void setAccountId(String accountId) {
		this.accountId = accountId;
	}

	public String getRoleId() {
		return this.roleId;
	}

	public void setRoleId(String roleId) {
		this.roleId = roleId;
	}

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof IcoAccountRoleId))
			return false;
		IcoAccountRoleId castOther = (IcoAccountRoleId) other;

		return ((this.getAccountId() == castOther.getAccountId()) || (this
				.getAccountId() != null
				&& castOther.getAccountId() != null && this.getAccountId()
				.equals(castOther.getAccountId())))
				&& ((this.getRoleId() == castOther.getRoleId()) || (this
						.getRoleId() != null
						&& castOther.getRoleId() != null && this.getRoleId()
						.equals(castOther.getRoleId())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getAccountId() == null ? 0 : this.getAccountId().hashCode());
		result = 37 * result
				+ (getRoleId() == null ? 0 : this.getRoleId().hashCode());
		return result;
	}

}