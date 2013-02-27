package org.king.topo.domain;


/**
 * MonitorDevWorktime entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevWorktime extends AbstractMonitorDevWorktime implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevWorktime() {
	}

	/** full constructor */
	public MonitorDevWorktime(Integer worktimeid, Integer deviceid) {
		super(worktimeid, deviceid);
	}

}
