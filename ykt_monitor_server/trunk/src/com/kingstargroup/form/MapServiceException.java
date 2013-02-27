package com.kingstargroup.form;

/**
 * MapServiceException entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapServiceException extends AbstractMapServiceException implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapServiceException() {
	}

	/** minimal constructor */
	public MapServiceException(MapServiceExceptionId id) {
		super(id);
	}

	/** full constructor */
	public MapServiceException(MapServiceExceptionId id, long serverId,
			String serverName, String serviceType, String status,
			String contactname, long errorcode) {
		super(id, serverId, serverName, serviceType, status, contactname,
				errorcode);
	}

}
