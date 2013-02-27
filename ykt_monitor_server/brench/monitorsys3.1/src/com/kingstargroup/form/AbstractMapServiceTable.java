package com.kingstargroup.form;

/**
 * AbstractMapServiceTable entity provides the base persistence definition of
 * the MapServiceTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapServiceTable implements java.io.Serializable {

	// Fields

	private long serviceId;
	private String serviceName;
	private long serverId;
	private String serverName;
	private String serviceType;
	private String url;
	private String ip;
	private long port;
	private String dbname;
	private String username;
	private String password;

	// Constructors

	/** default constructor */
	public AbstractMapServiceTable() {
	}

	/** full constructor */
	public AbstractMapServiceTable(String serviceName, long serverId,
			String serverName, String serviceType, String url, String ip,
			long port, String dbname, String username, String password) {
		this.serviceName = serviceName;
		this.serverId = serverId;
		this.serverName = serverName;
		this.serviceType = serviceType;
		this.url = url;
		this.ip = ip;
		this.port = port;
		this.dbname = dbname;
		this.username = username;
		this.password = password;
	}

	// Property accessors

	public long getServiceId() {
		return this.serviceId;
	}

	public void setServiceId(long serviceId) {
		this.serviceId = serviceId;
	}

	public String getServiceName() {
		return this.serviceName;
	}

	public void setServiceName(String serviceName) {
		this.serviceName = serviceName;
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

	public String getUrl() {
		return this.url;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public long getPort() {
		return this.port;
	}

	public void setPort(long port) {
		this.port = port;
	}

	public String getDbname() {
		return this.dbname;
	}

	public void setDbname(String dbname) {
		this.dbname = dbname;
	}

	public String getUsername() {
		return this.username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return this.password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

}