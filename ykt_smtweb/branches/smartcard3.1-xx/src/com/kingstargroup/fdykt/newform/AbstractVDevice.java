package com.kingstargroup.fdykt.newform;

/**
 * AbstractVDevice entity provides the base persistence definition of the
 * VDevice entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVDevice implements java.io.Serializable {

	// Fields

	private VDeviceId id;

	// Constructors

	/** default constructor */
	public AbstractVDevice() {
	}

	/** full constructor */
	public AbstractVDevice(VDeviceId id) {
		this.id = id;
	}

	// Property accessors

	public VDeviceId getId() {
		return this.id;
	}

	public void setId(VDeviceId id) {
		this.id = id;
	}

}