package org.king.monitor.domain;

/**
 * AbstractMapServiceException entity provides the base persistence definition
 * of the MapServiceException entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapServiceException implements
		java.io.Serializable {

	// Fields

	private MapServiceExceptionId id;
	private long serverId;
	private String serverName;
	private String serviceType;
	private String status;
	private String contactname;
	private long errorcode;

	// Constructors

	/** default constructor */
	public AbstractMapServiceException() {
	}

	/** minimal constructor */
	public AbstractMapServiceException(MapServiceExceptionId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapServiceException(MapServiceExceptionId id, long serverId,
			String serverName, String serviceType, String status,
			String contactname, long errorcode) {
		this.id = id;
		this.serverId = serverId;
		this.serverName = serverName;
		this.serviceType = serviceType;
		this.status = status;
		this.contactname = contactname;
		this.errorcode = errorcode;
	}

	// Property accessors

	public MapServiceExceptionId getId() {
		return this.id;
	}

	public void setId(MapServiceExceptionId id) {
		this.id = id;
	}

	public long getServerId() {
		return this.serverId;
	}

	public void setServerId(long serverId) {
		this.serverId = serverId;
	}

	public String getServerName() {
		return this.serverName;
	}

	public void setServerName(String serverName) {
		this.serverName = serverName;
	}

	public String getServiceType() {
		return this.serviceType;
	}

	public void setServiceType(String serviceType) {
		this.serviceType = serviceType;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getContactname() {
		return this.contactname;
	}

	public void setContactname(String contactname) {
		this.contactname = contactname;
	}

	public long getErrorcode() {
		return this.errorcode;
	}

	public void setErrorcode(long errorcode) {
		this.errorcode = errorcode;
	}

}