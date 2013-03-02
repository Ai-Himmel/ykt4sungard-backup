package org.king.security.domain;

/**
 * IcoAccountRole entity. @author MyEclipse Persistence Tools
 */

public class IcoAccountRole  implements
		java.io.Serializable {

	// Fields

	private IcoAccountRoleId id;

	// Constructors

	/** default constructor */
	public IcoAccountRole() {
	}

	/** full constructor */
	public IcoAccountRole(IcoAccountRoleId id) {
		this.id = id;
	}

	// Property accessors

	public IcoAccountRoleId getId() {
		return this.id;
	}

	public void setId(IcoAccountRoleId id) {
		this.id = id;
	}

}