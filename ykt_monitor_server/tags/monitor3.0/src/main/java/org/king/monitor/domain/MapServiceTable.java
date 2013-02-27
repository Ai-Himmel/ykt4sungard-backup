package org.king.monitor.domain;

/**
 * MapServiceTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapServiceTable extends AbstractMapServiceTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapServiceTable() {
	}

	/** full constructor */
	public MapServiceTable(String serviceName, long serverId,
			String serverName, String serviceType, String url, String ip,
			long port, String dbname, String username, String password) {
		super(serviceName, serverId, serverName, serviceType, url, ip, port,
				dbname, username, password);
	}

}
