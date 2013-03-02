package org.king.check.domain;

/**
 * AbstractTCheckDeviceLocation entity provides the base persistence definition
 * of the TCheckDeviceLocation entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckDeviceLocation implements
		java.io.Serializable {

	// Fields

	private TCheckDeviceLocationId id;
	private String checkType;

	// Constructors

	/** default constructor */
	public AbstractTCheckDeviceLocation() {
	}

	/** minimal constructor */
	public AbstractTCheckDeviceLocation(TCheckDeviceLocationId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTCheckDeviceLocation(TCheckDeviceLocationId id,
			String checkType) {
		this.id = id;
		this.checkType = checkType;
	}

	// Property accessors

	public TCheckDeviceLocationId getId() {
		return this.id;
	}

	public void setId(TCheckDeviceLocationId id) {
		this.id = id;
	}

	public String getCheckType() {
		return this.checkType;
	}

	public void setCheckType(String checkType) {
		this.checkType = checkType;
	}

}