package org.king.check.domain;

import java.math.BigDecimal;

/**
 * AbstractTRoomdeviceId entity provides the base persistence definition of the
 * TRoomdeviceId entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTRoomdeviceId  implements java.io.Serializable {

	// Fields

	private String roomId;
	private Integer deviceId;

	// Constructors

	/** default constructor */
	public AbstractTRoomdeviceId() {
	}

	/** full constructor */
	public AbstractTRoomdeviceId(String roomId, Integer deviceId) {
		this.roomId = roomId;
		this.deviceId = deviceId;
	}

	// Property accessors


	public String getRoomId() {
		return roomId;
	}

	public void setRoomId(String roomId) {
		this.roomId = roomId;
	}

	public Integer getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(Integer deviceId) {
		this.deviceId = deviceId;
	}


}