package org.king.business.domain;


/**
 * MonitorDevtransCheck entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevtransCheck extends AbstractMonitorDevtransCheck
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevtransCheck() {
	}

	/** full constructor */
	public MonitorDevtransCheck(Integer worktimeid, String checkpoint,
			String lasttransdate, String lasttranstime) {
		super(worktimeid, checkpoint, lasttransdate, lasttranstime);
	}

}
