package org.king.topo.domain;


/**
 * MonitorTopoLocation entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoLocation extends AbstractMonitorTopoLocation implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoLocation() {
	}

	/** full constructor */
	public MonitorTopoLocation(String locationname, Integer locationindex) {
		super(locationname, locationindex);
	}

}
