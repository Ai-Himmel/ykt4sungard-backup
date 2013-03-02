package org.king.check.domain;

/**
 * AbstractTRoomdevice entity provides the base persistence definition of the
 * TRoomdevice entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTRoomdevice  implements java.io.Serializable {

	// Fields

	private TRoomdeviceId id;

	// Constructors

	/** default constructor */
	public AbstractTRoomdevice() {
	}

	/** full constructor */
	public AbstractTRoomdevice(TRoomdeviceId id) {
		this.id = id;
	}

	// Property accessors

	public TRoomdeviceId getId() {
		return this.id;
	}

	public void setId(TRoomdeviceId id) {
		this.id = id;
	}

}