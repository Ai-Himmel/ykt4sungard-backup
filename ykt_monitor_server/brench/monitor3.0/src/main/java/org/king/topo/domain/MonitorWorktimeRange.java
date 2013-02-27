package org.king.topo.domain;


/**
 * MonitorWorktimeRange entity. @author MyEclipse Persistence Tools
 */
public class MonitorWorktimeRange extends AbstractMonitorWorktimeRange
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorWorktimeRange() {
	}

	/** full constructor */
	public MonitorWorktimeRange(String formtime, String totime,
			String displaytime, Boolean enable) {
		super(formtime, totime, displaytime, enable);
	}

}
