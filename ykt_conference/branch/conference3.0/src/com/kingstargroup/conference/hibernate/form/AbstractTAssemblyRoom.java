package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTAssemblyRoom entity provides the base persistence definition of the
 * TAssemblyRoom entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTAssemblyRoom implements java.io.Serializable {

	// Fields

	private String roomId;
	private String roomName;
	private String address;
	private String sign;
	private long contain;
	private String comments;

	// Constructors

	/** default constructor */
	public AbstractTAssemblyRoom() {
	}

	/** full constructor */
	public AbstractTAssemblyRoom(String roomName, String address, String sign,
			long contain, String comments) {
		this.roomName = roomName;
		this.address = address;
		this.sign = sign;
		this.contain = contain;
		this.comments = comments;
	}

	// Property accessors

	public String getRoomId() {
		return this.roomId;
	}

	public void setRoomId(String roomId) {
		this.roomId = roomId;
	}

	public String getRoomName() {
		return this.roomName;
	}

	public void setRoomName(String roomName) {
		this.roomName = roomName;
	}

	public String getAddress() {
		return this.address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public String getSign() {
		return this.sign;
	}

	public void setSign(String sign) {
		this.sign = sign;
	}

	public long getContain() {
		return this.contain;
	}

	public void setContain(long contain) {
		this.contain = contain;
	}

	public String getComments() {
		return this.comments;
	}

	public void setComments(String comments) {
		this.comments = comments;
	}

}