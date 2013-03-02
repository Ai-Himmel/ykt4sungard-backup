package org.king.check.domain;

/**
 * TCheckDeviceLocation entity. @author MyEclipse Persistence Tools
 */
public class TCheckDeviceLocation extends AbstractTCheckDeviceLocation
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCheckDeviceLocation() {
	}

	/** minimal constructor */
	public TCheckDeviceLocation(TCheckDeviceLocationId id) {
		super(id);
	}

	/** full constructor */
	public TCheckDeviceLocation(TCheckDeviceLocationId id, String checkType) {
		super(id, checkType);
	}

}
