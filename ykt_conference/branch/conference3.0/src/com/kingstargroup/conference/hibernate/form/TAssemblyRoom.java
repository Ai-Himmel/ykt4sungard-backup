package com.kingstargroup.conference.hibernate.form;

/**
 * TAssemblyRoom entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TAssemblyRoom extends AbstractTAssemblyRoom implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TAssemblyRoom() {
	}

	/** full constructor */
	public TAssemblyRoom(String roomName, String address, String sign,
			long contain, String comments) {
		super(roomName, address, sign, contain, comments);
	}

}
