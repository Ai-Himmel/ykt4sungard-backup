package org.king.check.domain;

/**
 * TRoom entity. @author MyEclipse Persistence Tools
 */
public class TRoom extends AbstractTRoom implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TRoom() {
	}

	/** minimal constructor */
	public TRoom(String roomId) {
		super(roomId);
	}
	public TRoom(TArea schoolArea, String build, String roomName,Integer status) {
		super(schoolArea,  build,  roomName, status);
	}



}
