package org.king.check.domain;

/**
 * AbstractTRoom entity provides the base persistence definition of the TRoom
 * entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTRoom  implements java.io.Serializable {

	// Fields

	private String roomId;
	private TArea schoolArea = new TArea();
	private String build;
	private String roomName;
	private Integer status;
	

	public AbstractTRoom() {
	}

	public AbstractTRoom(String roomId) {
		this.roomId = roomId;
	}

	public AbstractTRoom(TArea schoolArea, String build, String roomName,Integer status) {
		this.schoolArea = schoolArea;
		this.build = build;
		this.roomName = roomName;
		this.status = status;
	}

	public String getRoomId() {
		return roomId;
	}
	public void setRoomId(String roomId) {
		this.roomId = roomId;
	}

	public TArea getSchoolArea() {
		return schoolArea;
	}

	public void setSchoolArea(TArea schoolArea) {
		this.schoolArea = schoolArea;
	}

	public String getBuild() {
		return build;
	}

	public void setBuild(String build) {
		this.build = build;
	}

	public String getRoomName() {
		return roomName;
	}

	public void setRoomName(String roomName) {
		this.roomName = roomName;
	}

	public Integer getStatus() {
		return status;
	}

	public void setStatus(Integer status) {
		this.status = status;
	}
	
}